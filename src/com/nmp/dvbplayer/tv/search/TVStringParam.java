package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

public class TVStringParam extends TVParam {
	private ArrayList<String> mValues;
	private int       mIndex;
	public TVStringParam(String name) {
		super(name, TVParam.ParamType.String);
		this.mValues = new ArrayList<String>();
		this.mIndex = 0;
	}
	
	
	public void clearValue() {
		this.mValues.clear();
	}
	
	public void addValue(String value) {
		this.mValues.add(value);
	}
	
	@Override
	public String getDisplayValue() {
		if (this.mIndex < 0 || this.mIndex >= this.mValues.size()) {
			return null;
		}
		return this.mValues.get(this.mIndex);
	}
	
	public void changeIdx(int diff) {
		int size = this.mValues.size();
		this.mIndex += diff;
		this.mIndex %= size;
		this.mIndex += size;
		this.mIndex %= size;
	}
	
	public int getIndex() {
		return this.mIndex;
	}
}
