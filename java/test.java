

public class test {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		System.out.println("Begin");
		FTLibrary lib = FTLibrary.INSTANCE;
		
		lib.InitFtUsbDeviceList();
		FT_HANDLE handle = lib.GetFtUsbDeviceHandle((new Integer(0)).byteValue());
		lib.OpenFtUsbDevice(handle);
		
		lib.StartFtTransferArea(handle, 0);
		
		FT_TRANSFER_AREA area = lib.GetFtTransferAreaAddress(handle);
		area.M_Main = 1;
		for(int i=0; i < 10; i++) {
			area = lib.GetFtTransferAreaAddress(handle);
			System.out.println(area.E_Main);
			Thread.sleep(1000);
		}
		area.M_Main = 0;
		
		lib.StopFtTransferArea(handle);
		lib.CloseFtDevice(handle);
		System.out.println("End");
	}

}
