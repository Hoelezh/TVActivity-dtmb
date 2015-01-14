package com.nmp.dvbplayer.common;

import com.alitech.dvb.DvbSyetemSetting;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;

public class TVSettingAspect extends TVSettingItem {
	private String mTitle;	
	public TVSettingAspect(Context ctx) {
		super(ctx);
		Resources res = ctx.getResources();
		this.mTitle = res.getString(R.string.tv_setting_aspect);		
		this.addOption(res.getString(R.string.tv_setting_aspect_0));
		this.addOption(res.getString(R.string.tv_setting_aspect_1));
		this.addOption(res.getString(R.string.tv_setting_aspect_2));
	}

	@Override
	public String getTitle() {
		return this.mTitle;
	}

	@Override
	public void apply() {
		this.save();
		// FIXME do the actual work!!!
		DvbSyetemSetting.setAspect(this.getIndex());
	}

}
