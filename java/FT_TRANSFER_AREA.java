import com.sun.jna.*;

import java.util.Arrays;
import java.util.List;

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
	public byte M_Main;
	public byte M_Sub1;
	public byte M_Sub2;
	public byte M_Sub3;
	public volatile byte[] rsvd5 = new byte[4];
	public volatile byte MES_Main;
	public volatile byte MES_Sub1;
	public volatile byte MES_Sub2;
	public volatile byte MES_Sub3;
	public volatile byte[] rsvd6 = new byte[1];
	public volatile byte reserverd_l1;
	public volatile byte reserverd_l2;
	public volatile byte reserverd_l3;
	public byte[] MPWM_Main = new byte[8];
	public byte[] MPWM_Sub1 = new byte[8];
	public byte[] MPWM_Sub2 = new byte[8];
	public byte[] MPWM_Sub3 = new byte[8];
	public volatile byte[] rsvd7 = new byte[32];
	public volatile short A1S1;
	public volatile short A1S2;
	public volatile short A1S3;
	public volatile short AVS1;
	public volatile short AVS2;
	public volatile short AVS3;
	public volatile byte[] rsvd8 = new byte[4];
	public volatile short AX_R;
	public volatile short AY_R;
	public volatile short AXS1_R;
	public volatile short AXS2_R;
	public volatile short AXS3_R;
	public volatile byte[] rsvd10 = new byte[54];
	public volatile byte Mode;
	public volatile byte MPWM_Update;
	public volatile byte TransferAktiv;
	public volatile byte[] rsvd11 = new byte[3];
	public volatile byte BudModules;
	public volatile byte SlotModule1;
	public volatile byte SlotModule2;
	public volatile byte[] rsvd12 = new byte[7];
	public volatile byte ChangeEg;
	public volatile byte ChangeAn;
	public volatile byte ChangeIr;
	public volatile byte[] rsvd13 = new byte[13];
	public volatile byte[] E16_Main = new byte[8];
	public volatile byte[] E16_Sub1 = new byte[8];
	public volatile byte[] E16_Sub2 = new byte[8];
	public volatile byte[] E16_Sub3 = new byte[8];
	public volatile short[] Distance16 = new short[2];
	public volatile byte[] rsvd14 = new byte[12];
	public volatile short[] IRKeys16 = new short[11];
	public volatile byte[] rsvd15 = new byte[15];
	public volatile short[] IRKeys16Code1 = new short[11];
	public volatile byte[] rsvd16 = new byte[10];
	public volatile short[] IRKeys16Code2 = new short[11];
	public volatile byte[] rsvd17 = new byte[10];
	public volatile short RfStatus;
	public volatile short RfPower;
	public volatile short RfError;
	public volatile short MsgNumInBuffer;
	public volatile short RfModulNr;
	public volatile byte[] rsvd19 = new byte[2];
	public volatile NativeLong dwTc;
	public volatile byte[] rsvd20 = new byte[64];

    @Override
    protected List getFieldOrder() {
        return Arrays.asList(
                "E_Main",
                "E_Sub1",
                "E_Sub2",
                "E_Sub3",
                "rsvd1",
                "Distance",
                "rsvd2",
                "IRKeys",
                "res_1",
                "AX",
                "AY",
                "A1",
                "A2",
                "AZ",
                "AV",
                "D1",
                "D2",
                "AXS1",
                "AXS2",
                "AXS3",
                "DS1",
                "DS2",
                "ZE",
                "rsvd3",
                "Timer1ms",
                "Timer10ms",
                "Timer100ms",
                "Timer1s",
                "Timer10s",
                "Timer1min",
                "res_bF",
                "res_bT",
                "resvd4",
                "M_Main",
                "M_Sub1",
                "M_Sub2",
                "M_Sub3",
                "rsvd5",
                "MES_Main",
                "MES_Sub1",
                "MES_Sub2",
                "MES_Sub3",
                "rsvd6",
                "reserverd_l1",
                "reserverd_l2",
                "reserverd_l3",
                "MPWM_Main",
                "MPWM_Sub1",
                "MPWM_Sub2",
                "MPWM_Sub3",
                "rsvd7",
                "A1S1",
                "A1S2",
                "A1S3",
                "AVS1",
                "AVS2",
                "AVS3",
                "rsvd8",
                "AX_R",
                "AY_R",
                "AXS1_R",
                "AXS2_R",
                "AXS3_R",
                "rsvd10",
                "Mode",
                "MPWM_Update",
                "TransferAktiv",
                "rsvd11",
                "BudModules",
                "SlotModule1",
                "SlotModule2",
                "rsvd12",
                "ChangeEg",
                "ChangeAn",
                "ChangeIr",
                "rsvd13",
                "E16_Main",
                "E16_Sub1",
                "E16_Sub2",
                "E16_Sub3",
                "Distance16",
                "rsvd14",
                "IRKeys16",
                "rsvd15",
                "IRKeys16Code1",
                "rsvd16",
                "IRKeys16Code2",
                "rsvd17",
                "RfStatus",
                "RfPower",
                "RfError",
                "MsgNumInBuffer",
                "RfModulNr",
                "rsvd19",
                "dwTc",
                "rsvd20");

    }
}
