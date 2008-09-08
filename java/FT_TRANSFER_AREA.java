import com.sun.jna.*;

public class FT_TRANSFER_AREA extends Structure {
	public volatile byte E_Main;
	public volatile byte E_Sub1;
	public volatile byte E_Sub2;
	public volatile byte E_Sub3;
	public volatile byte[] rsvd1 = new byte[8];
	public volatile byte Distance;
	public volatile byte rsvd2;
	public volatile byte IRKeys;
	public volatile byte res_1;
	public volatile short AX;
	public volatile short AY;
	public volatile short A1;
	public volatile short A2;
	public volatile short AZ;
	public volatile short AV;
	public volatile short D1;
	public volatile short D2;
	public volatile short AXS1;
	public volatile short AXS2;
	public volatile short AXS3;
	public volatile short DS1;
	public volatile short DS2;
	public volatile short ZE;
	public volatile byte[] rsvd3 = new byte[4];
	public volatile short Timer1ms;
	public volatile short Timer10ms;
	public volatile short Timer100ms;
	public volatile short Timer1s;
	public volatile short Timer10s;
	public volatile short Timer1min;
	public volatile short res_bF;
	public volatile byte res_bT;
	public volatile byte[] resvd4 = new byte[1];
	public volatile byte M_Main;
	
	/*
	("M_Sub1", c_ubyte),
	("M_Sub2", c_ubyte),
	("M_Sub3", c_ubyte),
	("rsvd5", c_ubyte*4),
	("MES_Main", c_ubyte),
	("MES_Sub1", c_ubyte),
	("MES_Sub2", c_ubyte),
	("MES_Sub3", c_ubyte),
	("rsvd6", c_ubyte*1),
	("reserverd_l1", c_ubyte),
	("reserverd_l2", c_ubyte),
	("reserverd_l3", c_ubyte),
	("MPWM_Main", c_ubyte*8),
	("MPWM_Sub1", c_ubyte*8),
	("MPWM_Sub2", c_ubyte*8),
	("MPWM_Sub3", c_ubyte*8),
	("rsvd7", c_ubyte*32),
	("A1S1", c_ushort),
	("A1S2", c_ushort),
	("A1S3", c_ushort),
	("AVS1", c_ushort),
	("AVS2", c_ushort),
	("AVS3", c_ushort),
	("rsvd8", c_ubyte*4),
	("AX_R", c_ushort),
	("AY_R", c_ushort),
	("AXS1_R", c_ushort),
	("AXS2_R", c_ushort),
	("AXS3_R", c_ushort),
	("rsvd10", c_ubyte*54),
	("Mode", c_ubyte),
	("MPWM_Update", c_ubyte),
	("TransferAktiv", c_ubyte),
	("rsvd11", c_ubyte*3),
	("BudModules", c_ubyte),
	("SlotModule1", c_ubyte),
	("SlotModule2", c_ubyte),
	("rsvd12", c_ubyte*7),
	("ChangeEg", c_ubyte),
	("ChangeAn", c_ubyte),
	("ChangeIr", c_ubyte),
	("rsvd13", c_ubyte*13),
	("E16_Main", c_ubyte*8),
	("E16_Sub1", c_ubyte*8),
	("E16_Sub2", c_ubyte*8),
	("E16_Sub3", c_ubyte*8),
	("Distance16", c_ushort*2),
	("rsvd14", c_ubyte*12),
	("IRKeys16", c_ushort*11),
	("rsvd15", c_ubyte*15),
	("IRKeys16Code1", c_ushort*11),
	("rsvd16", c_ubyte*10),
	("IRKeys16Code2", c_ushort*11),
	("rsvd17", c_ubyte*10),
	("RfStatus", c_ushort),
	("RfPower", c_ushort),
	("RfError", c_ushort),
	("MsgNumInBuffer", c_ushort),
	("RfModulNr", c_ushort),
	("rsvd19", c_ubyte*2),
	("dwTc", c_long),
	("rsvd20", c_ubyte*64),
	*/
}
