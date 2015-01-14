package com.alitech.dvb;

public class DvbSystem {
	
	public DvbSystem() {
		init();
	}
	
	// init devices and modules
	private static native int init();
	
	// uninit devices and modules
	public static native int exit();
	
	// load default
	public static native int loadDefault();

		// init devices and modules
	public static native int getboardType();
	
	// init devices and modules
	public static native int getTunerLock();
	
	// init devices and modules
	public static native int getTunerSNR();
	
	// init devices and modules
	public static native int getTunerAGC();
	
	// init devices and modules
	public static native int LockFreq(int satID, int tpID);
	
	public static native int PanelShow(String showChar, int len);
	
	static {
		System.loadLibrary("adr_hld");
		System.loadLibrary("ams");
		System.loadLibrary("dvbagent");
	}
}
