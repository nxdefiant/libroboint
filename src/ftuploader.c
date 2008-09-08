/*
 * Copyright (C) 2007 Erik Andresen erik@vontaene.de
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <usb.h>
#include <ftlib.h>

#define PROGRAM_UPLOAD_PACKET_SIZE 128
#define FLASH1 0x0
#define FLASH2 0x1
#define RAM 0x2
#define INTERFACE_NUM_DEFAULT 0
#define MAJOR_VERSION LIBFT_VERSION_MAJOR
#define MINOR_VERSION LIBFT_VERSION_MINOR
#define PATCH_VERSION LIBFT_VERSION_PATCH

int g_debug=0;
#define debug_print(fmt, args...) if(g_debug) printf(fmt, ##args)

void parse_hex_line(char *line, int size, char *result, int pos)
{
	int hexval;
	char s[3] = { '\0' };
	int i;
	int k;

	for(i=0, k=pos; i < size; i+=2, k++) {
		strncpy(s, &line[i], 2);
		sscanf(s, "%x", &hexval);
		*(result + k) = hexval;
	}
}


// TODO: check checksum
int read_hex(char *filename, char **result, int *dest)
{
	FILE *f;
	char buffer[1000];
	int result_len = 0; // length of data needed
	int result_size = 0; // length of *result array
	int len; // len of data in current line
	char tmp[5] = { '\0' };
	short int addr;
	short int addr_pre = 0;
	int len_pre = 256;
	int diff;

	*result = NULL;

	f = fopen(filename, "r");
	if (f == 0) {
		perror("fopen");
		return 0;
	}

	// start scanning first line
	fseek(f, 1, SEEK_CUR);
	fgets(buffer, 3, f);
	strncpy(tmp, buffer, 2);
	sscanf(tmp, "%x", &len);
	fseek(f, 6, SEEK_CUR);
	fgets(buffer, 1000, f);
	buffer[len*2] = '\0';
	sscanf(buffer, "%x", dest);
	if (*dest == 0x8000) {
		*dest = 0x0;
		printf("Found program for Flash 1\n");
	} else if (*dest == 0xA000) {
		*dest = 0x1;
		printf("Found program for Flash 2\n");
	} else if (*dest == 0x5000) {
		*dest = 0x2;
		printf("Found program for RAM\n");
	} else {
		printf("Unknown MEM Target\n");
		return 0;
	}

	// scan rest lines
	while(1) {
		fseek(f, 1, SEEK_CUR); // :

		fgets(buffer, 2+1, f); // length
		if (feof(f)) break;
		strncpy(tmp, buffer, 2+1);
		sscanf(tmp, "%x", &len);

		fgets(buffer, 4+1, f); // address
		if (feof(f)) break;
		strncpy(tmp, buffer, 4+1);
		sscanf(tmp, "%x", &addr);
		
		diff = (addr - addr_pre) - len_pre;
		if (diff > 0) {
			debug_print("Warning: Prev line at 0x%x shorter then expected, filling %d bytes with 0xff\n", addr_pre, diff);
			result_len+=diff;

			while(result_len >= result_size) {
				result_size += PROGRAM_UPLOAD_PACKET_SIZE;
				if ((*result = (char *)realloc(*result, result_size)) == NULL) {
					perror("realloc");
					return 0;
				}
				memset(*result+(result_size-PROGRAM_UPLOAD_PACKET_SIZE), 0, PROGRAM_UPLOAD_PACKET_SIZE); // set the additional memory to 0
			}
			memset(*result+(result_len-diff), 0xff, diff); // append 0xff
		}

		fseek(f, 2, SEEK_CUR); // record type

		fgets(buffer, 1000, f); // data + checksum
		if (feof(f)) break;
		
		buffer[len*2] = '\0'; // ignore checksum
		result_len+=len;
		while(result_len >= result_size) {
			result_size += PROGRAM_UPLOAD_PACKET_SIZE;
			if ((*result = (char *)realloc(*result, result_size)) == NULL) {
				perror("realloc");
				return 0;
			}
			memset(*result+(result_size-PROGRAM_UPLOAD_PACKET_SIZE), 0, PROGRAM_UPLOAD_PACKET_SIZE); // set the additional memory to 0
		}

		parse_hex_line(buffer, len*2, *result, result_len-len); // store data
		addr_pre = addr;
		len_pre = len;
	}
	fclose(f);

	return result_size;
}


void list_names(FT_HANDLE RBInt) {
	char name[80];

	if ((GetFtProgramName(RBInt, FLASH1, 80, name)) != 0) snprintf(name, 80, "<No Program stored>");
	printf("Flash #1:\t%s\n", name);
	if ((GetFtProgramName(RBInt, FLASH2, 80, name)) != 0) snprintf(name, 80, "<No Program stored>");
	printf("Flash #2:\t%s\n", name);
	if ((GetFtProgramName(RBInt, RAM, 80, name)) != 0) snprintf(name, 80, "<No Program stored>");
	printf("Ram:\t\t%s\n", name);
}


int upload_program(FT_HANDLE RBInt, char *filename, char *name, int autostart, int overwrite_target) {
	char *hexdump = NULL;
	int num;
	int dest;
	char *snewtarget;

	if ((num = read_hex(filename, &hexdump, &dest)) == 0) {
		fprintf(stderr, "Failed to parse file\n");
		return 0;
	}

	if (overwrite_target != -1) {
		if (overwrite_target == 0) snewtarget = "Flash 1";
		else if (overwrite_target == 1) snewtarget = "Flash 2";
		else if (overwrite_target == 2) snewtarget = "RAM";
		else snewtarget = "Unknown";

		printf("Overwriting Destination: Using %s\n", snewtarget);
		dest = overwrite_target;
	}

	if((DownloadFtProgram(RBInt, dest, hexdump, num, autostart, name, name != NULL ? strlen(name) : 0)) != 0) {
		fprintf(stderr, "Sorry: upload failed\n");
		fprintf(stderr, "Please restart Device!\n");
		return 0;
	}

	free(hexdump);
	return 1;
}


// WIP: Need another firmware to analyze
int upload_firmware(FT_HANDLE RBInt, char *filename) {
	char *hexdump;
	int num;

	return 0;

	DownloadFtProgram(RBInt, 0xf0, hexdump, num, 0, "BlockA", strlen("BlockA"));
	// 01.71.00.04: 0x0000da9...0x0010da8
	DownloadFtProgram(RBInt, 0xf1, hexdump, num, 0, "BlockB", strlen("BlockB"));
	// 01.71.00.04: 0x0010da9...0x0020da8
	// 01.71.00.04: final: 0xc0 0x35 0xc7 0x1a 0x75 0x19 0x01 0x00, answer: 0x1
	
	return 0;
}


int delete_program(FT_HANDLE RBInt, int mem) {
	char name[80];

	printf("Deleting program: ");
	if ((GetFtProgramName(RBInt, mem, 80, name)) == 0 && (DeleteFtProgram(RBInt, mem)) == 0) {
		printf("success\n");
		return 1;
	} else {
		printf("No program stored\n");
		return 0;
	}
}


int activate_program(FT_HANDLE RBInt, int mem) {
	char name[80];

	printf("Activating program: ");
	if ((GetFtProgramName(RBInt, mem, 80, name)) == 0 && (SetFtProgramActiv(RBInt, mem)) == 0) {
		printf("success\n");
		return 1;
	} else {
		printf("No program stored\n");
		return 0;
	}
}


int start_program(FT_HANDLE RBInt, int mem) {
	char name[80];

	printf("Starting program: ");
	if ((GetFtProgramName(RBInt, mem, 80, name)) == 0 && (StartFtProgram(RBInt, mem)) == 0) {
		printf("success\n");
		return 1;
	} else {
		printf("No program stored\n");
		return 0;
	}
}


void list_devices() {
	FT_HANDLE RBInt;
	int i;
	char buffer[32];

	printf("List of USB devices:\n");
	for(i=0; i < GetNumFtUsbDevice(); i++) {
		RBInt = GetFtUsbDeviceHandle(i);
		
		if (GetFtDeviceTypeString(RBInt, buffer, 32) == FTLIB_ERR_SUCCESS) {
			printf("#%d:\t\t%s\n", i, buffer);
		} else {
			printf("#%d:\t\t%s\n", i, "Failed/Unknown");
		}
	}
	printf("End of List\n");
}


int mem_name_to_number(char *name) {
	if (strncasecmp(name, "flash1", 6) == 0)
		return 0x0;
	else if (strncasecmp(name, "flash2", 6) == 0)
		return 0x1;
	else if (strncasecmp(name, "ram", 3) == 0)
		return 0x2;
	
	fprintf(stderr, "Unknown Memory\n");
	return -1;
}


void version() {
	char *s = GetLibVersionStrg();
	printf("ftuploader version: %d.%d.%d\n", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
	printf("libft version: %s\n", s);
	free(s);
}


void help(char *progname) {
	printf("Usage: %s [OPTION]...\n", progname);
	printf("-u, --usb-device\t\t Number of Interface to use. Default: %d.\n\t\t\t\t Get the list with --list\n", INTERFACE_NUM_DEFAULT);
	printf("-l, --list\t\t\t List Robo Interfaces\n");
	printf("-n, --names\t\t\t List Saved Programs\n");
	printf("-d, --delete=[FLASH1|FLASH2|RAM] Delete program in flash 1, 2 or ram\n");
	printf("-U, --upload-program=[FILENAME]\t Upload a file to the Interface\n");
	printf("-t, --target=[FLASH1|FLASH2|RAM] Overwrite target of the file given to -U\n");
	printf("-N, --name=NAME\t\t\t Name for program that is uploaded with -U\n");
	printf("-A, --autostart\t\t\t Autostart program uploading with -U\n");
	printf("-a, --activate=[FLASH1|FLASH2|RAM] Activate program in flash 1, 2 or ram\n");
	printf("-S, --serial=[on|off]\t\t Use real serial instead of usual 0001\n");
	printf("-s, --start=[FLASH1|FLASH2|RAM]\t Start program in flash 1, 2 or ram\n");
	printf("-k, --stop\t\t\t Stop running program\n");
	printf("-i, --info\t\t\t Display firmware, serial and RF settings of the interface\n");
	printf("-r, --radio=frequency,callsign\t Set the frequency and call sign for this interface\n\t\t\t\t The frequence is a value between 2 and 80\n\t\t\t\t and the call sign must be between 1 and 8\n");
	printf("-D, --debug\t\t\t Show some debug informations\n");
	printf("-V, --version\t\t\t Print version information\n");
	//printf("-f, --firmware=[FILENAME]\t\t\t Upload firmware to the Interface\n");
	printf("-h, --help\t\t\t This text\n");
	printf("\n"
	"Example:\n"
	"\t%s -U interpreter.hex -N BasicInterpreter\n", progname
	);
	printf("Will upload the file interpreter.hex as name BasicInterpreter to the first Interface found.\n"
	);
}


int main(int argc, char *argv[]) {
	FT_HANDLE RBInt = NULL;
	int c;
	static struct option long_options[] =
	{
		{"usb-device", required_argument, NULL, 'u'},
		{"list", no_argument, NULL, 'l'},
		{"names", no_argument, NULL, 'n'},
		{"delete", required_argument, NULL, 'd'},
		{"upload-program", required_argument, NULL, 'U'},
		{"target", required_argument, NULL, 't'},
		{"name", required_argument, NULL, 'N'},
		{"autostart", no_argument, NULL, 'A'},
		{"activate", required_argument, NULL, 'a'},
		{"start", required_argument, NULL, 's'},
		{"serial", required_argument, NULL, 'S'},
		{"stop", no_argument, NULL, 'k'},
		{"info", no_argument, NULL, 'i'},
		{"radio", required_argument, NULL, 'r'},
		{"debug", no_argument, NULL, 'D'},
		{"version", no_argument, NULL, 'V'},
		{"firmware", required_argument, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0}
	};
	int device_num = INTERFACE_NUM_DEFAULT;
	int option_index;
	int mem;
	char *optstring = "u:lnd:N:AU:a:s:S:kiDVf:ht:r:";
	int prg_running;
	char *name = NULL;
	int autostart = 0;
	char *s;
	int overwrite_target=-1;
	long int frequency=0, callsign=0;

	if(argc < 2) {
		help(argv[0]);
		exit(0);
	}

	InitFtUsbDeviceList();

	// scan for select usb device and help in optionlist first
	while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
		switch(c)
		{
			case 'u':
				device_num = atoi(optarg);
				break;
			case 'N':
				name = optarg;
				break;
			case 'A':
				autostart = 1;
				break;
			case 'l':
				list_devices();
				return 0;
			case 'D':
				g_debug = 1;
				break;
			case 'V':
				version();
				return 0;
			case 'h':
				help(argv[0]);
				return 0;
			case 't':
				overwrite_target = mem_name_to_number(optarg);
				if (overwrite_target == -1) fprintf(stderr, "Bad destination to write to. Using default\n");
				break;
		}
	}

	RBInt = GetFtUsbDeviceHandle(device_num);
	if (RBInt == NULL) {
		fprintf(stderr, "Error opening device #%d\n", device_num);
		exit(1);
	}
	OpenFtUsbDevice(RBInt);
	
	if (RBInt->type == FT_ROBO_IF_USB || RBInt->type == FT_ROBO_IF_OVER_RF) {
		if (GetFtStatus(RBInt, &prg_running)) {
			printf("Warning: Program in ");
			switch(prg_running) {
				case 0x0:	printf("Flash 1");
						break;
				case 0x1:	printf("Flash 2");
						break;
				case 0x2:	printf("RAM");
						break;
				default:	printf("Unknown Memory");
						break;
			}
			printf(" running!\n");
		}
	}

	// read options
	optind = 1; // reset option list
	while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
		switch(c)
		{
			case 0:
				printf ("Option %s", long_options[option_index].name);
				if (optarg) printf (" with argument %s", optarg);
				printf("\n");
				break;
			case 'u': // already handled
				break;
			case 'l': // already handled
				break;
			case 'n':
				list_names(RBInt);
				break;
			case 'd':
				mem = mem_name_to_number(optarg);
				if (mem != -1) delete_program(RBInt, mem);
				break;
			case 'U':
				if ((upload_program(RBInt, optarg, name, autostart, overwrite_target))) printf("Upload done\n");
				break;
			case 'N': // already handled
			case 'A':
				break;
			case 'a':
				mem = mem_name_to_number(optarg);
				if (mem != -1) activate_program(RBInt, mem);
				break;
			case 's':
				mem = mem_name_to_number(optarg);
				if (mem != -1) start_program(RBInt, mem);
				break;
			case 'S':
				printf("Turning real serial ");
				if (strncasecmp(optarg, "on", 2) == 0) {
					printf("on:\n");
					if ((SetRealSerial(RBInt, 1)) != 0) {
						printf("failed\n");
						break;
					}
					printf("success\n");
				} else {
					printf("off:\n");
					if ((SetRealSerial(RBInt, 0)) != 0) {
						printf("failed\n");
						break;
					}
					printf("success\n");
				}
				printf("Please restart the device now\n");
				break;
			case 'k':
				printf("Stopping program ");
				if ((StopFtProgram(RBInt)) == 0) printf("success\n");
				else printf("failed\n");
				break;
			case 'i':
				s = GetFtFirmwareStrg(RBInt);
				printf("Firmware:\t%s\n", s);
				free(s);
				s = GetFtSerialNrStrg(RBInt);
				printf("Serial:\t\t%s\n", s);
				free(s);
				GetRFMode(RBInt, &frequency, &callsign);
				printf("RF frequency:\t\t%d\n", frequency);
				printf("RF call sign:\t\t%d\n", callsign);
				break;
			case 'f':
				upload_firmware(RBInt, optarg);
				break;
			case 'r':
				{
				char *delim = ",";
				char str[10];
				strncpy(str, optarg, 10);

				printf("Setting Frequency and call sign:\n");

				// frequency
				s = strtok(str, delim);
				frequency = atoi(s);

				// callsign
				callsign = 0;
				s = strtok(NULL, delim);
				// no callsign given might be ok for RF module
				if (s == NULL) {
					if (RBInt->type != FT_ROBO_RF_DATA_LINK) {
						fprintf(stderr, "Missing call sign\n");
						break;
					}
				} else {
					callsign = atoi(s);
				}

				if (SetRFMode(RBInt, frequency, callsign) == FTLIB_ERR_SUCCESS)
					printf("success!\n");
				else
					printf("failed!\n");
				}
				break;
			case 'D': // already handled
			case 't':
			case 'h':
				break;
			default:
				help(argv[0]);
		}
	}

	if(RBInt) CloseFtDevice(RBInt);

	return 0;
}

