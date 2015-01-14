package com.nmp.dvbplayer.common;

import com.alitech.dvb.DvbPlayer;
import com.nmp.dvbplayer.R;

import android.app.Activity;
import android.app.Service;
import android.content.Context;
import android.content.SharedPreferences;
import android.media.AudioManager;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

public class VolumeBar {
	private String LOGTAG = "VolumeBar";
	private Toast mToast;
	private View mView;
	private ProgressBar mLevel;
	private ImageView mSpeaker;
	private TextView mDigitNum;
	
	
	private boolean mMute;
	private int mRelativeVolume = 0;
	private int mRelativeVolumeMax;
	private int mAbsoluteVolumeMax;
	private final static int DEFAULT_VOLUME = 15;
	private final static String KEY_VOL = "Volume";
	private final static String KEY_MUTE = "Mute";
	
	private AudioManager mAudioManager;
	private SharedPreferences mSharedPreferences;
	private SharedPreferences.Editor mSharedPreferencesEditor;
	
	
	public VolumeBar(Context context) {
		// TODO Auto-generated constructor stub
		mView = LayoutInflater.from(context).inflate(R.layout.volume_bar, null);
		mLevel = (ProgressBar) mView.findViewById(R.id.vol_bar_id_progress);
		mSpeaker = (ImageView) mView.findViewById(R.id.vol_bar_id_speaker);
		mDigitNum = (TextView) mView.findViewById(R.id.vol_bar_id_volume);
		
		mRelativeVolumeMax = mLevel.getMax();
		mSharedPreferences = context.getSharedPreferences("Volume", Activity.MODE_PRIVATE);
		mSharedPreferencesEditor = mSharedPreferences.edit();
		
		mRelativeVolume = mSharedPreferences.getInt(KEY_VOL, DEFAULT_VOLUME);
		mMute = mSharedPreferences.getBoolean(KEY_MUTE, false);
		
		mAudioManager = (AudioManager) context.getSystemService(Service.AUDIO_SERVICE);
		mAbsoluteVolumeMax = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
//		mRelativeVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
//		mRelativeVolume = mRelativeVolume * mRelativeVolumeMax / mAbsoluteVolumeMax;
		
		mToast = new Toast(context);
		mToast.setView(mView);
		mToast.setDuration(Toast.LENGTH_SHORT);
		mToast.setGravity(Gravity.TOP, 0, 110);
		mDigitNum.setText(String.valueOf(mRelativeVolume));
		mute(mMute);
		Log.i(LOGTAG, "VolumeBar init, current volume: " + mRelativeVolume);
	}
	
	public void volumeUp() {
		if(mMute == true)
			mute(!mMute);
		
		if(mRelativeVolume < mRelativeVolumeMax) {
			mRelativeVolume++;
			setVolume(mRelativeVolume);
			mLevel.setProgress(mRelativeVolume);
			mDigitNum.setText(String.valueOf(mRelativeVolume));
			
		}
		mToast.show();
		
		/* save volume */
		mSharedPreferencesEditor.putInt(KEY_VOL, mRelativeVolume);
		mSharedPreferencesEditor.commit();
		
		Log.i(LOGTAG, "volume up to: " + mRelativeVolume);
	}
	
	public void volumeDown() {
		if(mMute == true)
			mute(!mMute);

		if(mRelativeVolume > 0) {
			mRelativeVolume--;
			setVolume(mRelativeVolume);
			mLevel.setProgress(mRelativeVolume);		
			mDigitNum.setText(String.valueOf(mRelativeVolume));
		}
		mToast.show();

		/* save volume */
		mSharedPreferencesEditor.putInt(KEY_VOL, mRelativeVolume);
		mSharedPreferencesEditor.commit();
		
		Log.i(LOGTAG, "volume up down: " + mRelativeVolume);
	}
	
	public void volumeMute() {
		mute(!mMute);
		mToast.show();
		mSharedPreferencesEditor.commit();
		Log.i(LOGTAG, "volume mute status: " + mMute);
	}
	
	private void mute(boolean mute) {
		int flag;
		mMute = mute;
		if(mMute == true) {
			mLevel.setProgress(0);
			mLevel.setSecondaryProgress(mRelativeVolume);
			mSpeaker.setBackgroundResource(R.drawable.vol_speaker_mute);
			setVolume(0);
		} else {
			mLevel.setProgress(mRelativeVolume);
			mLevel.setSecondaryProgress(0);
			mSpeaker.setBackgroundResource(R.drawable.vol_speaker);
			setVolume(mRelativeVolume);
		}
		//mAudioManager.setStreamMute(AudioManager.STREAM_MUSIC, mMute);
		mSharedPreferencesEditor.putBoolean(KEY_MUTE, mMute);
		if(mMute)
                    flag = 1;
		else flag =0;
		DvbPlayer.SetVolMute(flag);	
	}
	
	private void setVolume(int value) {
		int absVolume = value * mAbsoluteVolumeMax / mRelativeVolumeMax;  
		Log.i(LOGTAG, "absVolume: " + absVolume + ", max: " + mAbsoluteVolumeMax);
		mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC, absVolume, 0);
	}
	
	public int getVolume() {
		int absVolume = mRelativeVolume * mAbsoluteVolumeMax / mRelativeVolumeMax;
		return absVolume;
	}

	public boolean getMuteState(){
		return mMute ;
	}
}