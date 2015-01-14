package com.alitech.dvb;

public class DvbSyetemSetting {
	
	private static native void initIDs();
	
	public static native boolean setAspect(int value);
	
	public static native boolean setBrightness(int value);
	
	public static native boolean setSndChn(int value);
}
