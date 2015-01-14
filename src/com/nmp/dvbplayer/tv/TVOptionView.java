package com.nmp.dvbplayer.tv;

import java.util.ArrayList;
import com.nmp.dvbplayer.R;

import android.content.res.Resources;
import android.view.KeyEvent;
import android.view.View;
import android.widget.RelativeLayout.LayoutParams;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class TVOptionView extends TVWidget {
	private TVActivity   mActivity;
	private View         mSelfView;
	private ImageView    mFocusView;
	private LayoutParams mLayoutParams;
	private LinearLayout mOptListView;
	
	private TVWidget     mRelatedWidget;
	private TVWidget     mSourceWidget;
	private TVWidget     mEpgWidget;
	private TVWidget     mFavWidget;
	private TVWidget     mSettingWidget;
	private TVWidget     mSerachWidget;
	private TVWidget     mUdrmWidget;	

	private int     mCurrentIdx;
	private boolean mFocus;
	private int     mStartPos;
	private int     mItemWidth;
	private int     mFocusWidth;
	
	private ArrayList<TVWidget> mWidgets;
	
	public TVOptionView(TVActivity activity) {
		this.mActivity = activity;
		
		int resId = R.id.tv_main;
		View view = activity.findViewById(resId);
		resId = R.layout.tv_option_list;
		View.inflate(activity, resId, (RelativeLayout)view);
		resId = R.id.tv_option_list;
		this.mSelfView = this.mActivity.findViewById(resId);
		resId = R.id.tv_option_container;
		view = this.mSelfView.findViewById(resId);
		this.mOptListView = (LinearLayout)view;
		resId = R.id.tv_option_focus;
		this.mFocusView = (ImageView)this.mSelfView.findViewById(resId);
		
		this.mRelatedWidget = null;
		this.mSourceWidget = null;
		this.mEpgWidget = null;
		this.mFavWidget = null;
		this.mSettingWidget = null;
		this.mSerachWidget = null;
		this.mUdrmWidget = null;

		this.mWidgets = new ArrayList<TVWidget>();
		this.focus(true);
		
		//每个选项的宽度是180像素，已经在layout文件中设定好了, 292是焦点区域的的宽度
		this.mItemWidth = 180;
		this.mFocusWidth = 322;
		
		this.hide();
	}
	
	private void initFocusPos() {
		int size = this.mWidgets.size();
		this.mStartPos = (1280 - this.mItemWidth * size - this.mFocusWidth + this.mItemWidth) / 2;
		this.mLayoutParams = new LayoutParams(this.mFocusView.getLayoutParams());
		this.mLayoutParams.setMargins(this.mStartPos, 0, 0, 0);
		this.mFocusView.setLayoutParams(this.mLayoutParams);	
	}
	
	public void TVTypeChange() {
		if (null == this.mRelatedWidget) {
			this.mRelatedWidget = new TVRelatedView(this.mActivity);
		}
		if (null == this.mSourceWidget) {
			this.mSourceWidget = new TVSourceView(this.mActivity);
		}
		if (null == this.mEpgWidget) {
			this.mEpgWidget = new TVEpgView(this.mActivity);
		}
		if (null == this.mFavWidget) {
			this.mFavWidget = new TVFavView(this.mActivity);
		}
		if (null == this.mSettingWidget) {
			this.mSettingWidget = new TVSettingView(this.mActivity);
		}
		if (null == this.mSerachWidget) {
			this.mSerachWidget = new TVSearchView(this.mActivity);
		}		
		if (null == this.mUdrmWidget) {
			this.mUdrmWidget = new TVUdrmView(this.mActivity);
		}	
		this.mOptListView.removeAllViews();
		this.mWidgets.clear();
		this.mCurrentIdx = 0;
		
		int drawId = 0;
		int strId = 0;
		if (this.mActivity.getIsRelated()) {
			drawId = R.drawable.tv_option_related_icon;
			strId = R.string.tv_option_related;
			this.addOption(drawId, strId, this.mRelatedWidget);
		}
		
		if (TVActivity.TV_NET == this.mActivity.getTVType()) {
			drawId = R.drawable.tv_option_src_icon;
			strId = R.string.tv_option_src;
			this.addOption(drawId, strId, this.mSourceWidget);
		}
		
		drawId = R.drawable.tv_option_epg_icon;
		strId = R.string.tv_option_epg;
		this.addOption(drawId, strId, this.mEpgWidget);
		
		drawId = R.drawable.tv_option_fav_icon;
		strId = R.string.tv_option_fav;
		this.addOption(drawId, strId, this.mFavWidget);
		
		drawId = R.drawable.tv_setting_icon;
		strId = R.string.tv_option_setting;
		this.addOption(drawId, strId, this.mSettingWidget);
		
		if (TVActivity.TV_DVB == this.mActivity.getTVType()) {
			drawId = R.drawable.tv_search_icon;
			strId = R.string.tv_option_search;
			this.addOption(drawId, strId, this.mSerachWidget);
		}
		
		drawId = R.drawable.tv_setting_icon;
		strId = R.string.rs_udrm_menu;		
		this.addOption(drawId, strId, this.mUdrmWidget);	

		this.initFocusPos();
	}
	
	private void addOption(int drawableId, int strId, TVWidget widget) {
		Resources res = this.mActivity.getResources();
		int index = this.mOptListView.getChildCount();
		View.inflate(this.mActivity, R.layout.tv_option_item, this.mOptListView);
		View view = this.mOptListView.getChildAt(index);
		TextView txtView = (TextView)view.findViewById(R.id.option_name);
		ImageView imgView = (ImageView)view.findViewById(R.id.option_icon);
		txtView.setText(res.getString(strId));
		imgView.setImageResource(drawableId);
		this.mWidgets.add(widget);
	}
	
	private void startAnimation(int oldIdx) {		
		int deltaX = this.mItemWidth * (this.mCurrentIdx - oldIdx);
		TranslateAnimation animation = new TranslateAnimation(0, deltaX, 0, 0);
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
				mFocusView.clearAnimation();
				int newPos = mStartPos + mItemWidth * mCurrentIdx;
				mLayoutParams.setMargins(newPos, 0, 0, 0);
				mFocusView.setLayoutParams(mLayoutParams);
			}
		});
		this.mFocusView.clearAnimation();
		this.mFocusView.setAnimation(animation);
		animation.startNow();
		this.getView().invalidate();
	}
	
	private boolean subViewAccept(int keyCode) {
		TVWidget widget = this.mWidgets.get(this.mCurrentIdx);
		if (widget != null) {
			return widget.accept(keyCode);
		}
		return false;
	}
	
	private TVWidget getSubView() {
		if (this.mCurrentIdx < 0 || this.mCurrentIdx >= this.mWidgets.size()) {
			return null;
		}
		return this.mWidgets.get(this.mCurrentIdx);
	}
	
	private boolean dispatchKey(int keyCode) {
		TVWidget widget = this.getSubView();
		if (widget != null) {
			return widget.onKeyDown(keyCode);
		}
		return false;
	}
	
	private void focusSubView(boolean f) {
		TVWidget widget = this.getSubView();
		if (widget != null) {
			widget.focus(f);
		}
	}
	
	public boolean onKeyDown(int keyCode) {
		boolean accept = this.subViewAccept(keyCode);
		if (this.mFocus) {
			if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
				this.changeFocusIdx(-1);
				this.focus(true);
				this.focusSubView(false);
				return true;
			}
			if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
				this.changeFocusIdx(1);
				this.focus(true);
				this.focusSubView(false);
				return true;
			}
			if (KeyEvent.KEYCODE_DPAD_UP == keyCode ||
					KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
					KeyEvent.KEYCODE_ENTER == keyCode) {
				if (accept) {
					this.focus(false);
					this.focusSubView(true);
				}
				return true;
			}
			if (KeyEvent.KEYCODE_MENU == keyCode) {
				if(this.dispatchKey(keyCode))
				{
					this.hide();
					return true;	
				}
			}
			if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode) {
				return true;
			}
		} else {
			if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode && !accept) {
				this.focus(true);
				this.focusSubView(false);
				this.changeFocusIdx(-1);
				return true;
			}
			if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode && !accept) {
				this.focus(true);
				this.focusSubView(false);
				this.changeFocusIdx(1);
				return true;
			}
			if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode && !accept) {
				this.focus(true);
				this.focusSubView(false);
				return true;
			}
			if (KeyEvent.KEYCODE_MENU == keyCode) {
				if(this.dispatchKey(keyCode) == true)
				{
					this.focus(true);
					this.focusSubView(false);
				}
				return true;	
			}
		}
		return this.dispatchKey(keyCode);
	}
	
	private void changeFocusIdx(int diff) {
		int oldIdx = this.mCurrentIdx;
		int size = this.mWidgets.size();
		this.mCurrentIdx += diff;
		if (this.mCurrentIdx >= size) {
			this.mCurrentIdx -= size;
		}
		if (this.mCurrentIdx < 0) {
			this.mCurrentIdx += size;
		}
		this.startAnimation(oldIdx);
		this.hideViewsExcept(this.mCurrentIdx);
	}
	
	private void hideViewsExcept(int idx) {
		for (int i = 0; i < this.mWidgets.size(); ++i) {
			TVWidget w = this.mWidgets.get(i);
			if (i == idx) {
				w.show();
			} else {
				w.hide();
			}
		}
	}
	
	@Override
	public void show() {
		if (this.getView().getVisibility() != View.VISIBLE) {
			super.show();
			this.TVTypeChange();
			this.hideViewsExcept(this.mCurrentIdx);
			this.mActivity.hideDialog(); 

		}
	}
	
	@Override
	public void hide() {
		if (this.getView().getVisibility() == View.VISIBLE) {
			super.hide();
			this.mCurrentIdx=0;
			this.focus(true);
			this.focusSubView(false);			
			this.hideViewsExcept(-1);
			this.mActivity.showDialog();

			if(this.biref_show_status()) {
				TVEpgView epgView = (TVEpgView)this.mEpgWidget;
				epgView.hidebrief();
			}
		}		
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
	public boolean accept(int keyCode) {
		return true;
	}
	
	@Override
	public void appNotify(String type, Object value) {
		for (TVWidget w : this.mWidgets) {
			w.appNotify(type, value);
		}
	}
	
	public boolean biref_show_status() {
		TVEpgView v = (TVEpgView)this.mEpgWidget;
		if (v != null && v.biref_show_status() == true) {
			return true;
		}
		else{
			return false;
		}
	}
}
