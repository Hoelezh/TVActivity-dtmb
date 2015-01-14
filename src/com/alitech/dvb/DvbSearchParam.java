package com.alitech.dvb;

import org.json.JSONException;
import org.json.JSONObject;

public class DvbSearchParam {
	private static final String KeyFreqFrom = "frequencyfrom";
	private static final String KeyFreqTo = "frequencyto";
	private static final String KeyBandWidth = "bandwidth";
	private static final String KeySymRate = "symbolrate";
	private static final String KeyNitSearch = "nitsearch";
	private static final String KeyQAM = "qam";
	private static final String KeyFrontendType = "frontendtype";
	private static final String KeySearchMethod = "searchmethod";
	private static final String KeyFTAOnly = "FTAOnly";
	private static final String KeyProgramType = "programtype";
	
	public final static int SEARCH_METHOD_TP_SCAN		= 0;
	public final static int SEARCH_METHOD_SAT_SCAN		= 1;
	public final static int SEARCH_METHOD_BLIND_SCAN	= 2; 
	public final static int SEARCH_METHOD_ACCURATEBLIND_SCAN	= 3; 
   	
	private int mFrequencyFrom;
	private int mFrequencyTo;
	private int mBandwidth;
	private int mSymbolRate;
	private int mQam; 
	private boolean mNitSearch;
	private int mFrontendType;
	private int mSearchMethod;
	private int mFTAOnly;
	private int mProgramType;
	
	public DvbSearchParam(int frqFrom, int frqTo,int bandwidth, int sym, int qam,
			 boolean nit, int frontendtype, int searchmethod,int ftaonly,int programtype ) {
		this.mFrequencyFrom = frqFrom;
		this.mFrequencyTo = frqTo;
		this.mBandwidth = bandwidth;
		this.mSymbolRate = sym;
		this.mQam = qam;
		this.mNitSearch = nit;
		this.mFrontendType = frontendtype;
		this.mSearchMethod = searchmethod;
		this.mFTAOnly = ftaonly;
		this.mProgramType = programtype;
	}

	public void setNitSearch(boolean flag) {
		this.mNitSearch = flag;
	}
	
	public boolean isNitSearch() {
		return this.mNitSearch;
	}

	public int getFrequencyFrom() {
		return this.mFrequencyFrom;
	}

	public int getFrequencyTo() {
		return this.mFrequencyTo;
	}

	public int getBandwidth() {
		return this.mBandwidth;
	}
	
	public int getQam() {
		return this.mQam;
	}	
	
	public int getSymbolRate() {
		return this.mSymbolRate;
	}
	public int getfrontendType() {
		return this.mFrontendType;
	}
	
	public String toString() {
		JSONObject object = new JSONObject();
		try {
			object.put(KeyFreqFrom, this.mFrequencyFrom);
			object.put(KeyFreqTo, this.mFrequencyTo);
			object.put(KeyBandWidth, this.mBandwidth);
			object.put(KeySymRate, this.mSymbolRate);
			object.put(KeyNitSearch, this.mNitSearch);
			object.put(KeyQAM, this.mQam);
			object.put(KeyFrontendType, this.mFrontendType);
			object.put(KeySearchMethod, this.mSearchMethod);
			object.put(KeyFTAOnly, this.mFTAOnly);
			object.put(KeyProgramType, this.mProgramType);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return object.toString();
	}
	
	public static DvbSearchParam create(String json) {
		DvbSearchParam param = new DvbSearchParam(0, 0, 0, 0, 0, false,0,0,0,0);
		try {
			JSONObject object = new JSONObject(json);
			param.mFrequencyFrom = object.optInt(KeyFreqFrom);
			param.mFrequencyTo = object.optInt(KeyFreqTo);
			param.mBandwidth = object.optInt(KeyBandWidth);
			param.mSymbolRate = object.optInt(KeySymRate);
			param.mNitSearch = object.optBoolean(KeyNitSearch);
			param.mQam = object.optInt(KeyQAM);
			param.mFrontendType = object.optInt(KeyFrontendType);
			param.mSearchMethod = object.optInt(KeySearchMethod);
			param.mFTAOnly = object.optInt(KeyFTAOnly);
			param.mProgramType = object.optInt(KeyProgramType);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		return param;
	}
}
