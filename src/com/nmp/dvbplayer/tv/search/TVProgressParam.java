package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.alitech.dvb.DvbChannelNode;
import com.alitech.dvb.DvbSearch;
import com.nmp.dvbplayer.R;
import com.nmp.dvbplayer.tv.data.TVChannel;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Resources;
import android.os.Handler;
import android.os.Message;

public class TVProgressParam {
	private Context mContext;
	public interface ProgressListener {
		void onProgressChange(int progress, int count, String msg);
	};
	
	public interface DataListener {
		void onDataChange(ArrayList<String> tvs, ArrayList<String> radios);
	};
	
	private static final int MSG_SEARCH = 0x123;
	
	private ProgressListener  mPrgListener;
	private DataListener      mDataListener;
	private ArrayList<String> mTVs;
	private ArrayList<String> mRadios;
	private int               mProgress;
	private String            mMessage;
	
	@SuppressLint("HandlerLeak")
	private Handler mMsgHandler = new Handler(){
		@Override
		public void handleMessage(Message msg) {
			switch(msg.what) {
			case MSG_SEARCH:
				onMessage(msg);
				break;
			default:
				super.handleMessage(msg);
				break;
			}
		}
	};
	
	public TVProgressParam(Context ctx) {
		this.mContext = ctx;
		this.mPrgListener = null;
		this.mDataListener = null;
		
		this.mProgress = 0;
		this.mMessage = "";

		this.mTVs = new ArrayList<String>();
		this.mRadios = new ArrayList<String>();
	}
	
	public void setProgressListener(ProgressListener listener) {
		this.mPrgListener = listener;
	}
	
	public void setDataListener(DataListener listener) {
		this.mDataListener = listener;
	}
	
	private void onMessage(Message msg) {
		int count = this.mTVs.size() + this.mRadios.size();
		Resources res = this.mContext.getResources();
	if(msg.arg1 == DvbSearch.SEARCH_PROGRAM_ADDED)
	{                		
    		DvbChannelNode channel = (DvbChannelNode)msg.obj;
    		String name = channel.getName();
    		if (TVChannel.DVB_RADIO_MODE == channel.getType()) {
    			this.mRadios.add(name);
    		} else {
    			this.mTVs.add(name);
    		}
			this.mMessage = res.getString(R.string.tv_search_get_program) + name;
			count += 1;
			if (this.mDataListener != null) {
				this.mDataListener.onDataChange(this.mTVs, this.mRadios);
				}
    	} else if(msg.arg1 == DvbSearch.SEARCH_COMPLETE) {
    		this.mMessage = res.getString(R.string.tv_search_all_pronums) + count;
    		this.mProgress = 100;
    	} else if(msg.arg1 == DvbSearch.SEARCH_TP_TUNING) {
    		DvbChannelNode.DvbFrontend fe = (DvbChannelNode.DvbFrontend)msg.obj;
    		this.mMessage = res.getString(R.string.tv_search_change_tp) + (double)(Math.round(fe.getFrequency()* 10)/10.0)/10000 + " MHz ...";
    	} else if (msg.arg1 == DvbSearch.SEARCH_PROGRESS) {
    		this.mProgress = (Integer)msg.obj;
    		this.mMessage = res.getString(R.string.tv_search_has_get) + count + res.getString(R.string.tv_search_programs);
    		//this.mMessage = "节目搜索完成, 总节目个数: " + count;
    	}
		
		//if (this.mDataListener != null) {
		//	this.mDataListener.onDataChange(this.mTVs, this.mRadios);
		//}
		
		if (this.mPrgListener != null) {
			this.mPrgListener.onProgressChange(this.mProgress, count, this.mMessage);
		}
	}
	
	public Handler getHandler() {
		return this.mMsgHandler;
	}
}
