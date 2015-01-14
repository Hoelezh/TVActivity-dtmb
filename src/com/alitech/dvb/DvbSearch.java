package com.alitech.dvb;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class DvbSearch {
	public static final String TAG="DvbSearch";
	
	public final static int SEARCH_PROGRESS = 0x0;
	public final static int SEARCH_TP_TUNING = 0x1;
	public final static int SEARCH_PROGRAM_ADDED = 0x2;
	public final static int SEARCH_TP_FULL = 0x3;
	public final static int SEARCH_PROGRAM_FULL = 0x4;
	public final static int SEARCH_COMPLETE = 0x5;
	public final static int SEARCH_STOP = 0x6;
	
	public Handler h = null;
	
	public void set_handler(Handler mhandler)
	{
		h = mhandler;
	}
	
	public void callback(int type, Object param)
	{
		switch (type)
		{
		case SEARCH_PROGRESS:
			//TODO: send msg MSG_SCAN_PROGRESS
			int progress = (Integer)param;
			Log.d(TAG, "SEARCH_PROGRESS"+progress);
			break;
		case SEARCH_TP_TUNING:
			//TODO: send msg MSG_SCAN_TP_TUNING
			DvbChannelNode.DvbFrontend frontend = (DvbChannelNode.DvbFrontend)param;
			Log.d(TAG, "SEARCH_TP_TUNING");
			Log.d(TAG,"ft_type"+frontend.getType());
			Log.d(TAG,"qam"+frontend.getQam());
			Log.d(TAG,"frq"+frontend.getFrequency());
			Log.d(TAG,"sym"+frontend.getSymbolRate());						
			break;
		case SEARCH_PROGRAM_ADDED:
			//TODO: send msg MSG_SCAN_PROGRAM_ADDED
			Log.d(TAG, "param = " + param);
			//DvbChannelNode channel = (DvbChannelNode)param;			
			//Log.d(TAG, "SEARCH_PROGRAM_ADDED");
			//DvbChannelNode.printChannelNode(channel);
			break;
		case SEARCH_TP_FULL:
			//TODO:
			Log.d(TAG, "SEARCH_TP_FULL");

			break;
		case SEARCH_PROGRAM_FULL:
			//TODO:
			Log.d(TAG, "SEARCH_PROGRAM_FULL");

			break;
		case SEARCH_COMPLETE:
			//TODO:
			Log.d(TAG, "SEARCH_COMPLETE");

			break;
		case SEARCH_STOP:
			//TODO:
			Log.d(TAG, "SEARCH_STOP");

			break;
		default:
		}
		
		if(null != h)
		{
			Message msg = new Message();
	        msg.what = 0x123;
	        msg.arg1 = type;
	        msg.obj = param;
	        h.sendMessage(msg);
		}
	}
	
	public int startSearch(DvbSearchParam param) {
		DvbChannelList.DvbChannels.clear();
		return this.start(param);
	}

	private static native void initIDs();

	public native int start(DvbSearchParam param);
	
	public native int stop();
	
	static {
		System.loadLibrary("adr_hld");
		System.loadLibrary("ams");
		System.loadLibrary("dvbagent");
	}	
	
}
