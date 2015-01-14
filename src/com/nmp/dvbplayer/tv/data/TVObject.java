package com.nmp.dvbplayer.tv.data;

public class TVObject {
	private int    mObjectId;
	private String mObjectName;
	
	public TVObject(int id, String name) {
		this.mObjectId = id;
		this.mObjectName = name;
	}
	
	public int getId() {
		return this.mObjectId;
	}
	
	public String getName() {
		return this.mObjectName;
	}
	
	public void setId(int id) {
		this.mObjectId = id;
	}
	
	public void setName(String name) {
		this.mObjectName = name;
	}
}
