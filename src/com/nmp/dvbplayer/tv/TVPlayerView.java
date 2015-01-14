/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.nmp.dvbplayer.tv;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnBufferingUpdateListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.net.Uri;
import android.util.AttributeSet;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.io.IOException;

import com.alitech.dvb.MyDvbPlayer;

/**
 * Displays a video file.  The VideoView class
 * can load images from various sources (such as resources or content
 * providers), takes care of computing its measurement from the video so that
 * it can be used in any layout manager, and provides various display options
 * such as scaling and tinting.
 */
public class TVPlayerView extends SurfaceView {
    private String TAG = TVPlayerView.class.getName();
    
    // all possible internal states
    public static final int STATE_ERROR              = -1;
    public static final int STATE_IDLE               = 0;
    public static final int STATE_PREPARING          = 1;
    public static final int STATE_PREPARED           = 2;
    public static final int STATE_PLAYING            = 3;
    public static final int STATE_PAUSED             = 4;
    public static final int STATE_PLAYBACK_COMPLETED = 5;

    private Uri         mUri;
    private int         mDuration;
    private int         mType;

    private int mCurrentState =            STATE_IDLE;
    private SurfaceHolder                  mSurfaceHolder = null;
    private MediaPlayer                    mMediaPlayer = null; 
    
    private OnPreparedListener             mOnPreparedListener;
    private OnErrorListener                mOnErrorListener;
    private OnBufferingUpdateListener      mOnBufferingUpdateListener;
    private OnInfoListener                 mOnInfoListener;
    private OnCompletionListener           mOnCompletionListener;
    private OnSeekCompleteListener         mOnSeekCompleteListener;
    
    private int                            mSeekWhenPrepared;  // recording the seek position while preparing
    private Context                        mContext;

    public TVPlayerView(Context context) {
        super(context);
        mContext = context;
        initVideoView();
    }

