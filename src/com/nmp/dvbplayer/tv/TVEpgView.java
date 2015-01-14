package com.nmp.dvbplayer.tv;

import java.util.Calendar;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import com.alitech.dvb.DvbEpg;
import com.alitech.dvb.DvbTime;
import com.nmp.dvbplayer.tv.TVUtility.TimeUtil;
import com.nmp.dvbplayer.tv.data.EpgItem;
import com.nmp.dvbplayer.tv.data.EpgList;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.tv.data.TVProgram;
import com.nmp.dvbplayer.tv.data.EpgList.LangCode;
import com.nmp.dvbplayer.R;

import android.content.res.Resources;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.text.Spannable;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams;

public class TVEpgView extends TVWidget {
	private static final String Tag = TVEpgView.class.getName();
	private class EpgTask extends AsyncTask<TVChannel, Void, EpgItem[]> {
		@Override
		protected EpgItem[] doInBackground(TVChannel... params) {			
			EpgList epgList = mActivity.getEpgList();
			
			return epgList.getEpg(mDayDiff, params[0], LangCode.Unknown);
		}
		@Override
		protected void onPostExecute(EpgItem[] result) {
			mEpgTask = null;
			TVChannel channel = mActivity.getChannelManager().getSelChannel();
			if (result != null && channel != null &&
					channel.getType() != TVChannel.NET_TURN_NODE &&
					!mActivity.supportLiveBack()) {
				// 因为直接更改result会影响到cache中的数据，所以这里需要做拷贝
				EpgItem[] oldResult = result;
				result = new EpgItem[oldResult.length];
				for (int i = 0; i < oldResult.length; ++i) {
					EpgItem oldItem = oldResult[i];
					EpgItem newItem = new EpgItem(oldItem.getTitle());
					newItem.setStartTime(oldItem.getStartTime());
					newItem.setEndTime(oldItem.getEndTime());
					newItem.setEpgType(oldItem.getEpgType());
					newItem.setLiveBack(false);
					newItem.setBrief(oldItem.getBrief());
					newItem.setDetail(oldItem.getDetail());
					result[i] = newItem;
				}
			}
			mEpgArray = result;
			updateIndex();
			updateEpgList(true);
		}
	};
	
	class mScrollingMovementMethod extends ScrollingMovementMethod {
		public boolean ScrollingUp(TextView widget, Spannable buffer) {
			return super.up(widget, buffer);
		}
		
		public boolean ScrollingDown(TextView widget, Spannable buffer) {
			return super.down(widget, buffer);
		}
		
		public boolean ScrollingPageUp(TextView widget, Spannable buffer) {
			return super.pageUp(widget, buffer);
		}
		
		public boolean ScrollingPageDown(TextView widget, Spannable buffer) {
			return super.pageDown(widget, buffer);
		}
	}
	
	private TVActivity mActivity;
	private View mSelfView;
	private View mFocusView;
	private LayoutParams mFocusLayout;
	
	private View mEPGBriefView;
	
	private EpgItem[] mEpgArray;
	private int mFocusIdx;
	private int mSelectedIdx;
	private boolean mFocus;
	
	private int mItemHeight;
	private int mStartY;
	private int mPageSize;
	private int mDayDiff;
	private int mNavDir; // 0 for enter app, 1 for move left, 2 for move right
	
	private EpgTask mEpgTask;
	
	private mScrollingMovementMethod mScrolling;
	
	public TVEpgView(TVActivity activity) {
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_epg_list, (RelativeLayout)view);
		View.inflate(activity, R.layout.tv_epg_brief, (RelativeLayout)view);
		this.mSelfView = this.mActivity.findViewById(R.id.tv_epg_list);		
		this.mFocusView = this.mSelfView.findViewById(R.id.tv_epg_focus);
		this.mEPGBriefView = this.mActivity.findViewById(R.id.tv_epg_brief);
		this.mFocusLayout = new LayoutParams(this.mFocusView.getLayoutParams());
		this.focus(false);
		this.hide();
		this.hidebrief();
		
		this.mEpgArray = null;
		this.mFocusIdx = 0;
		this.mSelectedIdx = -1;
		this.mItemHeight = 48;
		this.mStartY = 48;
		this.mPageSize = 10;
		this.mDayDiff = 0;
		this.mNavDir = 0;
		
		this.mEpgTask = null;
		
