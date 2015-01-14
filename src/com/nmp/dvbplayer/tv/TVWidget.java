package com.nmp.dvbplayer.tv;

import android.view.View;
import android.view.animation.AlphaAnimation;

public abstract class TVWidget {	
	public void show() {
		View v = this.getView();
		if (v != null && v.getVisibility() != View.VISIBLE) {
			v.setVisibility(View.VISIBLE);
			AlphaAnimation animation = new AlphaAnimation(0, 1);
			animation.setDuration(TVActivity.AnimTime);
			v.setAnimation(animation);
			animation.startNow();
			v.invalidate();
		}
	}
	
	public void hide() {
		View v = this.getView();
		if (v != null && View.VISIBLE == v.getVisibility()) {
			v.setVisibility(View.GONE);
		}
	}
	
	public void appNotify(String type, Object value) { }
	
	protected abstract View getView();
	
	public abstract boolean accept(int keyCode);
	
	public abstract boolean onKeyDown(int keyCode);
	
	public abstract void focus(boolean f);
}
