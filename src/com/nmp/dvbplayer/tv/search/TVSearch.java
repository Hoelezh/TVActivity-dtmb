package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.alitech.dvb.DvbSearchParam;

import android.content.Context;
import android.util.Pair;

public abstract class TVSearch {
	private Context mContext;
	private ArrayList<TVParam> mParams;
	private int mIndex;
	
	public TVSearch(Context ctx) {
		this.mContext = ctx;
		this.mParams = new ArrayList<TVParam>();
		this.mIndex = 0;
	}
	
	protected Context getContext() {
		return this.mContext;
	}
	
	protected void clearParams() {
		this.mParams.clear();
	}
	
	protected void addParam(TVParam param) {
		this.mParams.add(param);
	}
	
	protected void setIndex(int idx) {
		this.mIndex = idx;
	}
	
	public TVParam getCurrentParam() {
		if (this.mIndex < 0 || this.mIndex >= this.mParams.size()) {
			return null;
		}
		return this.mParams.get(this.mIndex);
	}
	public int getCurrentParamsize() {
		return this.mParams.size();
	}
	
	public ArrayList<Pair<String, String>> getDataList() {
		if (this.mParams.size() < 1) {
			return null;
		}
		
		ArrayList<Pair<String, String>> data;
		data = new ArrayList<Pair<String, String>>();
		
		for (TVParam param : this.mParams) {
			Pair<String, String> pair;
			String name = param.getName();
			String val = param.getDisplayValue();
			pair = new Pair<String, String>(name, val);
			data.add(pair);
		}
		
		return data;
	}
	
	protected abstract void initParams();
	
	public abstract DvbSearchParam getSearchParams();
}
