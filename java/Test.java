import java.lang.*;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		System.out.println("Begin");
		FTLibrary lib = FTLibrary.INSTANCE;
	
		// FT_HANDLE handle = lib.OpenFtCommDevice("/dev/ttyS3", 20, 10);
		
 		lib.InitFtUsbDeviceList();
		FT_HANDLE handle = lib.GetFtUsbDeviceHandle((new Integer(0)).byteValue());
		lib.OpenFtUsbDevice(handle);
		
		lib.StartFtTransferArea(handle, 0);
		
		FT_TRANSFER_AREA area = lib.GetFtTransferAreaAddress(handle);
		System.out.println("Transfer Aktiv:" + area.TransferAktiv);
		area.MPWM_Main[0] = 7; // PWM Motor 1
		area.MPWM_Main[1] = 6;
		area.MPWM_Main[2] = 7; // PWM Motor 2
		area.writeField("MPWM_Main");
		// area.M_Main = 1;
		area.writeField("M_Main", (byte)1); // Motor 1 right
		Thread.sleep(500);
		// area.M_Main = 2;
		area.writeField("M_Main", (byte)6); // Motor 1 & 2 left
		do {
			// area = lib.GetFtTransferAreaAddress(handle);
			System.out.println(area.readField("E_Main"));
			Thread.sleep(100);
			area.readField("E_Main"); // read E_Main from Hardware
		} while(area.E_Main != (byte)1); // stop when Digital Input 1 is shorted
		// area.M_Main = 0;
		area.writeField("M_Main", (byte)0);
		
		lib.StopFtTransferArea(handle);
		lib.CloseFtDevice(handle);
		System.out.println("End");
	}

}
