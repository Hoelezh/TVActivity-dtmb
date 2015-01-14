package com.alitech.dvb;

public class DvbPlayer {
	
	public int play(String source, boolean blkScrn) {
		DvbChannelNode node = DvbChannelNode.fromUrl(source);
		return start(node, blkScrn);
	}
	
	public static native int start(DvbChannelNode node, boolean blkScrn);

	public static native int stop(boolean blkScrn);

	public static native int pauseVideo();

	public static native int resumeVideo();

	public static native int switchAudioTrack(int audioTrackIdx);

	public static native int switchAudioChannel(int audioChannel);
	
	public static native int configNim(int nim);
	
	public static native int showlogo(String path);
	
	public static native int setPos(int l,int t,int r, int b);
	
	public static native int GetVol();
	
	public static native int SetVol(int vol);
	
	public static native int GetVolMute();
	
	public static native int SetVolMute(int mute);
	
	static {
		System.loadLibrary("adr_hld");
		System.loadLibrary("ams");
		System.loadLibrary("dvbagent");
	}
}
