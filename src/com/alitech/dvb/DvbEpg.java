package com.alitech.dvb;

public class DvbEpg {
	final static int  PRESENT_EVENT = 0;
	final static int  FOLLOWING_EVENT = 1;
	final static int  SCHEDULE_EVENT = 2;	
	
	public static void callback(int type, Object param) {		
		
		switch (type)
		{
		case PRESENT_EVENT:
		case FOLLOWING_EVENT:			
			//TODO: send pf update msg
			break;
		case SCHEDULE_EVENT:
			//TODO: send sch update msg
			break;
		default:
			// unknown epg event type
		}
	}	

	public static String getEndTime(String startTime) {
		String endTime = null;
		
		//TODO: get endTime
		
		return endTime;
	}

	private static native void initIDs();
	
	public native static DvbTime getStreamTime(int day_offset);

	public native int setActiveService(DvbChannelNode[] channels);
	
	public native int delService(DvbChannelNode channel);
		
	public native DvbEpgEvent getPresentEvent(DvbChannelNode channel, boolean forceUpdate);

	public native DvbEpgEvent getFollowingEvent(DvbChannelNode channel, boolean forceUpdate);

	public native int loadScheduleEvent(DvbChannelNode channel, DvbTime startTime, DvbTime endTime, boolean forceUpdate);

	public native DvbEpgEvent getScheduleEvent(int index);
	
	static {
		initIDs();
	}
}