    public TVPlayerView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
        mContext = context;
        initVideoView();
    }

    public TVPlayerView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        mContext = context;
        initVideoView();
    }

    @SuppressWarnings("deprecation")
	private void initVideoView() { 
        getHolder().addCallback(mSHCallback);
        getHolder().setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        setFocusable(true);
        setFocusableInTouchMode(true);
        requestFocus();
        mCurrentState = STATE_IDLE;
        this.mType = TVActivity.TV_NET;
    }
    
    public void setPlayerType(int type) {
    	this.release();
    	this.mType = type;
    }

    public void setVideoPath(String path) {
        setVideoURI(Uri.parse(path));
    }
    /**
     * @hide
     */
    public void setVideoURI(Uri uri) {
        mUri = uri;
        mSeekWhenPrepared = 0;
        openVideo();
        requestLayout();
        invalidate();
    }

    public void stopPlayback() {
        if (mMediaPlayer != null) {
            mMediaPlayer.stop();
            mMediaPlayer.release();
            mMediaPlayer = null;
            mCurrentState = STATE_IDLE;
        }
    }

    private void openVideo() {
        if (mUri == null || mSurfaceHolder == null) {
            // not ready for playback just yet, will try again later
            return;
        }
        
        Intent i = new Intent("com.android.music.musicservicecommand");
        i.putExtra("command", "pause");
        mContext.sendBroadcast(i);
        
        if (this.mMediaPlayer != null) {
            mMediaPlayer.reset();
            mCurrentState = STATE_IDLE;
        } else {
        	if (TVActivity.TV_DVB == this.mType) {
        		mMediaPlayer = new MyDvbPlayer();
        	} else {
        		mMediaPlayer = new MediaPlayer();
        	}
            mMediaPlayer.setOnPreparedListener(mPreparedListener);
            mMediaPlayer.setOnVideoSizeChangedListener(mSizeChangedListener);
            mMediaPlayer.setOnCompletionListener(mCompletionListener);
            mMediaPlayer.setOnErrorListener(mErrorListener);
            mMediaPlayer.setOnInfoListener(mOnInfoListener);
            mMediaPlayer.setOnBufferingUpdateListener(mOnBufferingUpdateListener);
            mMediaPlayer.setOnSeekCompleteListener(mOnSeekCompleteListener);
            mMediaPlayer.setDisplay(mSurfaceHolder);
            mMediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
            mMediaPlayer.setScreenOnWhilePlaying(true);
        }
        
        try {
        	mDuration = -1;
            mMediaPlayer.setDataSource(mContext, mUri);
            mMediaPlayer.prepareAsync();
            // we don't set the target state here either, but preserve the
            // target state that was there before.
            mCurrentState = STATE_PREPARING;
            
            if (TVActivity.TV_DVB == this.mType) {
	            //for dvb,needn't prepare file or stream for play
	            mCurrentState = STATE_PREPARED;			
	            if (mOnPreparedListener != null) {
	                mOnPreparedListener.onPrepared(mMediaPlayer);
	            }
            }
        } catch (IOException ex) {
            Log.w(TAG, "Unable to open content: " + mUri, ex);
            mCurrentState = STATE_ERROR;
            mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
            return;
        } catch (IllegalArgumentException ex) {
            Log.w(TAG, "Unable to open content: " + mUri, ex);
            mCurrentState = STATE_ERROR;
            mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
            return;
        } catch (IllegalStateException ex) {
        	Log.w(TAG, "Unable to open content: " + mUri, ex);
            mCurrentState = STATE_ERROR;
            mErrorListener.onError(mMediaPlayer, MediaPlayer.MEDIA_ERROR_UNKNOWN, 0);
            return;
        }
    }

    MediaPlayer.OnVideoSizeChangedListener mSizeChangedListener =
        new MediaPlayer.OnVideoSizeChangedListener() {
            public void onVideoSizeChanged(MediaPlayer mp, int width, int height) {
            	requestLayout();
            }
    };

    MediaPlayer.OnPreparedListener mPreparedListener = new MediaPlayer.OnPreparedListener() {
        public void onPrepared(MediaPlayer mp) {
            mCurrentState = STATE_PREPARED;
            if (mOnPreparedListener != null) {
                mOnPreparedListener.onPrepared(mMediaPlayer);
            } 

            int seekToPosition = mSeekWhenPrepared;  // mSeekWhenPrepared may be changed after seekTo() call
            if (seekToPosition != 0) {
                seekTo(seekToPosition);
            }
        }
    };

    private MediaPlayer.OnCompletionListener mCompletionListener =
        new MediaPlayer.OnCompletionListener() {
        public void onCompletion(MediaPlayer mp) {
            mCurrentState = STATE_PLAYBACK_COMPLETED;
            if (mOnCompletionListener != null) {
                mOnCompletionListener.onCompletion(mMediaPlayer);
            }
        }
    };

    private MediaPlayer.OnErrorListener mErrorListener =
        new MediaPlayer.OnErrorListener() {
        public boolean onError(MediaPlayer mp, int framework_err, int impl_err) {
            Log.d(TAG, "Error: " + framework_err + "," + impl_err);
            mCurrentState = STATE_ERROR;
            /* If an error handler has been supplied, use it and finish. */
            if (mOnErrorListener != null) {
            	mOnErrorListener.onError(mMediaPlayer, framework_err, impl_err);
            }
            return true;
        }
    };

    /**
     * Register a callback to be invoked when the media file
     * is loaded and ready to go.
     *
     * @param l The callback that will be run
     */
    public void setOnPreparedListener(MediaPlayer.OnPreparedListener l)
    {
        mOnPreparedListener = l;
    }

    /**
     * Register a callback to be invoked when the end of a media file
     * has been reached during playback.
     *
     * @param l The callback that will be run
     */
    public void setOnCompletionListener(OnCompletionListener l)
    {
        mOnCompletionListener = l;
    }

    /**
     * Register a callback to be invoked when an error occurs
     * during playback or setup.  If no listener is specified,
     * or if the listener returned false, VideoView will inform
     * the user of any errors.
     *
     * @param l The callback that will be run
     */
    public void setOnErrorListener(OnErrorListener l)
    {
        mOnErrorListener = l;
    }

    /**
     * Register a callback to be invoked when an informational event
     * occurs during playback or setup.
     *
     * @param l The callback that will be run
     */
    public void setOnInfoListener(OnInfoListener l)
    {
        mOnInfoListener = l;
    }
    
    public void setOnBufferingUpdateListener(OnBufferingUpdateListener l)
    {
    	mOnBufferingUpdateListener = l;
    }
    
    public void setOnSeekCompleteListener(OnSeekCompleteListener l)
    {
    	mOnSeekCompleteListener = l;
    }
    

    SurfaceHolder.Callback mSHCallback = new SurfaceHolder.Callback()
    {
    	@Override
        public void surfaceChanged(SurfaceHolder holder,
        		int format, int w, int h) {
        	requestLayout();
        }
    	@Override
        public void surfaceCreated(SurfaceHolder holder)
        {
            mSurfaceHolder = holder;
            openVideo();
        }
    	@Override
        public void surfaceDestroyed(SurfaceHolder holder)
        {
            // after we return from this we can't use the surface any more
            mSurfaceHolder = null;
            release();
        }
    };

    /*
     * release the media player in any state
     */
    private void release() {
    	//Log.i(TAG,"release");
        if (mMediaPlayer != null) {
            mMediaPlayer.reset();
            mMediaPlayer.release();
            mMediaPlayer = null;
            mCurrentState = STATE_IDLE;
        }
    }

    public void start() {
    	//Log.i(TAG,"start");
    	try {
	        if (isInPlaybackState()) {
	            mMediaPlayer.start();
	            mCurrentState = STATE_PLAYING;
	        }
    	} catch (IllegalStateException e) {
    		mCurrentState = STATE_ERROR;
    		e.printStackTrace();
    		if (mOnErrorListener != null) {
    			mOnErrorListener.onError(mMediaPlayer, 0, 0);
            }
    	}
    }

    public void pause() {
    	//Log.i(TAG,"pause:"+mMediaPlayer);
    	try {
    		if (isInPlaybackState()) {
    			//Log.i(TAG,"pause DO");
    			mMediaPlayer.pause();
    			mCurrentState = STATE_PAUSED;
   		
    		}
	   
    	} catch (IllegalStateException e) {
    		e.printStackTrace();
    		mCurrentState = STATE_ERROR;
    		if (mOnErrorListener != null) {
    			mOnErrorListener.onError(mMediaPlayer, 0, 0);
            }
    	}
    }

    public void suspend() {
    	//Log.i(TAG,"suspend");
        release();
    }

    public void resume() {
    	//Log.i(TAG,"resume");
        openVideo();
    }

    // cache duration as mDuration for faster access
    public int getDuration() {
        if (isInPlaybackState()) {
            if (mDuration > 0) {
                return mDuration;
            }
            mDuration = mMediaPlayer.getDuration();
            return mDuration;
        }
        mDuration = -1;
        return mDuration;
    }

    public int getCurrentPosition() {
        if (isInPlaybackState()) {
            return mMediaPlayer.getCurrentPosition();
        }
        return 0;
    }

    public void seekTo(int msec) {
        if (isInPlaybackState()) {
            mMediaPlayer.seekTo(msec);
            mSeekWhenPrepared = 0;
        } else {
            mSeekWhenPrepared = msec;
        }
    }

    public boolean isPlaying() {
        return isInPlaybackState() && mMediaPlayer.isPlaying();
    }
    
    public int getPlayerState() {
    	return this.mCurrentState;
    }

    private boolean isInPlaybackState() {
        return (mMediaPlayer != null &&
                mCurrentState != STATE_ERROR &&
                mCurrentState != STATE_IDLE &&
                mCurrentState != STATE_PREPARING);
    }
}
