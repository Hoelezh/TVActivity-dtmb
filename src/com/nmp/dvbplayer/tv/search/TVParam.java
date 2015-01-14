package com.nmp.dvbplayer.tv.search;

abstract class TVParam {
	public enum ParamType {
		Number,
		String
	};
	
	private String mName;
	private ParamType mType;
	private String mUnit;
	
	public TVParam(String name, ParamType type) {
		this.mName = name;
		this.mType = type;
	}
	
	public String getName() {
		return this.mName;
	}	
	
	public ParamType getType() {
		return this.mType;
	}
	
	public void setUnit(String unit) {
		this.mUnit = unit;
	}
	
	public String getUnit() {
		return this.mUnit;
	}
	
	public abstract String getDisplayValue();
};