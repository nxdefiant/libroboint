import com.sun.jna.*;

public interface FTLibrary extends Library {
	FTLibrary INSTANCE = (FTLibrary)Native.loadLibrary("ft", FTLibrary.class);
	
	int GetLibVersion();
	int InitFtUsbDeviceList();
	int GetNumFtUsbDevice();
	FT_HANDLE GetFtUsbDeviceHandle(byte Num);
	FT_HANDLE GetFtUsbDeviceHandleSerialNr(int dwSN, int dwTyp);	
	FT_HANDLE OpenFtCommDevice(String sDevice, int dwTyp, int dwZyklus);
	int OpenFtUsbDevice(FT_HANDLE hft);
	int CloseFtDevice(FT_HANDLE hft);
	int StartFtTransferArea(FT_HANDLE hFt, int ignored);
	FT_TRANSFER_AREA GetFtTransferAreaAddress(FT_HANDLE hFt);
	int StopFtTransferArea(FT_HANDLE hFt);
	int StartFtProgram(FT_HANDLE hFt, int dwMemBlock);
	int StopFtProgram(FT_HANDLE hFt);
	String GetFtFirmwareStrg(FT_HANDLE hFt);
	String GetFtSerialNrStrg(FT_HANDLE hFt);
}
