package com.nmp.dvbplayer.tv;

import java.lang.ref.WeakReference;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.view.KeyEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.RelativeLayout.LayoutParams;

import com.nmp.dvbplayer.tv.TVUtility.ImageCache;
import com.nmp.dvbplayer.tv.data.EpgItem;
import com.nmp.dvbplayer.tv.data.EpgList;
import com.nmp.dvbplayer.tv.data.RecommendItem;
import com.nmp.dvbplayer.tv.data.RecommendList;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.tv.data.TVProgram;
import com.nmp.dvbplayer.tv.data.EpgList.LangCode;
import com.nmp.dvbplayer.R;

public class TVRelatedView extends TVWidget {
	public static final String  ChnEvent = "channel-change";
	private static final int CacheSize = 2 * 1024 * 1024;
	private class RecommendTask extends AsyncTask<Void, Void, RecommendItem[]> {
		private EpgList   mEpgList;
		private TVChannel mChannel;
		private String    mTitle;		
		public RecommendTask(TVChannel chn) {
			this.mChannel = chn;
			this.mEpgList = mActivity.getEpgList();
			this.mTitle = "";			
			if (TVChannel.NET_TURN_NODE == this.mChannel.getType()) {
				TVProgram program = null;
				program = mActivity.getChannelManager().getSelProgram();
				if (program != null) {
					this.mTitle = program.getName();
				}
			}
		}
		@Override
		protected RecommendItem[] doInBackground(Void... params) {
			if (this.mTitle.length() < 1) {
				LangCode code = LangCode.Unknown;
				EpgItem[] items = null;
				items = this.mEpgList.getCurrentEpg(this.mChannel, code);
				if (items != null) {
					this.mTitle = items[0].getTitle();
				}	
			}
			return mRecList.getRecommendList(this.mTitle);
		}
		@Override
		protected void onPostExecute(RecommendItem[] result) {
			mRecTask = null;
			mRecArray = result;
			updateRecommendList();
		}
	};
	
	class ImageWorkerTask extends AsyncTask<String, Void, Bitmap> {
	    private final WeakReference<ImageView> mView;

	    public ImageWorkerTask(ImageView imageView) {
	        this.mView = new WeakReference<ImageView>(imageView);
	    }
	    
	    private int calculateInSampleSize(BitmapFactory.Options options, 
	    		int reqWidth, int reqHeight) {
		    // Raw height and width of image
		    final int height = options.outHeight;
		    final int width = options.outWidth;
		    int inSampleSize = 1;
	
		    if (height > reqHeight || width > reqWidth) {
	
		        // Calculate ratios of height and width to requested height and width
		        final int heightRatio = Math.round((float) height / (float) reqHeight);
		        final int widthRatio = Math.round((float) width / (float) reqWidth);
	
		        // Choose the smallest ratio as inSampleSize value, this will guarantee
		        // a final image with both dimensions larger than or equal to the
		        // requested height and width.
		        inSampleSize = heightRatio < widthRatio ? heightRatio : widthRatio;
		    }
	
		    return inSampleSize;
		}
	    
	    private Bitmap decodeBitmap(byte[] data, int reqWidth, int reqHeight) {
	        final BitmapFactory.Options options = new BitmapFactory.Options();
	        options.inJustDecodeBounds = true;
	        BitmapFactory.decodeByteArray(data, 0, data.length, options);

	        // Calculate inSampleSize
	        options.inSampleSize = calculateInSampleSize(options, reqWidth, reqHeight);

	        // Decode bitmap with inSampleSize set
	        options.inJustDecodeBounds = false;
	        return BitmapFactory.decodeByteArray(data, 0, data.length, options);
	    }

	    @Override
	    protected Bitmap doInBackground(String... params) {
	        String url = params[0];
	        byte[] data = mImageCache.get(url);
	        if (null == data) {
	        	data = TVUtility.httpRequest(url, null);
	        	if (data != null) {
	        		mImageCache.put(url, data);
	        	}
	        }
	        if (null == data) {
	        	return null;
	        }
	        return this.decodeBitmap(data, 600, 900);
	    }

	    // Once complete, see if ImageView is still around and set bitmap.
	    @Override
	    protected void onPostExecute(Bitmap bitmap) {
	        if (mView != null && bitmap != null) {
	            final ImageView imageView = mView.get();
	            if (imageView != null) {
	                imageView.setImageBitmap(bitmap);
	            }
	        }
	    }
	};
	
	private RecommendList mRecList;
	private TVActivity mActivity;
	private View mSelfView;
	private View mFocusView;
	private LayoutParams mFocusLayout;
	
