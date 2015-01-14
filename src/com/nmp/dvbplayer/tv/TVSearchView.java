package com.nmp.dvbplayer.tv;

import com.nmp.dvbplayer.tv.search.TVSearchSetting;
import com.nmp.dvbplayer.R;

import android.content.Intent;
import android.view.KeyEvent;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class TVSearchView extends TVWidget {
	private TVActivity mActivity;
	private TextView   mSelfView;
	
	public TVSearchView(TVActivity activity) {
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_search_view, (RelativeLayout)view);
		this.mSelfView = (TextView)this.mActivity.findViewById(R.id.tv_search_view);
		this.hide();
	}

	@Override
	protected View getView() {
		return this.mSelfView;
	}

	@Override
	public boolean accept(int keyCode) {
		if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||
				keyCode == KeyEvent.KEYCODE_ENTER) {
			Intent intent = new Intent(this.mActivity, TVSearchSetting.class);
			this.mActivity.startActivityForResult(intent, TVActivity.ReqCode);
		}
		return false;
	}

	@Override
	public boolean onKeyDown(int keyCode) {
		return true;
	}
	
	@Override
	public void focus(boolean f) {
		;
	}
}
