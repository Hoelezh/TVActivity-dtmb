package com.nmp.dvbplayer.tv;

import android.content.res.Resources;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams;

import com.nmp.dvbplayer.tv.data.TVSource;
import com.nmp.dvbplayer.R;

public class TVSourceView extends TVWidget {
	private static final String Tag = TVSourceView.class.getName();
	private static final int    MaxItems = 5;
	public static final String  SrcEvent = "source-change";
	
	private TVActivity mActivity;
	private View mSelfView;
	private View mLeftView;
	private View mRightView;
	private LinearLayout mSrcListView;
	private ImageView mFocusView;
	private LayoutParams mFocusLayout;	
	
	private int mFocusIdx;
	private int mSelectedIdx;
	private TVSource[] mSrcArray;
	private int mItemWidth;
	private int mItemHeight;
	private int mStartPos;
	private int mYPos;
	private boolean mFocus;
	
	public TVSourceView(TVActivity activity) {
		this.mActivity = activity;
		
		View view = this.mActivity.findViewById(R.id.tv_main);
		View.inflate(this.mActivity, R.layout.tv_source_list, (RelativeLayout)view);
		
		this.mSelfView = mActivity.findViewById(R.id.tv_source_list);
		this.mLeftView = this.mSelfView.findViewById(R.id.tv_src_left);
		this.mRightView = this.mSelfView.findViewById(R.id.tv_src_right);
		this.mFocusView = (ImageView)this.mSelfView.findViewById(R.id.tv_source_focus);
		this.mSrcListView = (LinearLayout)this.mSelfView.findViewById(R.id.tv_source_texts);
		this.mFocusLayout = new LayoutParams(this.mFocusView.getLayoutParams());
		
		this.mFocusIdx = 0;
		this.mSelectedIdx = 0;
		this.mSrcArray = null;
		this.focus(false);
		
		this.mItemWidth = 232;
		this.mItemHeight = 56;
		
		this.mStartPos = 0;
		this.mYPos = 0;
		
		this.hide();
	}
	
	@Override
	public void show() {
		if (View.VISIBLE == this.mSelfView.getVisibility()) {
			Log.d(Tag, "view is visible, show() do nothing!");
			return;
		}
		this.updateList();
		super.show();
	}
	
	private void updateList() {
		TVChnManager manager = this.mActivity.getChannelManager();
		this.mSrcListView.removeAllViews();
		this.mSrcArray = manager.getSelSources();
		
		if (null == this.mSrcArray) {
			Log.e(Tag, "no source list to show!");
			return;
		}
		
		int size = this.mSrcArray.length;		
		this.mSelectedIdx = manager.getSelSrcIdx();
		if (this.mFocusIdx < 0) {
			this.mFocusIdx = size - 1;
		}
		if (this.mFocusIdx >= size) {
			this.mFocusIdx = 0;
		}
		
		int start = this.mFocusIdx - this.mFocusIdx % MaxItems;
		Resources res = this.mActivity.getResources();
		for (int i = 0; i < MaxItems; ++i) {
			if (start + i >= size) {
				break;
			}
			LinearLayout.LayoutParams lp = null;
			lp = new LinearLayout.LayoutParams(this.mItemWidth, this.mItemHeight);
			TextView v = new TextView(this.mActivity);
			v.setLayoutParams(lp);
			v.setTextSize(TypedValue.COMPLEX_UNIT_PX, 32);
			v.setSingleLine();
			if (i + start == this.mSelectedIdx) {
				v.setTextColor(res.getColor(R.color.tv_yellow));
			} else {
				v.setTextColor(res.getColor(R.color.tv_white));
			}
			v.setGravity(Gravity.CENTER);
			v.setText(this.mSrcArray[i + start].getName());
			this.mSrcListView.addView(v);
		}
		
		this.mStartPos = (1280 - 1160) / 2;
		this.mYPos = (131 - this.mItemHeight) / 2;
		int x = this.mStartPos + this.mItemWidth * (this.mFocusIdx % MaxItems);
		this.mFocusLayout.setMargins(x, this.mYPos, 0, 0);
		this.mFocusView.setLayoutParams(this.mFocusLayout);
		
		int v = this.mFocusIdx >= MaxItems ? View.VISIBLE : View.GONE;
		this.mLeftView.setVisibility(v);
		int p = (size + MaxItems - 1) / MaxItems;
		v = this.mFocusIdx < (p - 1) * MaxItems ? View.VISIBLE : View.GONE;
		this.mRightView.setVisibility(v);
	}
	
	@Override
	public boolean accept(int keyCode) {
		if (this.mFocus) {
			// 有焦点时，只处理左右和回车键
			return (KeyEvent.KEYCODE_DPAD_LEFT == keyCode ||
					KeyEvent.KEYCODE_DPAD_RIGHT == keyCode ||
					KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
					KeyEvent.KEYCODE_ENTER == keyCode);
		} else {
			// 没有焦点时，接受上键和回车键
			return (KeyEvent.KEYCODE_DPAD_UP == keyCode ||
					KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
					KeyEvent.KEYCODE_ENTER == keyCode);
		}
	}
	
	@Override
	public boolean onKeyDown(int keyCode) {
		if (null == this.mSrcArray) {
			return false;
		}
		
		if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
			this.changeFocusIdx(-1);
			return true;
		}
		if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			this.changeFocusIdx(1);
			return true;
		}
		if (KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
				KeyEvent.KEYCODE_ENTER == keyCode) {			
			this.mActivity.changeSource(this.mFocusIdx - this.mSelectedIdx);
			this.mSelectedIdx = this.mFocusIdx;
			this.updateList();
			return true;
		}
		return false;
	}
	
	private void changeFocusIdx(int diff) {
		if (null == this.mSrcArray) {
			return;
		}
		
		int size = this.mSrcArray.length;
		int oldPage = this.mFocusIdx / MaxItems;
		int oldIdx = this.mFocusIdx % MaxItems;
		this.mFocusIdx += diff;
		if (this.mFocusIdx < 0) {
			this.mFocusIdx += size;
		}
		if (this.mFocusIdx >= size) {
			this.mFocusIdx -= size;
		}
		
		if (this.mFocusIdx / MaxItems != oldPage) {
			this.updateList();
		}
		
		int deltaX = this.mItemWidth * ((this.mFocusIdx % MaxItems) - oldIdx);
		TranslateAnimation animation = new TranslateAnimation(0, deltaX, 0, 0);
		animation.setDuration(TVActivity.AnimTime);
		animation.setAnimationListener(new Animation.AnimationListener() {			
			@Override
			public void onAnimationStart(Animation animation) { }			
			@Override
			public void onAnimationRepeat(Animation animation) { }			
			@Override
			public void onAnimationEnd(Animation animation) {
				mFocusView.clearAnimation();
				int newPos = mStartPos + mItemWidth * (mFocusIdx % MaxItems);
				mFocusLayout.setMargins(newPos, mYPos, 0, 0);
				mFocusView.setLayoutParams(mFocusLayout);
			}
		});
		this.mFocusView.clearAnimation();
		this.mFocusView.setAnimation(animation);
		animation.startNow();
		this.getView().invalidate();
	}
	
	@Override
	public void focus(boolean f) {
		this.mFocus = f;
		this.mFocusView.setVisibility(this.mFocus ? View.VISIBLE : View.GONE);
	}

	@Override
	protected View getView() {
		return this.mSelfView;
	}
	
	@Override
	public void appNotify(String type, Object value) {
		if (type.equalsIgnoreCase(SrcEvent)) {
			this.updateList();
		}
	}

}
