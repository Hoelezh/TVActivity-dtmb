package com.nmp.dvbplayer.tv.data;

public class TVSource extends TVObject {

	private String mSourceURL;

	public TVSource(int id, String name, String url) {
		super(id, name);
		this.mSourceURL = url;
	}

	public String getSourceURL() {
		return this.mSourceURL;
	}

}