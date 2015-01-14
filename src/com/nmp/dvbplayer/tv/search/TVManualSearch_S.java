package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;
import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.alitech.dvb.DvbSearchParam;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;

public class TVManualSearch_S extends TVSearch {
	
	private TVStringParam mCurSatselect;
	private TVNumberParam mFreq;
	private TVNumberParam mSymRate;
	private TVStringParam mPor;
	private TVStringParam mNit;
	private DVBSatelliteNode[] sat_nodes;
	private ArrayList<DVBSatelliteNode> mSatLists;
	
	public TVManualSearch_S(Context ctx) {
		super(ctx);
		this.mCurSatselect = null;
		this.mFreq = null;
		this.mSymRate = null;
		this.mPor = null;
		this.mNit = null;
		this.initParams();
	}

	@Override
	protected void initParams() {
		Resources res = this.getContext().getResources();
		this.clearParams();
		String name = res.getString(R.string.tv_search_cursatsel);
		this.mCurSatselect = new TVStringParam(name);
		this.sat_nodes = DVBSatellite.loadSatelliteNodes();
		if(this.sat_nodes == null || this.sat_nodes.length == 0)
		{
			this.mCurSatselect.addValue("NULL");
			this.mCurSatselect.changeIdx(0);
		}
		else
		{
		DVBSatelliteNode sNode;
		this.mSatLists = new ArrayList<DVBSatelliteNode>();
		for (int i = 0; i < this.sat_nodes.length; i++) {
			sNode = this.sat_nodes[i];
			if(sNode.isselect()) {
				mSatLists.add(sNode);
			}
		}
		int sat_count;
		sat_count = this.mSatLists.size();
		if(sat_count == 0 && this.sat_nodes.length > 0) {
			sNode = this.sat_nodes[0];
			mSatLists.add(sNode);
			sat_count = this.mSatLists.size();
			sNode.setselect(true);
			sNode.settuner1(true);
			DVBSatellite.updateSatellite(sNode);
		}
		for(int i=0;i<sat_count;i++)
		{
			this.mCurSatselect.addValue(this.mSatLists.get(i).getName());
			sNode = this.sat_nodes[i];
			if(sNode.isselect())
			{
				this.mCurSatselect.changeIdx(i);
				break;
			}
		}
		}
		this.addParam(this.mCurSatselect);
		name = res.getString(R.string.tv_search_freq);
		this.mFreq = new TVNumberParam(name, "04000");
		this.mFreq.setUnit("MHz");
		this.addParam(this.mFreq);
		
		name = res.getString(R.string.tv_search_sym);
		this.mSymRate = new TVNumberParam(name, "27500");
		this.mSymRate.setUnit("KBaud");
		this.addParam(this.mSymRate);
		
		name = res.getString(R.string.tv_search_por);
		this.mPor = new TVStringParam(name);
		this.mPor.addValue("H");
		this.mPor.addValue("V");
		this.mPor.addValue("Auto");
		this.mPor.changeIdx(0);
		this.addParam(this.mPor);
		
		name = res.getString(R.string.tv_search_net);
		this.mNit = new TVStringParam(name);
		name = res.getString(R.string.tv_off);
		this.mNit.addValue(name);
		name = res.getString(R.string.tv_open);
		this.mNit.addValue(name);
		this.mNit.changeIdx(0);
		this.addParam(this.mNit);
	}

	@Override
	public DvbSearchParam getSearchParams() {
		int freq = (int)(this.mFreq.getValue() * 100);
		int sym = (int)this.mSymRate.getValue();
		int por = this.mPor.getIndex();
		int bandwidth = 800; // FIXME
		boolean nit = this.mNit.getIndex() > 0;
		return new DvbSearchParam(freq, freq, bandwidth, sym, por, nit,0x00/*dvbs*/,0,0,0);
	}

}
