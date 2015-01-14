package com.nmp.dvbplayer.tv;

import java.util.Locale;

import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.R;

import android.content.res.Resources;
import android.view.KeyEvent;
import android.view.View;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class TVFavView extends TVWidget {
	private TVActivity mActivity;
	private TextView   mSelfView;
	
	public TVFavView(TVActivity activity) {
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_favorite_view, (RelativeLayout)view);
		this.mSelfView = (TextView)this.mActivity.findViewById(R.id.tv_favorite_view);
		this.hide();
	}
	
	@Override
	public void show() {
		this.setViewText(true);
		super.show();
	}

	@Override
	protected View getView() {
		return this.mSelfView;
	}

	@Override
	public boolean accept(int keyCode) {
		if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||
				keyCode == KeyEvent.KEYCODE_ENTER) {
			this.mActivity.toggleFavorite();
			this.setViewText(false);
		}
		return false;
	}

	@Override
	public boolean onKeyDown(int keyCode) {
		return true;
	}
	
	private void setViewText(boolean init) {
		TVChannel chn = this.mActivity.getChannelManager().getSelChannel();
		if (chn != null) {
			Resources res = this.mActivity.getResources();
			String txt = "";
			if (init) {
				String str1 = res.getString(R.string.tv_epg_fav1);
				String str2 = res.getString(R.string.tv_epg_fav2);
				txt = chn.isFavorite() ? str2 : str1;
				txt = String.format(Locale.CHINA, txt, chn.getName());
			} else {
				String tpl = res.getString(R.string.tv_epg_fav3);
				String str1 = res.getString(R.string.tv_epg_add);
				String str2 = res.getString(R.string.tv_epg_del);
				txt = chn.isFavorite() ? str1 : str2;
				txt = String.format(Locale.CHINA, tpl, txt, chn.getName());
			}
			this.mSelfView.setText(txt);
		}
	}

	@Override
	public void focus(boolean f) {
		;
	}
}
