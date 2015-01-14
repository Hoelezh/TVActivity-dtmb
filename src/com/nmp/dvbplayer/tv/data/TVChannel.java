package com.nmp.dvbplayer.tv.data;

public class TVChannel extends TVObject {
	public static final int NET_TV_NODE    = 0;
	public static final int NET_TURN_NODE  = 1;
	public static final int DVB_DATA_MODE  = 2;
	public static final int DVB_NVOD_MODE  = 3;
	public static final int DVB_TV_MODE    = 4;
	public static final int DVB_RADIO_MODE = 5;

	private String   mChnNumber;
	private boolean  mFavorite;
	private int      mType;
	
	public TVChannel(int id, String name, String number) {
		super(id, name);
		this.mChnNumber = number;
		this.mFavorite = false;
		this.mType = NET_TV_NODE;
	}

	public String getNumber() {
		return this.mChnNumber;
	}

	public boolean isFavorite() {
		return this.mFavorite;
	}

	public void setFavorite(boolean favorite) {
		this.mFavorite = favorite;
	}
	
	public void setType(int type) {
		this.mType = type;
	}
	
	public int getType() {
		return this.mType;
	}

}