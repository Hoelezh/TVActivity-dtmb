package com.nmp.dvbplayer.common;

import com.alitech.dvb.DvbProperty;
import com.alitech.dvb.DvbSyetemSetting;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;
import android.util.Log;

public class TVSettingBrightness extends TVSettingItem {
	private String mTitle;
	private int mBrightness = -1;
	public TVSettingBrightness(Context ctx) {
		super(ctx);
		
		Resources res = ctx.getResources();
		this.mTitle = res.getString(R.string.tv_setting_brightness);
		for (int i = 0; i < 10; ++i) {
			this.addOption(String.valueOf(i));
		}
		mBrightness = DvbProperty.get_int("persist.sys.brightness_osd",50);
		Log.i("TVSettingBrightness", "persist.sys.brightness_video:"+mBrightness);
		int idx_tol;
		
		if(mBrightness < 0)
			idx_tol =0;
		else{
			idx_tol = mBrightness /10;
			if(idx_tol > 9) idx_tol =9;
		}
		this.setDefaultIndex(idx_tol);
	}

	@Override
	public String getTitle() {
		return this.mTitle;
	}

	@Override
	public void apply() {
		int val;
		this.save();
		val = this.getIndex() * 10;
		DvbProperty.set("persist.sys.brightness_osd", Integer.toString(val));
		DvbProperty.set("persist.sys.brightness_video", Integer.toString(val));
		// FIXME do the actual work!
		DvbSyetemSetting.setBrightness(val);
		Log.i(" TVSettingBrightness", "set persist.sys.brightness_video:"+val);
	}

}
