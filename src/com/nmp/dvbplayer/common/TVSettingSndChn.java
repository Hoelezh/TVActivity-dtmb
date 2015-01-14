package com.nmp.dvbplayer.common;

import com.alitech.dvb.DvbSyetemSetting;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;
import android.util.Log;

public class TVSettingSndChn extends TVSettingItem {
	private String mTitle;
	private static String LOGTAG = "SoundChannel";
	public TVSettingSndChn(Context ctx) {
		super(ctx);
		
		Resources res = ctx.getResources();
		this.mTitle = res.getString(R.string.tv_setting_snd);
		this.addOption(res.getString(R.string.tv_setting_snd_0));
		this.addOption(res.getString(R.string.tv_setting_snd_1));
		this.addOption(res.getString(R.string.tv_setting_snd_2));
	}

	@Override
	public String getTitle() {
		return this.mTitle;
	}
      
	@Override
	public void apply() {
		this.save();
		// FIXME do the actual work!
		DvbSyetemSetting.setSndChn(this.getIndex());
	}	
	
	public  int getSndChn() {
		int newsndChn;
		newsndChn = super.loadIndex();
		if(0==newsndChn){
			Log.i(LOGTAG, "立体声newsndChn: " + newsndChn);
			newsndChn =2;
		}
		else if(2==newsndChn){
			Log.i(LOGTAG, "右声道newsndChn: " + newsndChn);
			newsndChn = 1;
		}
		else {
			Log.i(LOGTAG, "左声道newsndChn: " + newsndChn);
			newsndChn =0;
		}
		
		return newsndChn;
	}

}
