package com.nmp.dvbplayer.tv.search;

import android.content.Context;
import android.content.res.Resources;

import com.alitech.dvb.DvbSearchParam;
import com.nmp.dvbplayer.R;

public class TVFullSearch extends TVSearch {

	private TVNumberParam mStartFreq;
	private TVNumberParam mEndFreq;
	private TVNumberParam mSymRate;
	private TVStringParam mQAM;
	
	public TVFullSearch(Context ctx) {
		super(ctx);
		this.mStartFreq = null;
		this.mEndFreq = null;
		this.mSymRate = null;
		this.mQAM = null;
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
		
		name = res.getString(R.string.tv_search_sym);
		this.mSymRate = new TVNumberParam(name, "06875");
		this.mSymRate.setUnit("KBaud");
		this.addParam(this.mSymRate);
		
		name = res.getString(R.string.tv_search_qam);
		this.mQAM = new TVStringParam(name);
		this.mQAM.addValue("32-QAM");
		this.mQAM.addValue("64-QAM");
		this.mQAM.addValue("128-QAM");
		this.mQAM.addValue("256-QAM");
		this.mQAM.changeIdx(1);
		this.addParam(this.mQAM);
	}

	@Override
	public DvbSearchParam getSearchParams() {
		int sfreq = (int)(this.mStartFreq.getValue() * 100);
		int efreq = (int)(this.mEndFreq.getValue() * 100);
		int sym = (int)this.mSymRate.getValue();
		int qam = 5 + this.mQAM.getIndex();
		int bandwidth = 800; // FIXME
		boolean nit = false;
		return new DvbSearchParam(sfreq, efreq, bandwidth, sym, qam, nit,0x01/*dvbc*/,0,0,0);
	}

}
