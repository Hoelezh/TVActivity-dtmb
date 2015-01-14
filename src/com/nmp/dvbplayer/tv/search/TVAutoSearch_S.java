package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.alitech.dvb.DvbSearchParam;
import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.res.Resources;

public class TVAutoSearch_S extends TVSearch {
	
	private TVStringParam mCurSatselect;
	private TVStringParam mOnlyFTA;
	private TVStringParam mProtype;
	private TVStringParam mNit;
	private DVBSatelliteNode[] sat_nodes;
	private ArrayList<DVBSatelliteNode> mSatLists;
	
	public TVAutoSearch_S(Context ctx) {
		super(ctx);
		this.mCurSatselect = null;
		this.mOnlyFTA = null;
		this.mProtype = null;
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
		//this.mCurSatselect.addValue("sat_1");
		//this.mCurSatselect.addValue("sat_2");
		//this.mCurSatselect.addValue("sat_3");
		//this.mCurSatselect.changeIdx(0);
		this.addParam(this.mCurSatselect);
		
		name = res.getString(R.string.tv_search_onlyfta);
		this.mOnlyFTA = new TVStringParam(name);
		name = res.getString(R.string.tv_no);
		this.mOnlyFTA.addValue(name);
		name = res.getString(R.string.tv_yes);
		this.mOnlyFTA.addValue(name);
		this.mOnlyFTA.changeIdx(0);
		this.addParam(this.mOnlyFTA);
		
		
		name = res.getString(R.string.tv_search_protype);
		this.mProtype = new TVStringParam(name);
		name = res.getString(R.string.tv_search_tv_radio);
		this.mProtype.addValue(name);
		name = res.getString(R.string.tv_search_tv);
		this.mProtype.addValue(name);
		name = res.getString(R.string.tv_search_radio);
		this.mProtype.addValue(name);
		this.mProtype.changeIdx(0);
		this.addParam(this.mProtype);
		
		
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
		int freq = 0;
		int sym = 0;
		int por = 0;
		int bandwidth = 800; // FIXME
		boolean nit = this.mNit.getIndex() > 0;
		int fta = this.mOnlyFTA.getIndex();
		int protype = this.mProtype.getIndex();
		return new DvbSearchParam(freq, freq, bandwidth, sym, por, nit,0x00/*dvbs*/,2,fta,protype);
	}

}
