package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.nmp.dvbplayer.R;

import android.content.Context;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

public class TVNumPicker extends LinearLayout {

	private int                 mIntegerBits;
	private int                 mFractionBits;
	private int                 mFocusIdx;
	private ArrayList<TextView> mViewList;
	private ArrayList<Integer>  mValueList;
	private TVNumberParam       mParam;
	
	public TVNumPicker(Context context) {
		super(context);
		this.init();
	}

	public TVNumPicker(Context context, AttributeSet attrs) {
		super(context, attrs);
		this.init();
	}

	public TVNumPicker(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
		this.init();
	}
	
	private void init() {
		this.mIntegerBits = 0;
		this.mFractionBits = 0;
		this.mFocusIdx = 0;
		this.mViewList = new ArrayList<TextView>();
		this.mValueList = new ArrayList<Integer>();
		this.mParam = null;
	}
	
	public void setParam(TVNumberParam param) {
		this.mParam = param;
		this.mIntegerBits = this.mParam.getIntegerBits();
		this.mFractionBits = this.mParam.getFractionBits();
		this.mFocusIdx = 0;
		this.setup();
	}
	
	private void setInitVal() {
		this.mValueList.clear();
		double v = Math.pow(10, this.mFractionBits) * this.mParam.getValue();
		int val = (int)v;
		int num = this.mIntegerBits + this.mFractionBits;
		for (int i = 0; i < num; ++i) {
			this.mValueList.add(0, val % 10);
			val = val / 10;
		}
	}
	
	private void setup() {
		this.mViewList.clear();
		this.removeAllViews();
		this.setInitVal();
		
		int num = this.mIntegerBits + this.mFractionBits;
		int resId = R.layout.tv_num;
		for (int i = 0; i < num; ++i) {
			View.inflate(this.getContext(), resId, this);
		}
		
		if (this.mFractionBits > 0) {
			View.inflate(this.getContext(), resId, this);
			num += 1;
		}
		
		for (int i = 0; i < num; ++i) {
			TextView v = (TextView)this.getChildAt(i);
			if (i != this.mIntegerBits) {
				this.mViewList.add(v);
			} else {
				v.setText(".");
			}
		}
		
		num = this.mIntegerBits + this.mFractionBits;
		for (int i = 0; i < num; ++i) {
			TextView v = this.mViewList.get(i);
			int val = this.mValueList.get(i);
			v.setText(String.valueOf(val));
		}		
		changeFocus(0);
	}
	
	private void changeFocus(int diff) {
		int num = this.mIntegerBits + this.mFractionBits;
		this.mFocusIdx += diff;
		this.mFocusIdx %= num;
		this.mFocusIdx += num;
		this.mFocusIdx %= num;
		
		View v = this.mViewList.get(this.mFocusIdx);
		for (TextView view : this.mViewList) {
			int resId = (v == view) ? R.drawable.tv_num_bg : 0;
			view.setBackgroundResource(resId);
		}
	}
	
	private void changeValue(int diff) {
		int val = this.mValueList.get(this.mFocusIdx);
		val += diff;
		val %= 10;
		val += 10;
		val %=10;
		this.mValueList.set(this.mFocusIdx, val);
		this.mViewList.get(this.mFocusIdx).setText(String.valueOf(val));
		
		this.saveValue();
	}
	
	private void saveValue() {
		float value = 0.0f;
		for (Integer v : this.mValueList) {
			value *= 10;
			value += v;
		}
		for (int i = 0; i < this.mFractionBits; ++i) {
			value /= 10.0f;
		}
		this.mParam.setValue(value);
	}
	
	private void numberInput(int num) {
		this.mValueList.set(this.mFocusIdx, num);
		this.mViewList.get(this.mFocusIdx).setText(String.valueOf(num));
		this.saveValue();
		this.changeFocus(1);
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
			changeFocus(-1);
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
			changeFocus(1);
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
			changeValue(1);
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
			changeValue(-1);
			return true;
		}
		if (keyCode >= KeyEvent.KEYCODE_0 && keyCode <= KeyEvent.KEYCODE_9) {
			numberInput(keyCode - KeyEvent.KEYCODE_0);
			return true;
		}
		return super.onKeyDown(keyCode, event);
	}
}
