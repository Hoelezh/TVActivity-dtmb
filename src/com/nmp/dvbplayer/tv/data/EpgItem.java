package com.nmp.dvbplayer.tv.data;

public class EpgItem {
	public static enum EpgType {
		Movie,
		News,
		Sport,
		Unknown
	};
	
	private String  mStartTime;
	private String  mEndTime;
	private EpgType mType;
	private boolean mLiveBack;
	private String mTitle;
	private String mBrief;
	private String mDetail;
	
	public EpgItem(String title) {
		this.mStartTime = "";
		this.mEndTime = "";
		this.mType = EpgType.Unknown;
		this.mLiveBack = false;
		this.mTitle = title;
		this.mBrief = "";
		this.mDetail = "";
	}
	
	public void setStartTime(String time) {
		this.mStartTime = time;
	}

	public String getStartTime() {
		return this.mStartTime;
	}
	
	public void setEndTime(String time) {
		this.mEndTime = time;
	}

	public String getEndTime() {
		return this.mEndTime;
	}
	
	public void setEpgType(EpgType type) {
		this.mType = type;
	}
	
	public EpgType getEpgType() {
		return this.mType;
	}

	public boolean canLiveBack() {
		return this.mLiveBack;
	}
	
	public void setLiveBack(boolean liveback) {
		this.mLiveBack = liveback;
	}
	
	public TVSource[] getSources() {
		return null;
	}
	
	public String getTitle() {
		return this.mTitle;
	}
	
	public void setBrief(String brief) {
		this.mBrief = brief;
	}
	
	public String getBrief() {
		return this.mBrief;
	}
	
	public void setDetail(String detail) {
		this.mDetail = detail;
	}
	
	public String getDetail() {
		return this.mDetail;
	}
}