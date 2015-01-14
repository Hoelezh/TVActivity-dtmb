package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;
import java.util.HashMap;

import com.alitech.dvb.DvbSearch;
import com.alitech.dvb.DvbSearchParam;
import com.alitech.dvb.DvbSystem;
import com.nmp.dvbplayer.R;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class TVSearchProgress extends Activity implements
		TVProgressParam.DataListener,
		TVProgressParam.ProgressListener {
	private static final int ListSize = 5;
	private static final String Key1 = "field1";
	private static final String Key2 = "field2";
	private static final int DefaultTime = 2000;
	private static final int MSG_SEARCH_FINISH = 0;
	
	private TVProgressParam mParams;
	private SimpleAdapter   mAdapter;
	private DvbSearchParam  mSearchParam;
	private DvbSearch       mDvbSearch;
	private ArrayList<HashMap<String, Object>> mData;
	
	private ListView    mListView;
	private TextView    mMsgView;
	private ProgressBar mProgressBar;
	private TextView    mProgressView;
	private int         mProgramCount;
	
	@SuppressLint("HandlerLeak")
	private Handler mMsgHandler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch(msg.what) {
			case MSG_SEARCH_FINISH:
				Intent intent = new Intent();
				intent.putExtra("result", mProgramCount);
				setResult(RESULT_OK, intent);
				finish();
				break;
			default:
				super.handleMessage(msg);
				break;
			}
		}
	};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tv_search_progress);
		
		Intent intent = this.getIntent();
		String param = intent.getStringExtra("param");
		this.mSearchParam = DvbSearchParam.create(param);
		this.mDvbSearch = null;
		this.mProgramCount = 0;
		this.mParams = null;
		
		this.mListView = (ListView)this.findViewById(R.id.tv_progress_list);
		this.mMsgView = (TextView)this.findViewById(R.id.tv_message_info);
		this.mProgressBar = (ProgressBar)this.findViewById(R.id.tv_progress_bar);
		this.mProgressView = (TextView)this.findViewById(R.id.tv_progress_view);
		
		this.mData = new ArrayList<HashMap<String, Object>>();
		this.mAdapter = new SimpleAdapter(
			this,
			this.mData,
			R.layout.tv_search_prg_item,
			new String[] { Key1 , Key2 },
			new int[] { R.id.text_field1, R.id.text_field2 }
		);
		this.mListView.setAdapter(this.mAdapter);
	}
	
	@Override
    protected void onStart() {
		super.onStart();
		this.mParams = new TVProgressParam(this);
		this.mParams.setDataListener(this);
		this.mParams.setProgressListener(this);
		
		this.mProgramCount = 0;
		DvbSystem.loadDefault();
		this.mDvbSearch = new DvbSearch();
		this.mDvbSearch.set_handler(this.mParams.getHandler());
		this.mDvbSearch.startSearch(this.mSearchParam);
	}
	
	@Override
    protected void onStop() {
    	super.onStop();
    	this.mParams.setDataListener(null);
		this.mParams.setProgressListener(null);
		this.mDvbSearch.stop();
	}

	@Override
	public void onProgressChange(int progress, int count, String msg) {
		this.mProgressBar.setProgress(progress);
		this.mProgressView.setText(String.valueOf(progress) + "%");
		this.mMsgView.setText(msg);
		this.mProgramCount = count;
		
		if (progress >= 100) {
			int msgId = MSG_SEARCH_FINISH;
			int time = DefaultTime;
			this.mMsgHandler.removeMessages(msgId);
			this.mMsgHandler.sendEmptyMessageDelayed(msgId, time);
		}
	}

	@Override
	public void onDataChange(ArrayList<String> tvs, ArrayList<String> radios) {
		int size1 = tvs.size();
		int size2 = radios.size();
		this.mData.clear();
		for (int i = ListSize; i > 0; --i) {
			String tv = "";
			String radio = "";
			if (size1 - i >= 0) {
				tv = tvs.get(size1 - i);
			}
			if (size2 - i >= 0) {
				radio = radios.get(size2 - i);
			}
			HashMap<String, Object> map = new HashMap<String, Object>();
			map.put(Key1, tv);
			map.put(Key2, radio);
			this.mData.add(map);
		}
		this.mAdapter.notifyDataSetChanged();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		boolean keyHandled = false;
		if (keyCode == KeyEvent.KEYCODE_MUTE ||
				keyCode == KeyEvent.KEYCODE_VOLUME_UP ||
				keyCode == KeyEvent.KEYCODE_VOLUME_DOWN ||
				keyCode == KeyEvent.KEYCODE_VOLUME_MUTE) {
			keyHandled = true;
		}			
		
		if(keyHandled == false)
			keyHandled = super.onKeyDown(keyCode, event);
		
		return keyHandled;
	}
	
	
}
