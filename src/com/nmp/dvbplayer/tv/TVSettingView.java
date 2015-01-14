package com.nmp.dvbplayer.tv;

import java.util.ArrayList;

import com.nmp.dvbplayer.common.TVSettingAspect;
import com.nmp.dvbplayer.common.TVSettingBrightness;
import com.nmp.dvbplayer.common.TVSettingItem;
import com.nmp.dvbplayer.common.TVSettingSndChn;
import com.nmp.dvbplayer.R;

import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;
import android.widget.TextView;

public class TVSettingView extends TVWidget {
	private static final String Tag = TVSettingView.class.getName();
	private static final int    MaxItems = 3;
	private TVActivity   mActivity;
	private View         mSelfView;
	private View         mFocusView;
	private LinearLayout mViewList;
	private boolean      mFocus;
	private ArrayList<TVSettingItem> mSettings;
	private ArrayList<View>          mViews;
	private int          mFocusIdx;
	private int          mItemHeight;
	private RelativeLayout.LayoutParams mFocusLayout;
	
	public TVSettingView(TVActivity activity) {
		this.mActivity = activity;
		
		this.mSettings = new ArrayList<TVSettingItem>();
		this.mViews = new ArrayList<View>();
		
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_setting_view, (RelativeLayout)view);
		this.mSelfView = this.mActivity.findViewById(R.id.tv_setting_view);
		this.mFocusView = this.mSelfView.findViewById(R.id.tv_setting_focus);
		
		this.mViewList = (LinearLayout)this.mSelfView.findViewById(R.id.tv_setting_list);
		int size = this.mViewList.getChildCount();
		for (int i = 0; i < size; ++i) {
			this.mViews.add(this.mViewList.getChildAt(i));
		}
		this.mSettings.add(new TVSettingAspect(this.mActivity));
		this.mSettings.add(new TVSettingBrightness(this.mActivity));
		this.mSettings.add(new TVSettingSndChn(this.mActivity));
		
		this.mItemHeight = 70;
		this.mFocusLayout = new LayoutParams(this.mFocusView.getLayoutParams());
		this.mFocusIdx = MaxItems - 1;
		this.focus(false);
		this.setFocusPos();	
		this.hide();
	}
	
	@Override
	public void show() {
		this.updateList();
		super.show();
	}
	
	private void changeFocusIdx(int diff) {
		int newIdx = this.mFocusIdx + diff;
		if (newIdx >= MaxItems || newIdx < 0) {
			return;
		}
		
		int oldIdx = this.mFocusIdx;
		this.mFocusIdx = newIdx;
		
		int delta = this.mItemHeight * (this.mFocusIdx - oldIdx);
		TranslateAnimation animation = new TranslateAnimation(0, 0, 0, delta);
		animation.setDuration(TVActivity.AnimTime);
		animation.setAnimationListener(new Animation.AnimationListener() {			
			@Override
			public void onAnimationStart(Animation animation) {
				;
			}			
			@Override
			public void onAnimationRepeat(Animation animation) {
				// do nothing
			}			
			@Override
			public void onAnimationEnd(Animation animation) {
				setFocusPos();
			}
		});
		this.mFocusView.clearAnimation();
		this.mFocusView.setAnimation(animation);
		this.mFocusView.bringToFront();
		animation.startNow();
		this.mFocusView.invalidate();
		this.mViewList.bringToFront();
	}
	
	private void setFocusPos() {
		this.mFocusView.clearAnimation();
		int start = this.mFocusIdx * this.mItemHeight;
		this.mFocusLayout.setMargins(0, start, 0, 0);
		this.mFocusView.setLayoutParams(this.mFocusLayout);
	}
	
	private void changeValue(int dir) {
		if (this.mFocusIdx < 0 || this.mFocusIdx >= MaxItems) {
			Log.d(Tag, "invalid focus index: " + this.mFocusIdx);
			return;
		}
		
		TVSettingItem setItem = this.mSettings.get(this.mFocusIdx);
		setItem.changeIndex(dir);
		setItem.apply();
		this.updateList();
	}
	
	private void updateList() {
		if (this.mSettings.size() != this.mViews.size() ||
				this.mSettings.size() != MaxItems) {
			Log.e(Tag, "setting item size not equal to view size!");
			return;
		}
		
		for (int i = 0; i < MaxItems; ++i) {
			View view = this.mViews.get(i);
			TVSettingItem setItem = this.mSettings.get(i);
			int id = R.id.tv_setting_title;
			TextView titleView = (TextView)view.findViewById(id);
			id = R.id.tv_setting_value;
			TextView valView = (TextView)view.findViewById(id);
			titleView.setText(setItem.getTitle());
			valView.setText(setItem.currentOption());
		}
	}

	@Override
	protected View getView() {
		return this.mSelfView;
	}

	@Override
	public boolean accept(int keyCode) {
		if (this.mFocus) {
			if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode ||
					KeyEvent.KEYCODE_DPAD_RIGHT == keyCode ||
					KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
					KeyEvent.KEYCODE_ENTER == keyCode) {
				return true;
			}
			if (KeyEvent.KEYCODE_DPAD_UP == keyCode) {
				return true;
			}
			if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode &&
					this.mFocusIdx < MaxItems - 1) {
				return true;
			}
			return false;
		} else {
			// 没有焦点时，接受上键和回车键
			return (KeyEvent.KEYCODE_DPAD_UP == keyCode ||
					KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
					KeyEvent.KEYCODE_ENTER == keyCode);
		}
	}

	@Override
	public boolean onKeyDown(int keyCode) {
		if (KeyEvent.KEYCODE_DPAD_UP == keyCode) {
			this.changeFocusIdx(-1);
		} else if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode) {
			this.changeFocusIdx(1);
		} else if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
			this.changeValue(-1);
		} else if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			this.changeValue(1);
		}
		return true;
	}

	@Override
	public void focus(boolean f) {
		this.mFocus = f;
		int v = this.mFocus ? View.VISIBLE : View.GONE;
		if (this.mFocusView.getVisibility() != v) {
			this.mFocusView.setVisibility(v);
		}
	}
}
