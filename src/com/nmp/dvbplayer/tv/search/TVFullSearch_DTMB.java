package com.nmp.dvbplayer.tv.search;

import android.content.Context;
import android.content.res.Resources;

import com.alitech.dvb.DvbSearchParam;
import com.nmp.dvbplayer.R;

public class TVFullSearch_DTMB extends TVSearch {

	private TVNumberParam mStartFreq;
	private TVNumberParam mEndFreq;
	private TVStringParam mBandwidth;
	private TVStringParam mSearchMode;
	
	public TVFullSearch_DTMB(Context ctx) {
		super(ctx);
		this.mStartFreq = null;
		this.mEndFreq = null;
		this.mBandwidth = null;
		this.mSearchMode = null;
		this.initParams();
	}

	@Override
	protected void initParams() {
		Resources res = this.getContext().getResources();
		this.clearParams();

		String name = res.getString(R.string.tv_search_beg_freq);
		this.mStartFreq = new TVNumberParam(name, "111.00");
		this.mStartFreq.setUnit("MHz");
		this.addParam(this.mStartFreq);
		
		name = res.getString(R.string.tv_search_end_freq);
		this.mEndFreq = new TVNumberParam(name, "859.00");
		this.mEndFreq.setUnit("MHz");
		this.addParam(this.mEndFreq);
		
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
	}

	@Override
	public DvbSearchParam getSearchParams() {
		int sfreq = (int)(this.mStartFreq.getValue() * 100);
		int efreq = (int)(this.mEndFreq.getValue() * 100);
		int sym = 0;
		int qam = 0;
		int bandwidth = 800; // FIXME
		boolean nit = false;
		return new DvbSearchParam(sfreq, efreq, bandwidth, sym, qam, nit,0x02/*dtmb*/,0,0,0);
	}

}
