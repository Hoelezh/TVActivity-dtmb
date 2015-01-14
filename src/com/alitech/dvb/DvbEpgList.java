package com.alitech.dvb;

import android.content.Context;
import android.util.Log;

import com.nmp.dvbplayer.tv.data.EpgItem;
import com.nmp.dvbplayer.tv.data.EpgList;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.alitech.dvb.DvbTime;
import com.nmp.dvbplayer.tv.TVUtility.TimeUtil;

public class DvbEpgList implements EpgList {
	private static final String TAG = "DvbEpgList";
	
	static DvbEpg cDvbEpg = null;

	public DvbEpgList(Context ctx) {
		;
	}
	
	@Override
	public LangCode[] getLanguages() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public EpgItem[] getEpg(int time, TVChannel channel, LangCode code) {
		// TODO Auto-generated method stub
		DvbTime stream_time;
		stream_time = cDvbEpg.getStreamTime(time);

		if(stream_time == null)
		{
			String data_now = new TimeUtil().getDate(time);
			String[] arr = data_now.split("-");
			int year = Integer.parseInt(arr[0]);
			int month = Integer.parseInt(arr[1]);
			int day = Integer.parseInt(arr[2]);
			if(time == 0)
			{
				String time_2 = new TimeUtil().getCurrentTime();
				int hour = new TimeUtil().getHour(time_2);
				int min = new TimeUtil().getMinute(time_2);
				stream_time = new DvbTime(year, month, day, hour, min, 0);
			}
			else
			{
				stream_time = new DvbTime(year, month, day, 0, 0, 0);
			}
		}
			
		DvbChannelNode[] channels = new DvbChannelNode[1];

		//DvbTime dvbTime_s = new DvbTime(year, month, day, 0, 0, 0);
		DvbTime dvbTime_e = new DvbTime(stream_time.mYear, stream_time.mMonth, stream_time.mDay, 23, 59, 59);
		//DvbChannelNode dvbChannel = new DvbChannelNode(1024, "test channel","1");
		channels[0] = (DvbChannelNode)channel;
		//DvbChannelNode.printChannelNode(channels[0]);
		//cDvbEpg.setActiveService(channels);
		int event_cnt = cDvbEpg.loadScheduleEvent((DvbChannelNode)channel, stream_time,
				dvbTime_e, false);
		if (event_cnt > 0) {
			//event_cnt = 2;
			EpgItem[] epgItems = new EpgItem[event_cnt];
			EpgItem epg_tmp;
			int index = 0;
			for (int i = 0; i < event_cnt; i++) {
				epg_tmp = cDvbEpg.getScheduleEvent(i);
				if(epg_tmp != null)
				{
					epgItems[index] = epg_tmp;
					index++;
				}
			}
			return epgItems;
		} else
			return null;

	}

	@Override
	public EpgItem[] getCurrentEpg(TVChannel channel, LangCode code) {
		// TODO Auto-generated method stub
		DvbChannelNode[] channels = new DvbChannelNode[1];
		channels[0] = (DvbChannelNode)channel;
		//DvbChannelNode.printChannelNode(channels[0]);
		//cDvbEpg.setActiveService(channels);
		
		EpgItem presentEvent = cDvbEpg.getPresentEvent(channels[0], true);
		EpgItem followingEvent = cDvbEpg.getFollowingEvent(channels[0], false);
		
		if ((presentEvent != null) && (followingEvent != null)) {

			EpgItem[] epgItems = new EpgItem[2];
			epgItems[0] = presentEvent;
			epgItems[1] = followingEvent;
			return epgItems;
		} else
			return null;

	}

	static {
		Log.d(TAG, "static++++++++++++++++++++++");
		cDvbEpg = new DvbEpg();
		Log.d(TAG, "static----------------------");
	}

}
