package com.alitech.dvb;

public class DVBSatellite {

	
	private static native void initIDs();	
	
	// load channels from DB by group(PARAM+CHAN_GROUP+CHAN_MODE)
	public static native DVBSatelliteNode[] loadSatelliteNodes();
	
	// save node to DB
	public static native int updateSatellite(DVBSatelliteNode node);
	
	public static native DvbTpNode[] loadTpNodes(int sat_id);
	
	public static native int updateTpNode(DvbTpNode node);
	
	public static native boolean deleteSatellite(int sat_id);
	
	public static native boolean deleteTpNode(int sat_id, int tp_id);
	
	static {
		System.loadLibrary("adr_hld");
		System.loadLibrary("ams");
		System.loadLibrary("dvbagent");
	}
}
