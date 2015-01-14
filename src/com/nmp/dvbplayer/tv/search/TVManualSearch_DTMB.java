package com.nmp.dvbplayer.tv.search;

import com.alitech.dvb.DvbSearchParam;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;

public class TVManualSearch_DTMB extends TVSearch {
	
	private TVNumberParam mFreq;
	private TVStringParam mBandwidth;
	private TVStringParam mSearchMode;
	private TVStringParam mNit;
	
	
	public TVManualSearch_DTMB(Context ctx) {
		super(ctx);
		this.mFreq = null;
		this.mBandwidth = null;
		this.mSearchMode = null;
		this.mNit = null;
		this.initParams();
	}

	@Override
	protected void initParams() {
		Resources res = this.getContext().getResources();
		this.clearParams();

		String name = res.getString(R.string.tv_search_freq);
		this.mFreq = new TVNumberParam(name, "299.00");
		this.mFreq.setUnit("MHz");
		this.addParam(this.mFreq);
		
		name = res.getString(R.string.tv_search_band_width);
		this.mBandwidth = new TVStringParam(name);
		this.mBandwidth.addValue("8M");
		//this.mNit.addValue("7M");		
		//this.mNit.addValue("6M");
		this.mBandwidth.setUnit("MHz");
		this.addParam(this.mBandwidth);
		
		name = res.getString(R.string.tv_search_search_mode);
		this.mSearchMode = new TVStringParam(name);
		this.mSearchMode = new TVStringParam(name);
		this.mSearchMode.addValue("自动");
		this.addParam(this.mSearchMode);
		
		name = res.getString(R.string.tv_search_net);
		this.mNit = new TVStringParam(name);
		this.mNit.addValue("关");
		this.mNit.addValue("开");
		this.addParam(this.mNit);
	}


	@Override
	public DvbSearchParam getSearchParams() {
		int freq = (int)(this.mFreq.getValue() * 100);
		int sym = 0;
		int qam = 0;
		int bandwidth = 800; // FIXME
		boolean nit = this.mNit.getIndex() > 0;
		return new DvbSearchParam(freq, freq, bandwidth, sym, qam, nit,0x01/*dtmb*/,-6,0,0);
	}

}
