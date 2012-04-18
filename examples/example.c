/** @file */

#include <stdio.h>
#include <usb.h>
#include "roboint.h"

/**
 * \brief real word example
 *
 * This example will start running Motor 1 with low speed to the right, wait 2 seconds
 * and then max speed to the left until the input #1 is high
 *
 */
int main() {
	FT_HANDLE hFt = NULL;
	FT_TRANSFER_AREA *transfer_area = NULL;

	// Get List of USB devices
	InitFtUsbDeviceList();

	// Get Number of usb devices
	printf("Found %d ft USB devices\n", GetNumFtUsbDevice());

	// Get handle on a device
	hFt = GetFtUsbDeviceHandle(0);

	// Open connection
	OpenFtUsbDevice(hFt);

	StartFtTransferArea(hFt, NULL);
	transfer_area = GetFtTransferAreaAddress(hFt);
	if (transfer_area) {
		transfer_area->MPWM_Main[0] = 7; // PWM Motor 1
		transfer_area->MPWM_Main[1] = 1;
		transfer_area->M_Main = 2; // Motor 1 right
		sleep(2);
		transfer_area->M_Main = 1; // Motor 1 left
		do {
			printf("End 1: %d\n", transfer_area->E_Main & 0x1); // Digital Input 1
			usleep(10000);
		} while(!(transfer_area->E_Main & 0x1)); // stop when end = 1
		printf("End 1: %d\n", transfer_area->E_Main & 0x1); // Digital Input 1
		transfer_area->M_Main = 0;
	}
	StopFtTransferArea(hFt);
	
	// Close connection
	CloseFtDevice(hFt);

	return 0;
}

