package com.alitech.dvb;

import com.nmp.dvbplayer.tv.data.EpgItem;

import android.util.Log;

public class DvbEpgEvent extends EpgItem {	
	public static final String TAG="DvbEpgEvent";
	
	final static int  NIBBLE_MOVIE = 0x10;
	final static int  NIBBLE_NEWS = 0x20;
	final static int  NIBBLE_SHOW = 0x30;
	final static int  NIBBLE_SPORT = 0x40;
	final static int  NIBBLE_CHILDREN = 0x50;
	final static int  NIBBLE_MUSIC = 0x60;
	final static int  NIBBLE_ARTS = 0x70;
	final static int  NIBBLE_SOCIAL = 0x80;
	final static int  NIBBLE_EDU = 0x90;
	final static int  NIBBLE_LEISURE = 0xA0;
	final static int  NIBBLE_SPECIAL = 0xB0;

	DvbTime mStart;
	DvbTime mEnd;
	int index;
	
	public DvbEpgEvent(int index, String title) {
		//super(""+index);
		super(title);
	}
	
	public void setEpgNibble(int level) {
		EpgType epgType;
		
		switch (level & 0xF0) {
		case NIBBLE_MOVIE:
			epgType = EpgType.Movie;
			break;
		case NIBBLE_NEWS:
			epgType = EpgType.News;
			break;
		case NIBBLE_SPORT:
			epgType = EpgType.Sport;
			break;
		default:
			epgType = EpgType.Unknown;
		}
		
		super.setEpgType(epgType);
	}	
	
	public void setStartDvbTime(DvbTime time) {
		String timeStr = String.format("%02d:%02d", time.mHour, time.mMin);
		
		super.setStartTime(timeStr);
	}
	
	public void setEndDvbTime(DvbTime time) {
		String timeStr = String.format("%02d:%02d", time.mHour, time.mMin);
		
		super.setEndTime(timeStr);
	}	
	
	public void setEventBrief(String brief){
		
		super.setBrief(brief);
	}
	
	public void setEventDetail(String detail){
		
		super.setDetail(detail);
	}
	
	public void setEventLang(String lang){
		;
	}
	
	public static void printEpgEvent(DvbEpgEvent event) {
		Log.d(TAG, "start list node "+ event.getTitle());
		Log.d(TAG, "start time:"+ event.getStartTime());
		Log.d(TAG, "end time:"+ event.getEndTime());
		Log.d(TAG, "type:"+ event.getEpgType());
		
		
		Log.d(TAG, "Deatail:" + event.getDetail());
		

	}	
}
