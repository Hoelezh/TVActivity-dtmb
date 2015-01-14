package com.nmp.dvbplayer.tv.search;

import com.alitech.dvb.DvbSearchParam;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;

public class TVManualSearch extends TVSearch {
	
	private TVNumberParam mFreq;
	private TVNumberParam mSymRate;
	private TVStringParam mQAM;
	private TVStringParam mNit;
	
	public TVManualSearch(Context ctx) {
		super(ctx);
		this.mFreq = null;
		this.mSymRate = null;
		this.mQAM = null;
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
		
		name = res.getString(R.string.tv_search_net);
		this.mNit = new TVStringParam(name);
		this.mNit.addValue("关");
		this.mNit.addValue("开");
		this.addParam(this.mNit);
	}

	@Override
	public DvbSearchParam getSearchParams() {
		int freq = (int)(this.mFreq.getValue() * 100);
		int sym = (int)this.mSymRate.getValue();
		int qam = 5 + this.mQAM.getIndex();
		int bandwidth = 800; // FIXME
		boolean nit = this.mNit.getIndex() > 0;
		return new DvbSearchParam(freq, freq, bandwidth, sym, qam, nit,0x01/*dvbc*/,-6,0,0);
	}

}