		this.mScrolling = new mScrollingMovementMethod();
	}
	
	/**
	 * 计算当前播放的EPG的下标
	 */
	private void updateIndex() {
		TVChannel channel = this.mActivity.getChannelManager().getSelChannel();
		if (null == this.mEpgArray || null == channel) {
			Log.e(Tag, "channel is null or epg data is empty!");
			return;
		}
		
		if (this.mNavDir > 0) {
			this.mFocusIdx = 0;
		} else {
			this.mFocusIdx = this.mEpgArray.length - 1;
		}
		
		if (this.mDayDiff != 0) {
			return;
		}
		
		this.mSelectedIdx = 0;
		if (TVChannel.NET_TURN_NODE == channel.getType()) {
			TVProgram program = this.mActivity.getChannelManager().getSelProgram();
			if (program != null) {
				for (int i = 0; i < this.mEpgArray.length; ++i) {
					if (program.getName().equals(this.mEpgArray[i].getTitle())) {
						this.mSelectedIdx = i;
						break;
					}
				}
			}
		} else {	
			DvbTime stream_time = DvbEpg.getStreamTime(0);
			TimeUtil tu = new TimeUtil();	
			int now;
			if(stream_time != null) {
				now = tu.getMinutes(stream_time.getTimeSting());
			}
			else {
				now = tu.getMinutes(tu.getCurrentTime());
			}

			for (int i = this.mEpgArray.length - 1; i >= 0; --i) {
				int minute = tu.getMinutes(this.mEpgArray[i].getStartTime());
				if (now > minute) {
					this.mSelectedIdx = i;
					break;
				}
			}			
		}
		if (0 == this.mNavDir) {
			this.mFocusIdx = this.mSelectedIdx;
		}
	}
	
	private void updateEpgList(boolean showEmpty) {
		LinearLayout epgListView;
		int rid = R.id.tv_epg_items;
		epgListView = (LinearLayout)this.mSelfView.findViewById(rid);
		rid = R.id.tv_epg_now;
		TextView epgNowView = (TextView)this.mSelfView.findViewById(rid);
		View epgLeftView = this.mSelfView.findViewById(R.id.tv_epg_pre);
		View epgRightView = this.mSelfView.findViewById(R.id.tv_epg_next);
		Resources res = this.mActivity.getResources();
		TVChannel channel = this.mActivity.getChannelManager().getSelChannel();
		
		boolean isturn = (channel != null && 
				channel.getType() == TVChannel.NET_TURN_NODE);
				
		if (channel != null && TVChannel.NET_TURN_NODE == channel.getType()) {
			epgNowView.setText(channel.getName());
		} else {
			String timeTxt; //= new TimeUtil().getDate(this.mDayDiff);
			
			DvbTime stream_time;
			stream_time = DvbEpg.getStreamTime(this.mDayDiff);
			
			if(stream_time == null) {
				timeTxt = new TimeUtil().getDate(this.mDayDiff);
			}
			else {
				timeTxt = stream_time.getDateSting();
			}
				
			
			if (0 == this.mDayDiff) {
				timeTxt += " " + res.getString(R.string.tv_epg_today);
			}
			epgNowView.setText(timeTxt);
		}
		epgListView.removeAllViews();
		
		int size = 0;
		if (this.mEpgArray != null) {
			size = this.mEpgArray.length;
		}
		size = (size + this.mPageSize - 1) / this.mPageSize - 1;
		if ((isturn || this.mDayDiff <= this.getMinDayDiff()) &&
				this.mFocusIdx < this.mPageSize) {
			epgLeftView.setVisibility(View.INVISIBLE);
		} else {
			epgLeftView.setVisibility(View.VISIBLE);
		}
		if ((isturn || this.mDayDiff >= this.getMaxDayDiff()) &&
				this.mFocusIdx >= size * this.mPageSize) {
			epgRightView.setVisibility(View.INVISIBLE);
		} else {
			epgRightView.setVisibility(View.VISIBLE);
		}
		
		if (null == this.mEpgArray) {
			if (channel != null && showEmpty) {
				String txt = " " + res.getString(R.string.tv_no_epg);
				epgNowView.setText(channel.getName() + txt);
			} else {
				String txt = res.getString(R.string.tv_epg_loading);
				epgNowView.setText(txt + "...");
			}
			return;
		}
		//每屏显示10条EPG
		int startIdx = this.mFocusIdx - this.mFocusIdx % this.mPageSize;
    	for (int i = 0; i < this.mPageSize; ++i) {
    		if (startIdx + i >= this.mEpgArray.length) {
    			break;
    		}
    		
    		EpgItem epgItem = this.mEpgArray[startIdx + i];    		
    		LinearLayout.LayoutParams lp = null;
    		int w = LinearLayout.LayoutParams.MATCH_PARENT;
			lp = new LinearLayout.LayoutParams(w, this.mItemHeight);
			lp.gravity = Gravity.CENTER_VERTICAL;
			lp.setMargins(50, 0, 25, 0);
			TextView v = new TextView(this.mActivity);
			v.setSingleLine();
			v.setHorizontallyScrolling(false);
			v.setEllipsize(null);
			v.setLayoutParams(lp);
			v.setTextSize(TypedValue.COMPLEX_UNIT_PX, 32);
			if (startIdx + i == this.mSelectedIdx) {
				v.setTextColor(res.getColor(R.color.tv_yellow));
			} else {
				v.setTextColor(res.getColor(R.color.tv_white));
			}
			v.setText(epgItem.getStartTime() + " " + epgItem.getTitle());
			if (epgItem.canLiveBack()) {
				Drawable playIcon = res.getDrawable(R.drawable.tv_epg_play);
				playIcon.setBounds(0, 0, 48, 48);
				v.setCompoundDrawables(null, null, playIcon, null);
			}
			epgListView.addView(v);
    	}
    	
    	int newPos = mStartY + mItemHeight * (mFocusIdx % mPageSize);
		mFocusLayout.setMargins(0, newPos, 0, 0);
		mFocusView.setLayoutParams(mFocusLayout);
	}
	
	private void requestEpgList() {
		this.mFocusIdx = 0;
		this.mSelectedIdx = -1;
		this.mEpgArray = null;
		TVChannel channel = this.mActivity.getChannelManager().getSelChannel();
		if (null == channel) {			
			this.updateEpgList(false);
			return;
		}
		
		if (this.mEpgTask != null) {
			this.mEpgTask.cancel(true);
		}		
		this.mEpgTask = new EpgTask();
		Executor exec = Executors.newCachedThreadPool();
		this.mEpgTask.executeOnExecutor(exec, channel);
		this.updateEpgList(false);
	}
	
	/**
	 * 我们只能在当前显示的10条EPG上移动光标，上下键不会把光标移动到其他的EPG上，即使是同一天的！
	 * @param diff
	 */
	private void changeFocusIdx(int diff) {
		View v = this.mEPGBriefView;
		if (null == this.mEpgArray || v.getVisibility() == View.VISIBLE) {
			if(v.getVisibility() == View.VISIBLE) {
				TextView mTextView;
				mTextView = (TextView)v.findViewById(R.id.tv_epg_brief_content);
				if(diff == 1) {
					mScrolling.ScrollingDown(mTextView, null);
				}
				else if (diff == -1) {
					mScrolling.ScrollingUp(mTextView, null);
				}
				
			}
			return;
		}
		int oldIdx = this.mFocusIdx;
		int newIdx = this.mFocusIdx + diff;
		// 超出了有效的下标
		if (newIdx < 0 || newIdx >= this.mEpgArray.length) {
			return;
		}
		// 超出了最上边的EPG的下标
		if (newIdx < oldIdx / this.mPageSize * this.mPageSize) {
			return;
		}
		// 超出了最后边的EPG的下标
		if (newIdx >= (oldIdx - oldIdx % this.mPageSize + this.mPageSize)) {
			return;
		}
		this.mFocusIdx = newIdx;
		
		int deltaY = this.mItemHeight * (this.mFocusIdx - oldIdx);
		TranslateAnimation animation = new TranslateAnimation(0, 0, 0, deltaY);
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
				int newPos = mStartY + mItemHeight * (mFocusIdx % mPageSize);
				mFocusLayout.setMargins(0, newPos, 0, 0);
				mFocusView.setLayoutParams(mFocusLayout);
			}
		});
		this.mFocusView.clearAnimation();
		this.mFocusView.setAnimation(animation);
		animation.startNow();
		this.getView().invalidate();
	}
	
	private int getMaxDayDiff() {
		/*
		int max = Calendar.SATURDAY + 1;
		Calendar c = Calendar.getInstance();
		int weekday = c.get(Calendar.DAY_OF_WEEK);
		if (Calendar.SUNDAY == weekday) {
			weekday = max;
		}
		return max - weekday;*/
		return 6;
	}
	
	private int getMinDayDiff() {
		//return -7;
		return 0;
	}
	
	private void showNewList(int dir) {
		View v = this.mEPGBriefView;
		if (v.getVisibility() == View.VISIBLE) {
			return;
		}
		
		TVChannel chn = this.mActivity.getChannelManager().getSelChannel();
		this.mNavDir = dir;
		int m = this.mFocusIdx % this.mPageSize;
		if (dir < 0) {
			if (this.mFocusIdx >= this.mPageSize) {
				this.mFocusIdx -= (m + 1);
				this.updateEpgList(false);
			} else {
				if (chn != null && chn.getType() != TVChannel.NET_TURN_NODE) {
					if (this.mDayDiff > this.getMinDayDiff()) {
						this.mDayDiff -= 1;
						this.requestEpgList();
					}
				}
			}
			return;
		}
		
		if (dir > 0) {
			int len = 0;
			if (this.mEpgArray != null) {
				len = this.mEpgArray.length;
			}
			len = (len + this.mPageSize - 1) / this.mPageSize - 1;
			if (this.mFocusIdx < len * this.mPageSize) {
				this.mFocusIdx += this.mPageSize;
				this.mFocusIdx -= m;
				this.updateEpgList(false);
			} else {
				if (chn != null && chn.getType() != TVChannel.NET_TURN_NODE) {
					if (this.mDayDiff < this.getMaxDayDiff()) {
						this.mDayDiff += 1;
						this.requestEpgList();
					}
				}
			}
		}
	}
	
	@Override
	public void show() {
		if (this.getView().getVisibility() != View.VISIBLE) {			
			this.mEpgArray = null;
			this.mFocusIdx = 0;
			this.mSelectedIdx = -1;
			this.mDayDiff = 0;
			this.mNavDir = 0;			
			this.mEpgTask = null;			
			this.requestEpgList();
			super.show();
		}
	}
	
	@Override
	public boolean accept(int keyCode) {		
		if (this.mFocus) {
			if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode) {
				if (null == this.mEpgArray) {
					return false;
				}
				// 如果下标在屏幕上的最后那条EPG，不接收下键，这样子可以把自己的焦点让给其他部分
				if (this.mFocusIdx >= this.mEpgArray.length - 1 ||
						this.mFocusIdx % this.mPageSize == this.mPageSize - 1) {
					return false;
				}
			}
		} else {
			// 只能通过这几个键获得按键
			return (KeyEvent.KEYCODE_DPAD_UP == keyCode ||
					KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
					KeyEvent.KEYCODE_ENTER == keyCode);
		}
		return true;
	}
	
	
	public void showBrief() {
		View v = this.mEPGBriefView;
	
		
		if (v != null && v.getVisibility() != View.VISIBLE) {
			this.hide();
			EpgItem item = this.mEpgArray[this.mFocusIdx];
			TextView mTextView = null;
			String brief = null;
			
			mTextView = (TextView)v.findViewById(R.id.tv_epg_brief_title);
			mTextView.setText(item.getTitle());
			
			mTextView = (TextView)v.findViewById(R.id.tv_epg_brief_time);
			mTextView.setText(item.getStartTime()+" -- " + item.getEndTime());

			mTextView = (TextView)v.findViewById(R.id.tv_epg_brief_content);
			brief = item.getBrief() + "\n" + item.getDetail();
			if(brief == "") {
				mTextView.setText("没有节目简介！");
			}
			else {
				mTextView.setText(brief);
			}
			
			mTextView.setMovementMethod(ScrollingMovementMethod.getInstance());
			
			//mTextView.setMovementMethod(ScrollingMovementMethod.getInstance());
			v.setVisibility(View.VISIBLE);
			//this.mActivity.setContentView(v);
			//v.setVisibility(View.VISIBLE);
			v.invalidate();
		}
	}
	
	public void hidebrief() {
		View v = this.mEPGBriefView;
		if (v != null && View.VISIBLE == v.getVisibility()) {
			v.setVisibility(View.GONE);
		}
	}
	
	public boolean biref_show_status() {
		View v = this.mEPGBriefView;
		if (v != null && View.VISIBLE == v.getVisibility()) {
			return true;
		}
		else{
			return false;
		}
	}
	
	@Override
	public boolean onKeyDown(int keyCode) {
		if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
			this.showNewList(-1);
			return true;
		}
		
		if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			this.showNewList(1);
			return true;
		}
		
		if (KeyEvent.KEYCODE_DPAD_UP == keyCode) {
			this.changeFocusIdx(-1);
			return true;
		}
		
		if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode) {
			this.changeFocusIdx(1);
			return true;
		}
		
		if (KeyEvent.KEYCODE_DPAD_CENTER == keyCode ||
				KeyEvent.KEYCODE_ENTER == keyCode) {			
			if (null == this.mEpgArray) {
				return true;
			}
			if (this.mFocusIdx < 0 || this.mFocusIdx >= this.mEpgArray.length) {
				return true;
			}
			//EpgItem item = this.mEpgArray[this.mFocusIdx];
			this.showBrief();
			return true;
		}
		
		if (KeyEvent.KEYCODE_BACK == keyCode ||
				KeyEvent.KEYCODE_ESCAPE == keyCode){
			this.hidebrief();
			this.show();
			return true;
		}
		if (KeyEvent.KEYCODE_MENU == keyCode)
			return true;
		return false;
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

}
