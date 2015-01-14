package com.nmp.dvbplayer.tv.search;

public class TVNumberParam extends TVParam {

	private float  mValue;
	private int    mIntegerBits;
	private int    mFractionBits;
	public TVNumberParam(String name, String value) {
		super(name, TVParam.ParamType.Number);		
		int idx = value.indexOf(".");
		int len = value.length();
		if (idx < 0) {
			this.mIntegerBits = len;
			this.mFractionBits = 0;
		} else if (0 == idx) {
			this.mIntegerBits = 0;
			this.mFractionBits = len - 1;
		} else {
			this.mIntegerBits = idx;
			this.mFractionBits = len - idx - 1;
		}		
		this.mValue = Float.valueOf(value);
	}
	
	public void setValue(float value) {
		this.mValue = value;
	}

	public float getValue() {
		return this.mValue;
	}
	
	public int getIntegerBits() {
		return this.mIntegerBits;
	}
	
	public void setIntegerBits(int bits) {
		this.mIntegerBits = bits;
	}
	
	public int getFractionBits() {
		return this.mFractionBits;
	}
	
	public void setFractionBits(int bits) {
		this.mFractionBits = bits;
	}

	@Override
	public String getDisplayValue() {
		String val = String.valueOf(this.mValue);
		if (this.mFractionBits < 1) {
			val = String.valueOf((int)this.mValue);
		}
		return val + " " + this.getUnit();
	}
}
