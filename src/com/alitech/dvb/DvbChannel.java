package com.alitech.dvb;

public class DvbChannel {
	public final static int CHAN_MODE_MASK = 0x7F000000;
	public final static int CHAN_GROUP_MASK = 0x00FF0000;
	public final static int CHAN_GROUP_PARAM_MASK = 0x0000FFFF;
	
	public final static int CHAN_GROUP_ALL = 0x00000000;  // TVRADIO+NVOD+DATA
	public final static int CHAN_GROUP_TVRADIO = 0x00010000;
	public final static int CHAN_GROUP_NVOD = 0x00020000;
	public final static int CHAN_GROUP_DATA = 0x00030000;
	public final static int CHAN_GROUP_LOCAL = 0x00040000;
	public final static int CHAN_GROUP_FAV = 0x00050000;
	public final static int CHAN_GROUP_FAVALL = 0x00060000;    
	
	public final static int CHAN_MODE_RADIO = 0x00000000;
	public final static int CHAN_MODE_TV = 0x01000000;
	public final static int CHAN_MODE_TVRADIO = 0x02000000; 
	
	private static native void initIDs();	
	
	// load channels from DB by group(PARAM+CHAN_GROUP+CHAN_MODE)
	public static native DvbChannelNode[] loadChannels(int group);
	
	// save node to DB
	public static native int updateChannel(DvbChannelNode node);
	
	static {
		System.loadLibrary("adr_hld");
		System.loadLibrary("ams");
		System.loadLibrary("dvbagent");
	}
}
