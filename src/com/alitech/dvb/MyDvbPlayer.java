package com.alitech.dvb;

import android.content.Context;
import android.media.MediaPlayer;
import android.net.Uri;
import android.util.Log;
import com.alitech.dvb.DvbPlayer;

public class MyDvbPlayer extends MediaPlayer {
	//DvbPlayer
	private String TAG = MyDvbPlayer.class.getName();
	//private  MediaPlayer.OnPreparedListener mOnPreparedListener = null;
	//private static final int STATE_ERROR              = -1;
	private static final int STATE_IDLE               = 0;
	//private static final int STATE_PREPARING          = 1;
	//private static final int STATE_PREPARED           = 2;
	private static final int STATE_PLAYING            = 3;
	private static final int STATE_PAUSED             = 4;
	//private static final int STATE_PLAYBACK_COMPLETED = 5;
	private static final int STATE_STOP             = 6;
	
	private int mFrameLeft;
	private int mFrameTop;
	private int mFrameRight;
	private int mFrameBottom;
	String mSrc;
	private int mState;
	public MyDvbPlayer() {
		// TODO Auto-generated constructor stub
		mFrameLeft =-1;
		mState = STATE_IDLE;
	}	
	
	public void setOnPreparedListener(MediaPlayer.OnPreparedListener l)
	{
		//mOnPreparedListener = l;
		//super.setOnPreparedListener(l);
	}
	
	public void setOnCompletionListener()
	{
		
	}
	
	public void setOnErrorListener()
	{
		
	}
	
	public void setOnInfoListener()
	{
		
	}
	
	public void setOnBufferingUpdateListener()
	{
		
	}
	
	public void setOnSeekCompleteListener()
	{
		
	}
	
	public void setAudioStreamType()
	{
		
	}
	
	public int getDuration()
	{
		return -1;
	}
	
	public void prepareAsync()
	{
		//super.prepareAsync();
		//mState = STATE_PREPARING;
	}	
	
	public void seekTo(int mSec)
	{
		
	}
	
	public void setDataSource(Context ctx, Uri uri)
	{
		mSrc = uri.toString();
		Log.d(TAG, mSrc);
		DvbPlayer.configNim(0);
	}
	
	public void start()
	{
		mState = STATE_PLAYING;
		DvbChannelNode node;
		node = DvbChannelNode.fromUrl(mSrc);
		DvbPlayer.start(node, true);
		//Log.i(TAG, "start 1");
		
	}
	
	public void pause()
	{
		if(STATE_PLAYING == mState){
			DvbPlayer.stop(true);
			
		}
		mState = STATE_PAUSED;
		//Log.i(TAG, "pause");
		
	}
	
	@Override
	public void stop()
	{
		if(STATE_PLAYING == mState){
			DvbPlayer.stop(true);
			
		}
		mState = STATE_STOP;
		//Log.i(TAG, "stop 1");
		
	}
	
	@Override
	public void reset()
	{
		if(STATE_PLAYING == mState){
			DvbPlayer.stop(true);
			
		}
		super.reset();
		mState = STATE_IDLE;
		Log.i(TAG, "reset 1");
		
	}
	
	@Override
	public void release()
	{
		mState = STATE_IDLE;
		super.release();
		//Log.i(TAG, "release 1");
		
	}
	
	@Override
	public void setVideoViewFrame(int left, int top, int right, int bottom) {
		super.setVideoViewFrame(left,top,right,bottom);
		if((mFrameLeft != left)||(mFrameTop != top)||(mFrameRight != right)||(mFrameBottom != bottom)){
			Log.i(TAG,"gavin setVideoViewFrame frame:"+left+" "+top+" "+right + " " +bottom);
			DvbPlayer.setPos(left,top,right,bottom);
			mFrameLeft = left;
			mFrameTop = top;
			mFrameRight = right;
			mFrameBottom = bottom;
		}
	}
}
