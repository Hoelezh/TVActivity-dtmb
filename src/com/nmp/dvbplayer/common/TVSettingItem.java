package com.nmp.dvbplayer.common;

import java.util.ArrayList;

import android.content.Context;
import android.content.SharedPreferences;

public abstract class TVSettingItem {
	private static final String PreferenceKey = "Setting";
	private Context             mContext;
	private int                 mIndex;
	private ArrayList<String>   mOptsName;
	
	public TVSettingItem(Context ctx) {
		this.mContext = ctx;
		this.mIndex = -1;
		this.mOptsName = new ArrayList<String>();
	}
	
	protected void addOption(String name) {
		this.mOptsName.add(name);
	}
	
	private SharedPreferences getSharedPreferences() {
    	String key = PreferenceKey;
    	int mode = Context.MODE_PRIVATE;
    	Context ctx = this.mContext;
    	return ctx.getSharedPreferences(key, mode);
    }
	
	public void save() {
		this.initIndex();
		if (this.mIndex >= 0) {
			String key = this.getTitle();
			String val = this.mOptsName.get(this.mIndex);
			SharedPreferences.Editor editor;
			editor = this.getSharedPreferences().edit();
			editor.putString(key, val);
			editor.commit();
		}
	}
	
	public void setDefaultIndex(int index) {
		int size = this.mOptsName.size();
		if (size > 0 && size > index && index > 0){
			this.mIndex = index;
			String key = this.getTitle();
			String val = this.mOptsName.get(this.mIndex);
			SharedPreferences.Editor editor;
			editor = this.getSharedPreferences().edit();
			editor.putString(key, val);
			editor.commit();
		}
	}
	private void initIndex() {
		int size = this.mOptsName.size();
		if (size > 0 && -1 == this.mIndex) {
			String defVal = this.mOptsName.get(0);
			String key = this.getTitle();
			String val = this.getSharedPreferences().getString(key, defVal);
			this.mIndex = this.mOptsName.indexOf(val);
		}
	}
	
	public void changeIndex(int diff) {
		this.initIndex();
		int size = this.mOptsName.size();
		this.mIndex += diff;
		this.mIndex %= size;
		this.mIndex += size;
		this.mIndex %= size;
	}
	
	public String currentOption() {
		this.initIndex();		
		if (this.mIndex < 0) {
			return null;
		}		
		return this.mOptsName.get(this.mIndex);
	}
	
	public String[] getOptionsName() {
		if (this.mOptsName.size() < 1) {
			return null;
		}
		String[] opts = new String[this.mOptsName.size()];
		this.mOptsName.toArray(opts);
		return opts;
	}
	
	public int getIndex() {
		return this.mIndex;
	}
	
	public int loadIndex() {
		this.initIndex();
		return this.mIndex;
	}
	
	public abstract String getTitle();	
	public abstract void apply();
}