	private int mFocusIdx;
	private boolean mFocus;
	private int mItemWidth;
	private int mStartX;
	
	private RecommendTask mRecTask;
	private RecommendItem[] mRecArray;
	private ImageWorkerTask[] mWorkers;
	
	ImageCache mImageCache;
	
	public TVRelatedView(TVActivity activity) {
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_related_list, (RelativeLayout)view);
		this.mSelfView = this.mActivity.findViewById(R.id.tv_related_list);
		this.mFocusView = this.mSelfView.findViewById(R.id.tv_related_focus);
		this.mFocusLayout = new LayoutParams(this.mFocusView.getLayoutParams());
		this.focus(false);
		this.hide();
		
		this.mFocusIdx = 0;
		this.mRecList = new RecommendList();
		this.mRecTask = null;
		this.mRecArray = null;
		this.mWorkers = null;
		
		//宽度为115，33为左右margin
		this.mItemWidth = 115 + 33 * 2;
		// 因为是居中排列，假设有6个节目
		this.mStartX = (1280 - 6 * this.mItemWidth) / 2;
		
		this.mImageCache = new ImageCache(CacheSize);
	}
	
	@Override
	public void show() {
		if (this.getView().getVisibility() != View.VISIBLE) {
			super.show();
			this.mFocusIdx = 0;
			this.startRecTask();
		}
	}
	
	private void startRecTask() {
		TVChannel channel = this.mActivity.getChannelManager().getSelChannel();
		if (null == channel) {			
			this.updateRecommendList();
			return;
		}
		
		if (this.mRecTask != null) {
			this.mRecTask.cancel(true);
		}
		this.mRecTask = new RecommendTask(channel);
		Executor exec = Executors.newCachedThreadPool();
		this.mRecTask.executeOnExecutor(exec);
	}
	
	private void updateRecommendList() {
		View v = this.mSelfView.findViewById(R.id.tv_related_images);
		LinearLayout recImgList = (LinearLayout)v;
		recImgList.removeAllViews();
		if (null == this.mRecArray) {
			return;
		}
		if (this.mWorkers != null) {
			for (int i = 0; i < this.mWorkers.length; ++i) {
				this.mWorkers[i].cancel(true);
			}
		}
		this.mWorkers = new ImageWorkerTask[this.mRecArray.length];
		
		for (int i = 0; i < this.mRecArray.length; ++i) {
			v = View.inflate(this.mActivity, R.layout.tv_related_item, recImgList);
		}
		
        Executor exec = Executors.newCachedThreadPool();
		for (int i = 0; i < this.mRecArray.length; ++i) {
			v = recImgList.getChildAt(i);
			ImageView imgView = (ImageView)v.findViewById(R.id.tv_related_pic);
			TextView txtView = (TextView)v.findViewById(R.id.tv_related_name);
			txtView.setText(this.mRecArray[i].getName());			
			this.mWorkers[i] = new ImageWorkerTask(imgView);
			this.mWorkers[i].executeOnExecutor(exec, this.mRecArray[i].getPosterURL());
		}
		this.mStartX = (1280 - this.mRecArray.length * this.mItemWidth) / 2;
		int left = this.mStartX + this.mItemWidth * this.mFocusIdx;
		this.mFocusLayout.setMargins(left, 0, 0, 0);
		this.mFocusView.setLayoutParams(this.mFocusLayout);
	}
	
	private void changeFocusIdx(int diff) {
		if (null == this.mRecArray) {
			return;
		}
		
		int oldIdx = this.mFocusIdx;
		this.mFocusIdx += diff;
		if (this.mFocusIdx < 0) {
			this.mFocusIdx += this.mRecArray.length;
		}
		if (this.mFocusIdx >= this.mRecArray.length) {
			this.mFocusIdx -= this.mRecArray.length;
		}
		
		int deltaX = this.mItemWidth * (this.mFocusIdx - oldIdx);
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
				int left = mStartX + mItemWidth * mFocusIdx;
				mFocusLayout.setMargins(left, 0, 0, 0);
				mFocusView.setLayoutParams(mFocusLayout);
			}
		});
		this.mFocusView.clearAnimation();
		this.mFocusView.setAnimation(animation);
		this.mFocusView.bringToFront();
		animation.startNow();
		this.getView().invalidate();
	}
	
	@Override
	public boolean accept(int keyCode) {
		if (null == this.mRecArray) {
			return false;
		}
		
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
		if (null == this.mRecArray) {
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
			//FIXME
			return true;
		}
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
	
	@Override
	public void appNotify(String type, Object value) {
		if (type.equalsIgnoreCase(ChnEvent)) {
			this.startRecTask();
		}
	}
}
