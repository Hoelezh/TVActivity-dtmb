package com.alitech.dvb;

public class DvbProperty{

	public static native String getSS(String key, String def);
	public static native int get_int(String key, int def);
	public static native void set(String key,String val);
	
	static {
		System.loadLibrary("cutils");
		System.loadLibrary("dvbagent");
	}
}