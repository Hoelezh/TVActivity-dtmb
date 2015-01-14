package com.nmp.dvbplayer.tv.data;

public class RecommendItem extends TVObject {
	private String mPosterUrl;
	private String mPrivateData;
	public RecommendItem(int id, String name) {
		super(id, name);
		this.mPosterUrl = "";
		this.mPrivateData = "";
	}
	
	public void setPosterURL(String url) {
		this.mPosterUrl = url;
	}
	
	public String getPosterURL() {
		return this.mPosterUrl;
	}
	
	public void setPrivateData(String data) {
		this.mPrivateData = data;
	}
	
	public String getPrivateData() {
		return this.mPrivateData;
	}

}