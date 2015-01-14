package com.nmp.dvbplayer.tv;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Locale;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.regex.Pattern;

import com.alitech.dvb.DvbEpgList;
import com.alitech.dvb.DvbSystem;
import com.alitech.dvb.DvbUdrm;
import com.nmp.dvbplayer.common.TVSettingSndChn;
import com.nmp.dvbplayer.common.VolumeBar;
import com.nmp.dvbplayer.tv.TVChnManager.UpdateEvent;
import com.nmp.dvbplayer.tv.TVUtility.TimeUtil;
import com.nmp.dvbplayer.tv.data.EpgItem;
import com.nmp.dvbplayer.tv.data.EpgList;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.tv.data.TVGroup;
import com.nmp.dvbplayer.tv.data.TVProgram;
import com.nmp.dvbplayer.tv.data.TVSource;
import com.nmp.dvbplayer.tv.data.EpgList.LangCode;
import com.nmp.dvbplayer.tv.search.TVSearchSetting;
import com.nmp.dvbplayer.R;
//import com.nmp.myplayer.tv.net.NetEpgList;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.content.res.Resources;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnBufferingUpdateListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class TVActivity extends Activity implements 
		TVChnManager.UpdateListener,
		OnBufferingUpdateListener,
		OnCompletionListener,
		OnErrorListener,
		OnInfoListener,
		OnSeekCompleteListener,
		OnPreparedListener {
	
	private static final String Tag = TVActivity.class.getName();
	private static final int    MaxSteps = 180;
    private static final double SeekSpeed = 1.065;
	private static final int    ChannelPageSize = 9;
	private static final int    ShowListTimeout = 5 * 1000;
	private static final int    DialogTimeout = 3 * 1000;
	private static final int    DelayPlayTimeout = 8 * 1000;
	private static final int    SeekTimeout = 3 * 1000;
	private static final int    ChannelTimeout = 2 * 1000;
	private static final int    MinRecordTime = 30 * 60 * 1000;
	
	public static final int     ReqCode = 1;	
	public static final int     TV_DVB = 0;
	public static final int     TV_NET = 1;
	public static final int     AnimTime = 200;
	
	public static final String  DvbAction = "START-DVB-ACTION";
	
	private static final int MSG_HIDE_CHANNEL_LIST = 0;
	private static final int MSG_HIDE_PLAYBAR      = 1;
	private static final int MSG_HIDE_OPTION       = 2;
	private static final int MSG_DELAY_PLAY        = 3;
	private static final int MSG_UPDATE_PROGRESS   = 4;
	private static final int MSG_SEEK_TIMEOUT      = 5;
	private static final int MSG_CHANNEL_TIMEOUT   = 6;
	private static final int MSG_RECORD_TIMEOUT    = 7;
	private static final int MSG_DIALOG_TIMEOUT    = 8;
	private static final int MSG_OSD_TIMEOUT    =9;
	private static final int MSG_TUNER_STATUS    =10;
	
	private static final int UDRAM_NOTIFY_MAIL = 129;
	private static final int UDRAM_NOTIFY_OSD = 130;
	private static final int UDRAM_NOTIFY_IPPV=131;
	private static final int UDRAM_NOTIFY_PPT=132;
	private static final int UDRAM_NOTIFY_SERVICE_STATUS=133;
	private static final int UDRAM_NOTIFY_FINGER=134;
	private static final int UDRAM_NOTIFY_LOADER=135;

	private final static int	MCAS_DISP_NO_ENCRMPT = 0;	
	private final static int	MCAS_DISP_UTI_ERR=1;
	private final static int	MCAS_DISP_UTI_INVALID=2;
	private final static int	MCAS_DISP_NO_SERVICE_PROVIDER=3;
	private final static int	MCAS_DISP_NVRAM_ERR=4;
	private final static int	MCAS_DISP_NO_SIGNAL=5;
	private final static int	MCAS_DISP_UNORAML=6;
	private final static int	MCAS_DISP_NO_LICENCE=7;
	private final static int	MCAS_DISP_DISCRAMBLE_SUCCUSS=8;
	private final static int	MCAS_DISP_AREA_LIMIT=9;
	private final static int	MCAS_DISP_GLASS_LIMIT=10;
	private final static int	MCAS_DISP_FINGER_DISPLAY=11;
	private final static int	MCAS_DISP_CREDIT_LIMIT=12;
	private final static int	MCAS_DISP_PREVIEW=13;
	private final static int	MCAS_DISP_HAVE_BUY=14;
	private final static int	MCAS_DISP_MAX_LICENCE_NUM=15;
	private final static int	MCAS_DISP_NO_ACCOUT=16;
	private final static int	MCAS_DISP_CONDIONAL_PLAY=17;
	private final static int	MCAS_DISP_PASWD_RESET=18;
	private final static int	MCAS_DISP_CONNECT_SEVER_FAIL=19;
	private final static int	MCAS_DISP_PROTECT_BY_DRM=20;
	private final static int	MCAS_DISP_LOCK_UTI=21;
	private final static int	MCAS_DISP_UNLOCK_UTI=22;

	private static final int EMAIL_DISP_FORCE_EMAIL = 0;
	private static final int EMAIL_DISP_NORMAL_EMAIL = 1;
	private static final int EMAIL_DISP_NORMAL_FULL = 2;
	
	private static final int LockLedOn = 11;
	private static final int LockLedOff = 12;
	
	 private int lockledstatus = -1;
	
	
	protected int udrm_info_timeout;

	public DvbUdrm dvbUdrm;
	
	private Timer mTimerTask;
	private Handler mMsgHandler;


	@SuppressLint("HandlerLeak")
	private void processManagerHandle() {
	this.mMsgHandler = new Handler() {
		@Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case MSG_TUNER_STATUS:
            	if(DvbSystem.getTunerLock() == 1) {
            		if(lockledstatus != 1 )
            			DvbSystem.PanelShow("abdc", LockLedOn);
            		lockledstatus = 1;
            	}
            	else {
            		if(lockledstatus != 0)
            			DvbSystem.PanelShow("abdc", LockLedOff);
            		lockledstatus = 0;
            	}
            	break;
            case MSG_HIDE_CHANNEL_LIST:
            	mChnListView.setVisibility(View.GONE);
            	mChnManager.resetFocusChannel();
            	updateGroups();
                break;
            case MSG_HIDE_PLAYBAR:
            	hidePlaybar();
            	break;
            case MSG_HIDE_OPTION:
				//	mOptionView.hide();
            	break;
            case MSG_DELAY_PLAY:
            	play(null);
            	break;
            case MSG_UPDATE_PROGRESS:
            	if (mVideoView.isPlaying()) {
	            	mDuration = mVideoView.getDuration();
	        		mCurrent = mVideoView.getCurrentPosition();
            	} else {
            		mDuration = -1;
            		mCurrent = 0;
            	}
            	
        		int nextcheck = 1000 - mCurrent % 1000;
        		int msgId = MSG_UPDATE_PROGRESS;
        		mMsgHandler.removeMessages(msgId);
        		mMsgHandler.sendEmptyMessageDelayed(msgId, nextcheck);
            	if (View.VISIBLE == mPlaybarView.getVisibility()) {
            		updatePlaybar(mDuration, mCurrent, mSeekPos);
            	}
            	if (mVideoView.isPlaying()) {
            		mChnManager.setCurrentTime(mCurrent);
            	}
            	break;
            case MSG_SEEK_TIMEOUT:
            	seek();
            	break;
            case MSG_CHANNEL_TIMEOUT:
            	playThisChannel();
            	break;
            case MSG_RECORD_TIMEOUT:
            	refreshFavList();
            	break;
            case MSG_DIALOG_TIMEOUT:
            	hideDialog();
            	break;
			case MSG_OSD_TIMEOUT:
				hideUdrmOsd();
				break;

			case  UDRAM_NOTIFY_SERVICE_STATUS:
				udram_message_proc(msg.arg1);
				break;
			case  UDRAM_NOTIFY_LOADER:
				ota_emm_message_proc(msg.arg1);
				break;

			case  UDRAM_NOTIFY_MAIL:
				email_message_proc((String[]) msg.obj,msg.arg1);
				break;		

			case  UDRAM_NOTIFY_OSD:
				osd_message_proc((String[]) msg.obj,msg.arg1);	
				break;
            default:
            	super.handleMessage(msg);
            	break;
            }
        }
	};
	
	TimerTask task = new TimerTask(){
	    public void run(){
	    //execute the task 
			Log.i(Tag, "check tuner lock -->");
			mMsgHandler.sendEmptyMessage(MSG_TUNER_STATUS);
	    }
	};

	mTimerTask = new Timer();
	mTimerTask.schedule(task, 2000, 5000);
	}
	
	private class EpgTask extends AsyncTask<TVChannel, Void, EpgItem[]> {
		@Override
		protected EpgItem[] doInBackground(TVChannel... params) {
			if (null == params[0]) {
				return null;
			}
			return mEpgList.getCurrentEpg(params[0], LangCode.Unknown);
		}
		@Override
		protected void onPostExecute(EpgItem[] result) {
			updatePlaybar(result);
			mEpgTask = null;
		}
	};
	
	private EpgTask         mEpgTask = null;
	
	private TVChnManager    mChnManager;
	private EpgList         mEpgList;
	private ArrayList<View> mChnLists;
	private EpgItem         mEpgItem;
	
	private View            mChnListView;
	private View            mPlaybarView;
	private TVPlayerView    mVideoView;
	private TVOptionView    mOptionView;
	private TextView        mChannelView;
	private VolumeBar       mVolumeView;
	private TextView        mDialogView;
	private TextView        mUdrmOsdView;
	private int             mChannel;
	private int             mDuration;
	private int             mCurrent;
	private int             mSeekPos;
    private int             mSeekKeyCount;
    private long            mSeekKeyTime;
    private int             mTVType;
    private long            mLastPlayTime;
    
    private boolean         mShowRelated;
    private boolean         mSupportLiveBack;
    private boolean         mCheckDvb;
	private String udrmStatusTxt  ="";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.i(Tag, "onCreate");
		this.processManagerHandle();
		
		this.setContentView(R.layout.tv_main);
		copyDB();
		this.mShowRelated = false;
		this.mSupportLiveBack = false;
		this.mCheckDvb = true;
		
		int rid = R.id.tv_main;
		RelativeLayout relLayout = (RelativeLayout)this.findViewById(rid);
		View.inflate(this, R.layout.tv_channel_list, relLayout);
		View.inflate(this, R.layout.tv_playbar, relLayout);
		
		rid = R.id.tv_list_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);
		this.mChnLists = new ArrayList<View>();
		for (int i = 0; i < ChannelPageSize; ++i) {
			View.inflate(this, R.layout.tv_list_item, lLayout);
		}
		for (int i = 0; i < lLayout.getChildCount(); ++i) {
			this.mChnLists.add(lLayout.getChildAt(i));
		}
		
		this.dvbUdrm = new DvbUdrm();
		this.dvbUdrm.set_handler(this.mMsgHandler);

		this.mChnListView = this.findViewById(R.id.tv_chn_list);
		this.mPlaybarView = this.findViewById(R.id.tv_playbar);
		this.mOptionView = new TVOptionView(this);
		this.mVideoView = (TVPlayerView)this.findViewById(R.id.tv_player_view);
		this.mVideoView.setOnBufferingUpdateListener(this);
		this.mVideoView.setOnCompletionListener(this);
		this.mVideoView.setOnErrorListener(this);
		this.mVideoView.setOnInfoListener(this);
		this.mVideoView.setOnSeekCompleteListener(this);
		this.mVideoView.setOnPreparedListener(this);
		this.mChannelView = (TextView)this.findViewById(R.id.tv_chn_number);
		this.mVolumeView = new VolumeBar(this);
		this.mDialogView = (TextView)this.findViewById(R.id.tv_dialog);
		this.mUdrmOsdView = (TextView)this.findViewById(R.id.tv_udrmosd);
		
		this.mChannel = 0;
		this.mDuration = -1;
		this.mCurrent = 0;
		this.mSeekPos = -1;
		this.mSeekKeyCount = 0;
		this.mSeekKeyTime = 0;	
		this.mLastPlayTime = Long.MAX_VALUE;
		this.mEpgItem = null;
	}

	private void copyDB()
	{
		String dbPath = "/data/data/com.nmp.dvbplayer";
		String dbName = "db.bin";
		File dbFile = new File(dbPath,dbName);
		if(dbFile.exists()){
			Log.i("test","DB is already exit");
			return;		
		}
		InputStream is =null;	
		try {
			is =getResources().getAssets().open(dbName);
				
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}
			
		FileOutputStream fos =null;
		try {
			fos =  new FileOutputStream(dbFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return;
		}  
			
		byte[] buffer =new byte[1024];   
		int size = 0;   
		int length = 0; //字节   
		try {
			while( (length= is.read(buffer)) > 0){   
				fos.write(buffer,0,length);   
				size += length;   
						
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}   
		try {
			fos.flush();
			fos.close();  
			is.close();   
			Log.i("test","DB copy finish");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}   
		
	}

	protected void osd_message_proc( String[] str,int timeout ) {

		this.showUdrmOsd(str[1]+"\n        "+str[2],timeout);
	}

	protected void udram_message_proc(int disp_type) 
	{

		this.setUdrm_info_timeout(0xff);

		Resources res = this.getResources(); 
		switch(disp_type)
		{
		case MCAS_DISP_NO_ENCRMPT:
			udrmStatusTxt= res.getString(R.string.rs_no_encrampt);
			break;
		case MCAS_DISP_UTI_ERR:
			udrmStatusTxt= res.getString(R.string.rs_uti_ic_err);
			break;
		case MCAS_DISP_UTI_INVALID:
			udrmStatusTxt= res.getString(R.string.rs_uti_ic_invalid);
			break;
		case MCAS_DISP_NO_SERVICE_PROVIDER:
			udrmStatusTxt= res.getString(R.string.rs_no_service_provider);
			break;
		case MCAS_DISP_NVRAM_ERR:
			udrmStatusTxt= res.getString(R.string.rs_nvram_err);
			break;
		case MCAS_DISP_NO_SIGNAL:
			udrmStatusTxt= res.getString(R.string.rs_no_signal);
			break;
		case MCAS_DISP_UNORAML:
			udrmStatusTxt= res.getString(R.string.rs_unoraml);
			break;
		case MCAS_DISP_NO_LICENCE:
			udrmStatusTxt= res.getString(R.string.rs_disp_no_licence);
			break;
		case MCAS_DISP_DISCRAMBLE_SUCCUSS:
			this.setUdrm_info_timeout(0);
			break ;
		case MCAS_DISP_AREA_LIMIT:
			udrmStatusTxt= res.getString(R.string.rs_disp_area_limit);
			break;
		case MCAS_DISP_GLASS_LIMIT:
			udrmStatusTxt= res.getString(R.string.rs_disp_glass_limit);

			// strID = RS_DISP_GLASS_LIMIT;
			//	        if(win_udrm_pwd_open_ex(NULL,0)==TRUE)
			//	        {
			//	            current_channel = sys_data_get_cur_group_cur_mode_channel();
			//	            get_prog_at(current_channel, &node);
			//
			//
			//	            UDRMServiceViewLevelDisableTemp(0,node.prog_number,g_udrm_old_pin,&result);
			//	        }

			break;
		case MCAS_DISP_FINGER_DISPLAY:
			udrmStatusTxt= res.getString(R.string.rs_disp_finger_display);

			break;
		case MCAS_DISP_CREDIT_LIMIT:
			udrmStatusTxt= res.getString(R.string.rs_disp_credit_limit);
			break;
		case MCAS_DISP_PREVIEW:
			udrmStatusTxt= res.getString(R.string.rs_disp_preview);
			break;
		case MCAS_DISP_HAVE_BUY:
			udrmStatusTxt= res.getString(R.string.rs_disp_have_buy);
			break;
		case MCAS_DISP_MAX_LICENCE_NUM:
			udrmStatusTxt= res.getString(R.string.rs_disp_max_licence_num);
			break;
		case MCAS_DISP_NO_ACCOUT:
			udrmStatusTxt= res.getString(R.string.rs_disp_no_accout);
			break;
		case MCAS_DISP_CONDIONAL_PLAY:
			udrmStatusTxt= res.getString(R.string.rs_disp_condional_play);
			break;
		case MCAS_DISP_PASWD_RESET:
			this.setUdrm_info_timeout(5);
			udrmStatusTxt= res.getString(R.string.rs_disp_paswd_reset);
			break;
		case MCAS_DISP_CONNECT_SEVER_FAIL:
			udrmStatusTxt= res.getString(R.string.rs_disp_connect_sever_fail);
			break;
		case MCAS_DISP_PROTECT_BY_DRM:
			udrmStatusTxt= res.getString(R.string.rs_disp_protect_by_drm);
			break;
		case MCAS_DISP_LOCK_UTI:
			udrmStatusTxt= res.getString(R.string.rs_disp_lock_uti);
			break;
		case MCAS_DISP_UNLOCK_UTI:
			udrmStatusTxt= res.getString(R.string.rs_disp_unlock_uti);
			break;
		default:
			break;
		}

		this.showDialog(udrmStatusTxt ,getUdrm_info_timeout());


		return  ;

	}
	public void ota_emm_message_proc(int msg_code) 
	{

	}
	public void email_message_proc(String[] strings, int disp_type) 
	{
		this.setUdrm_info_timeout(3);

		Resources res = this.getResources(); 
		String txt = "";
		switch(disp_type)
		{
		case EMAIL_DISP_FORCE_EMAIL:
			txt= res.getString(R.string.rs_force_email);
			this.showUdrmOsd(txt+"\n"+strings[1]+"\n        "+strings[2],0xff);
			break;
		case EMAIL_DISP_NORMAL_EMAIL:
			txt= res.getString(R.string.rs_normal_email);
			break;
		case EMAIL_DISP_NORMAL_FULL:
			txt= res.getString(R.string.rs_full_email);
			break;
		default:
			txt= res.getString(R.string.rs_no_service_provider);
			break;
		}
		this.showDialog(txt);


	}

    @Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (ReqCode == requestCode) {
			this.mCheckDvb = false;
			TVGroup[] groups = this.mChnManager.getChannelList().getGroups();
			if (null == groups || 0 == groups.length) {
				this.finish();
			}
		}
	}
	
	@Override
    protected void onStart() {
    	super.onStart();
    	Log.i(Tag, "onStart");
    	Intent intent = this.getIntent();
    	String action = intent.getAction();
    	this.mTVType = TV_NET;
    	if (action != null && action.equals(DvbAction)) {
    		this.mTVType = TV_DVB;
    	}
		this.mTVType = TV_DVB;
    	
		this.mVideoView.setPlayerType(this.mTVType);
    	this.mChnManager = new TVChnManager(this);
    	if (this.mTVType == TV_NET) {
    		//NetEpgList epglist = new NetEpgList(this);
    		//this.mEpgList = epglist;
    		//epglist.setChannelList(this.mChnManager.getChannelList());
    	} else {
    		this.mEpgList = new DvbEpgList(this);
    	}
    	this.updateGroups();
    	this.showPlaybar(false);
    	
    	//this.play(null);
    	
    	int msg = MSG_DELAY_PLAY;
    	int timeout = DelayPlayTimeout/8;
    	this.mMsgHandler.removeMessages(msg);
    	this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
    	
    	//this.showChannelList();
    	
    	// 没有DVB频道信息，自动跳转到搜台页面，并且只跳转一次，否则用户无法退出直播应用了！
    	TVGroup[] groups = this.mChnManager.getGroups();
    	if (this.mCheckDvb && TV_DVB == this.mTVType &&
    			(null == groups || groups.length < 1)) {
    		intent = new Intent(this, TVSearchSetting.class);
			this.startActivityForResult(intent, ReqCode);
    	}
    }
    
    @Override
    protected void onStop() {
    	super.onStop();
    	//Log.i(Tag, "onStop 1");
    	this.mChnManager.destroy();
    	this.mVideoView.stopPlayback();
    	this.updateFavList();
    	if (this.mEpgTask != null) {
    		this.mEpgTask.cancel(true);
    	}
    	this.mMsgHandler.removeMessages(MSG_HIDE_CHANNEL_LIST);
    	this.mMsgHandler.removeMessages(MSG_HIDE_PLAYBAR);
    	this.mMsgHandler.removeMessages(MSG_HIDE_OPTION);
    	this.mMsgHandler.removeMessages(MSG_DELAY_PLAY);
    	this.mMsgHandler.removeMessages(MSG_UPDATE_PROGRESS);
    	this.mMsgHandler.removeMessages(MSG_SEEK_TIMEOUT);
    	this.mMsgHandler.removeMessages(MSG_RECORD_TIMEOUT);
    	DvbSystem.PanelShow("----",4);
    	//Log.i(Tag, "onStop 2");
    } 
    
    @Override
    protected void onPause()
    {
    	super.onPause();
    	this.mVideoView.pause();
    	//Log.i(Tag, "onPause");
    	
    }
    
    public TVChnManager getChannelManager() {
    	return this.mChnManager;
    }
    
    public EpgList getEpgList() {
    	return this.mEpgList;
    }
    
    public int getTVType() {
    	return this.mTVType;
    }
    
    public boolean getIsRelated() {
    	return this.mShowRelated;
    }
    
    public boolean supportLiveBack() {
    	return this.mSupportLiveBack;
    }
    
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    	if (keyCode == KeyEvent.KEYCODE_BACK ||
    			keyCode == KeyEvent.KEYCODE_ESCAPE) {
    		if (View.VISIBLE == this.mDialogView.getVisibility()) {
    			this.hideDialog();
    			return true;
			}else if (View.VISIBLE == this.mUdrmOsdView.getVisibility()) {
				this.hideUdrmOsd(); 
    			return true;
    		} else if (View.VISIBLE == this.mChannelView.getVisibility()) {
    			this.hideChannelNum();
    			return true;
    		} else if (View.VISIBLE == this.mPlaybarView.getVisibility()) {
    			this.hidePlaybar();
    			return true;
    		} else if (View.VISIBLE == this.mChnListView.getVisibility()) {
    			this.mChnListView.setVisibility(View.GONE);
    			this.mChnManager.resetFocusChannel();
    			this.updateGroups();
    			return true;
    		} else if (View.VISIBLE ==
    				this.mOptionView.getView().getVisibility()) {
    			if(this.mOptionView.biref_show_status()){
    				
    				this.mOptionView.onKeyDown(keyCode);
    				this.showOptions();
    			}
    			else {
    				this.mOptionView.hide();
    			}
    			return true;
    		}
    		//需要调用底层的回调来退出应用！
    		return super.onKeyDown(keyCode, event);
    	}
    	
    	return this.onKeyDown(keyCode);
    }
    
    public boolean onKeyDown(int keyCode) {
    	if (keyCode >= KeyEvent.KEYCODE_0 && keyCode <= KeyEvent.KEYCODE_9) {
    		this.keyNumInput(keyCode - KeyEvent.KEYCODE_0);
    		return true;
    	}
    	
    	if (KeyEvent.KEYCODE_MENU == keyCode) {
    		if (View.VISIBLE == this.mChnListView.getVisibility()) {
    			this.showChannelList();
    			this.toggleFavorite();
    			return true;
    		} else if (View.VISIBLE ==
    				this.mOptionView.getView().getVisibility()) {
				this.showOptions();
				return this.mOptionView.onKeyDown(keyCode);
    		} else {
    			this.showOptions();
    		}
    		return true;
    	}
    	
    	if (View.VISIBLE == this.mOptionView.getView().getVisibility()) {
    		this.showOptions();
    		return this.mOptionView.onKeyDown(keyCode);
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
    		this.onPressUp();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
    		this.onPressDown();
    		return true;
    	} 
    	
    	if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
    		this.onPressLeft();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
    		this.onPressRight();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||
    			keyCode == KeyEvent.KEYCODE_ENTER) {
    		this.onPressEnter();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_VOLUME_DOWN) {
    		this.mVolumeView.volumeDown();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_VOLUME_UP) {
    		this.mVolumeView.volumeUp();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_VOLUME_MUTE ||
    			keyCode == KeyEvent.KEYCODE_MUTE) {
    		this.mVolumeView.volumeMute();
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_PAGE_DOWN) {
    		if (View.VISIBLE == this.mChnListView.getVisibility()) {
    			this.mChnManager.changeFocusChannel(this.mChnLists.size());
		    	this.updateChannels();
		    	this.showChannelList();
        	}
    		return true;
    	}
    	
    	if (keyCode == KeyEvent.KEYCODE_PAGE_UP) {
    		if (View.VISIBLE == this.mChnListView.getVisibility()) {
    			this.mChnManager.changeFocusChannel(-this.mChnLists.size());
		    	this.updateChannels();
		    	this.showChannelList();
        	}
    		return true;
    	}
    	
    	return true;
    }
    
    private void onPressDown() {
    	if (View.VISIBLE == this.mChnListView.getVisibility()) {
    		if (!this.mChnManager.isLastChannel()) {
		    	this.mChnManager.changeFocusChannel(1);
		    	this.updateChannels();
		    	this.showChannelList();
    		}
    	} else {
    		this.updateFavList();
    		this.mChnManager.findChannel(-1, null);
    		this.updateGroups();
    		this.showPlaybar(false);
    		this.play(null);
    	}
    }
    
    private void onPressUp() {
    	if (View.VISIBLE == this.mChnListView.getVisibility()) {
    		if (!this.mChnManager.isFirstChannel()) {
		    	this.mChnManager.changeFocusChannel(-1);
		    	this.updateChannels();
		    	this.showChannelList();
    		}
    	} else {
    		this.updateFavList();
    		this.mChnManager.findChannel(1, null);
    		this.updateGroups();
    		this.showPlaybar(false);
    		this.play(null);
    	}
    }
    
    private void onPressLeft() {
    	if (View.VISIBLE == this.mChnListView.getVisibility()) {
	    	this.mChnManager.changeFocusGroup(-1);
	    	this.updateGroups();
	    	this.showChannelList();
	    	this.startChnListAnimation(-1);
    	} else {
    		if (View.VISIBLE == this.mPlaybarView.getVisibility()) {
    			this.updateSeekPos(false);
    		}
    		this.showPlaybar(true);
    	}
    }
    
    private void updateSeekPos(boolean dir) {
    	TVChannel chn = this.mChnManager.getSelChannel();
		if (chn != null && this.mDuration > 0 &&
				(chn.getType() == TVChannel.NET_TURN_NODE || this.mEpgItem != null)){
			if (this.mSeekPos < 0) {
				this.mSeekPos = this.mCurrent;
			}
			int step = this.getSeekStep();
			if (dir) {
				this.mSeekPos += step;
				if (this.mSeekPos > this.mDuration) {
					this.mSeekPos = this.mDuration;
				}
			} else {
				this.mSeekPos -= step;
				if (this.mSeekPos < 0) {
					this.mSeekPos = 0;
				}
			}
			this.updatePlaybar(this.mDuration, this.mCurrent, this.mSeekPos);
			
			int msg = MSG_SEEK_TIMEOUT;
			int timeout = SeekTimeout;
			this.mMsgHandler.removeMessages(msg);
			this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
		}
    }
    
    private void onPressRight() {
    	if (View.VISIBLE == this.mChnListView.getVisibility()) {
	    	this.mChnManager.changeFocusGroup(1);
	    	this.updateGroups();
	    	this.showChannelList();
	    	this.startChnListAnimation(1);
    	} else {
    		if (View.VISIBLE == this.mPlaybarView.getVisibility()) {
    			this.updateSeekPos(true);
    		}
    		this.showPlaybar(true);
    	}
    }
    
    private void onPressEnter() {
    	if (View.VISIBLE == this.mDialogView.getVisibility()) {
    		this.hideDialog();
		} else if (View.VISIBLE == this.mChannelView.getVisibility()) {
    		this.playThisChannel();
    	} else if (View.VISIBLE == this.mChnListView.getVisibility()) {
    		if (null == this.mEpgItem && this.mChnManager.faultSelect()) {
    			this.mChnListView.setVisibility(View.GONE);
    		} else {
	    		this.updateFavList();
		    	this.mChnManager.selectChannel();
		    	this.updateChannels();
		    	this.showChannelList();
		    	this.play(null);
    		}
    	} else {
    		if (this.mSeekPos >= 0 &&
    				View.VISIBLE == this.mPlaybarView.getVisibility()) {
    			this.seek();
    		} else {
	    		this.showChannelList();
	    		this.hidePlaybar();
    		}
    	}
    }
    
    private int getSeekStep() {
    	int curStep = 5000;
    	int maxStep = this.mDuration / MaxSteps;
    	long now = System.currentTimeMillis();
    	
    	if (maxStep < 1) {
    		maxStep = 1;
    	}
    	if (now - this.mSeekKeyTime > 1000) {
    		this.mSeekKeyCount = 1;
    	} else {
    		this.mSeekKeyCount += 1;
    	}
    	this.mSeekKeyTime = now;
    	curStep *= Math.pow(SeekSpeed, this.mSeekKeyCount);
    	
    	return Math.min(curStep, maxStep);
    }
    
    private void seek() {
    	this.mVideoView.seekTo(this.mSeekPos);
    	this.mCurrent = this.mSeekPos;
    	this.mMsgHandler.removeMessages(MSG_SEEK_TIMEOUT);
    	this.mSeekPos = -1;
    	this.mSeekKeyCount = 0;
    	this.mSeekKeyTime = 0;
    	this.updatePlaybar(this.mDuration, this.mCurrent, this.mSeekPos);
    }
    
    private void play(String url) {
    	this.mMsgHandler.removeMessages(MSG_DELAY_PLAY);
    	this.mChnManager.setUpdateListener(this);
    	if (null == url) {
	    	TVSource source = this.mChnManager.getSelSource();
	    	if (null == source) {
	    		Log.e(Tag, "no source info for current channel!");
	    		return;
	    	}
	    	this.mChnManager.setUpdateListener(null);
	    	url = source.getSourceURL();
    	}
    	if (null == url) {
    		Log.e(Tag, "cannot get url from source!");
    		return;
    	}
    	
    	if (mTVType == TV_DVB) {
    		DvbSystem.PanelShow(String.format(Locale.CHINA, "%04d", Integer.parseInt( this.mChnManager.getselchnum())), 4);
    		String oldVol = new String("&audioVolume=");
    		int pos = url.indexOf(oldVol);
    		if (pos != -1) {
    			int end = url.indexOf('&', pos + oldVol.length());
    			if (end != -1) {
    				oldVol = url.substring(pos, end);
    			} else {
    				oldVol = url.substring(pos);
    			}
    			int vol = mVolumeView.getVolume();
    			vol = vol * 100 / 15;
        		String newVol = new String("&audioVolume=") + String.valueOf(vol);
        		url = url.replace(oldVol, newVol);
    		}
		String oldaudioChl = new String("&audioChannel=");
    		int pos_sndChl = url.indexOf(oldaudioChl);
    		if (pos_sndChl != -1) {
    			int end = url.indexOf('&', pos_sndChl + oldaudioChl.length());
    			if (end != -1) {
    				oldaudioChl = url.substring(pos_sndChl, end);
    			} else {
    				oldaudioChl = url.substring(pos_sndChl);
    			}
    			TVSettingSndChn sndChnSet = new TVSettingSndChn(this);
    			int audiochl = sndChnSet.getSndChn();
        		String newSndChl = new String("&audioChannel=") + String.valueOf(audiochl);
        		url = url.replace(oldaudioChl, newSndChl);
    		}
    	}
    	
    	this.setLoadingPercent(0);
    	this.hideDialog();
    	this.mEpgItem = null;
    	this.mLastPlayTime = Long.MAX_VALUE;
    	
    	this.updatePlaybar(this.mChnManager.getSelChannel());
    	if (View.VISIBLE == this.mPlaybarView.getVisibility()) {
    		this.updateEpg();
    	}
    	
    	this.mMsgHandler.removeMessages(MSG_UPDATE_PROGRESS);
		this.mMsgHandler.sendEmptyMessageDelayed(MSG_UPDATE_PROGRESS, 0);
		
		Log.d(Tag, "play url: " + url);
		this.mVideoView.setVideoPath(url);
    }
    
    public void changeSource(int diff) {
    	this.updateFavList();
    	this.mChnManager.changeSelSource(diff);
    	this.play(null);
    }
    
    public void changeProgram(int diff) {
    	this.updateFavList();
    	this.mChnManager.changeSelProgram(diff);
    	this.play(null);
    }
    
    public void startLiveBack(EpgItem item) {
    	if (!item.canLiveBack()) {
    		Log.e(Tag, "this epg item cannot liveback!");
    		return;
    	}
    	TVSource[] sources = item.getSources();
    	if (null == sources || sources.length < 1) {
    		Log.e(Tag, "liveback url is null!");
    		return;
    	}
    	
    	String url = sources[0].getSourceURL();
    	this.play(url);
    	this.mCurrent = 0;
    	this.mDuration = -1;
    	
    	EpgItem[] epgs = null;
    	this.mEpgItem = item;
    	this.updatePlaybar(epgs);
    }
    
    private void setLoadingPercent(int percent) {
    	View ld = this.findViewById(R.id.tv_player_loading);
    	//TextView lp = (TextView)this.findViewById(R.id.tv_loading_percent);
    	if (percent < 100) {
    		ld.bringToFront();
    		ld.setVisibility(View.VISIBLE);
    		//lp.setText(String.valueOf(percent));
    	} else {
    		ld.setVisibility(View.GONE);
    		//lp.setText(String.valueOf(0));
    	}
    }
        
    private void updateGroups() {
    	TVGroup[] groups = this.mChnManager.getGroups();
    	TVGroup grp = this.mChnManager.getFocusGroup();
    	int curGrpIdx = this.mChnManager.getFocusGrpIdx();
    	
    	if (null == groups || null == grp) {
    		this.updateChannels();
    		return;
    	} 
    	
    	int rid = R.id.tv_list_group;
    	TextView grpName = (TextView)this.mChnListView.findViewById(rid);
    	grpName.setText(grp.getName());
    	
    	rid = R.id.tv_list_right;
    	View grpRight = this.mChnListView.findViewById(rid);
    	if (curGrpIdx < groups.length - 1) {
    		grpRight.setVisibility(View.VISIBLE);
    	} else {
    		grpRight.setVisibility(View.INVISIBLE);
    	}
    	
    	rid = R.id.tv_list_left;
    	View grpLeft = this.mChnListView.findViewById(rid);
    	if (curGrpIdx > 0) {
    		grpLeft.setVisibility(View.VISIBLE);
    	} else {
    		grpLeft.setVisibility(View.INVISIBLE);
    	}
    	
    	this.updateChannels();
    }
    
	private void updateChannels() {
		TVChannel[] channels = this.mChnManager.getFocusChannels();  	
    	int curGrpIdx = this.mChnManager.getFocusGrpIdx();
    	int curGrpSelIdx = this.mChnManager.getSelGrpIdx();
    	int curChnIdx = this.mChnManager.getFocusChnIdx();
    	int curChnSelIdx = this.mChnManager.getSelChnIdx();
    	
    	// 移动焦点的方式是光标停留在列表中间，直到前后没有数据了，光标才向前后移动
    	int startIdx = 0;
    	if (channels != null && channels.length > 0) {
	    	int halfLen = this.mChnLists.size() / 2;
	    	int endIdx = curChnIdx + halfLen;
	    	if (endIdx >= channels.length) {
	    		endIdx = channels.length - 1;
	    	}
	    	startIdx = endIdx - halfLen * 2;
	    	if (startIdx < 0) {
	    		startIdx = 0;
	    	}
    	}
    	
    	for (int i = 0; i < this.mChnLists.size(); ++i) {
    		View v = this.mChnLists.get(i);
    		int iconId = R.id.tv_list_item_fav_icon;
    		int txtId = R.id.tv_list_item_text;
    		int colorId = R.color.tv_white;
    		ImageView imgv = (ImageView)v.findViewById(iconId);
    		TextView txtv = (TextView)v.findViewById(txtId);
    		int defColor = this.getResources().getColor(colorId);
    		
    		imgv.setVisibility(View.GONE);
			txtv.setVisibility(View.GONE);
			txtv.setTextColor(defColor);
			v.setBackgroundResource(0);
    		
    		if (channels != null && i + startIdx < channels.length) {
    			TVChannel chn = channels[startIdx + i];
    			if (chn.isFavorite()) {
    				imgv.setVisibility(View.VISIBLE);
    			}
    			txtv.setVisibility(View.VISIBLE);
    			txtv.setText(chn.getNumber() + " " + chn.getName());
    			if (startIdx + i == curChnIdx) {
    				v.setBackgroundResource(R.drawable.tv_list_item_focus);
    			}
    			
    			boolean mark = (curGrpIdx == curGrpSelIdx);
    			mark = mark && (startIdx + i == curChnSelIdx);
    			if (mark) {
    				colorId = R.color.tv_yellow;
    				defColor = this.getResources().getColor(colorId);
    				txtv.setTextColor(defColor);
    			}
    		}
    	}
    }
	
	private void startChnListAnimation(int dir) {
		final View v = this.mChnListView.findViewById(R.id.tv_list_items);
    	v.setVisibility(View.INVISIBLE);
		TranslateAnimation animation;
		animation = new TranslateAnimation(dir * 368, 0, 0, 0);
		animation.setDuration(TVActivity.AnimTime);
		animation.setAnimationListener(new Animation.AnimationListener() {			
			@Override
			public void onAnimationStart(Animation animation) { }			
			@Override
			public void onAnimationRepeat(Animation animation) {}			
			@Override
			public void onAnimationEnd(Animation animation) {
				v.setVisibility(View.VISIBLE);
			}
		});
		v.clearAnimation();
		v.setAnimation(animation);
		animation.startNow();
		v.invalidate();
	}
	
	private void showChannelList() {
    	if (this.mChnListView.getVisibility() != View.VISIBLE) {
	    	View grpRight = this.mChnListView.findViewById(R.id.tv_list_right);
	    	grpRight.clearAnimation();
	    	AlphaAnimation animation = new AlphaAnimation(0, 1);
			animation.setDuration(TVActivity.AnimTime);
			animation.setRepeatCount(3);
			grpRight.setAnimation(animation);
			animation.startNow();
			grpRight.invalidate();
    	}
    	
    	int msg = MSG_HIDE_CHANNEL_LIST;
		int timeout = ShowListTimeout;
		this.mChnListView.setVisibility(View.VISIBLE);
    	this.mMsgHandler.removeMessages(msg);
    	this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
    	this.hidePlaybar();
    	this.hideChannelNum();
    	this.mOptionView.hide();
	}
	
	private void showPlaybar(boolean auto) {
		int msg = MSG_HIDE_PLAYBAR;
		int timeout = ShowListTimeout;
		this.mMsgHandler.removeMessages(msg);
		if (auto) {
			this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
		}
    	if (this.mPlaybarView.getVisibility() != View.VISIBLE) {
    		this.updatePlaybar(this.mDuration,	this.mCurrent, this.mSeekPos);
	    	this.updateEpg();
	    	this.mPlaybarView.setVisibility(View.VISIBLE);
    	}
    	this.hideChannelNum();
    	this.mChnListView.setVisibility(View.GONE);
    	this.mOptionView.hide();
	}
	
	private void keyNumInput(int num) {
		this.mChannel *= 10;
		this.mChannel += num;
		this.mChannel %= 1000;
		
		int msg = MSG_CHANNEL_TIMEOUT;
		this.mMsgHandler.removeMessages(msg);
		this.mMsgHandler.sendEmptyMessageDelayed(msg, ChannelTimeout);
		String strnum = String.format(Locale.CHINA, "%03d", this.mChannel);
		this.mChannelView.setText(strnum);
		this.mChannelView.setVisibility(View.VISIBLE);
	}
	
	private void hideChannelNum() {
		this.mChannel = 0;
		this.mChannelView.setVisibility(View.GONE);
		this.mMsgHandler.removeMessages(MSG_CHANNEL_TIMEOUT);
	}
	
	private void playThisChannel() {
		String chn = String.format(Locale.CHINA, "%03d", this.mChannel);
		this.updateFavList();
		if (this.mChnManager.findChannel(0, chn)) {
			this.updateGroups();			
    		this.showPlaybar(false);
    		this.play(null);
		} else {
			Resources res = this.getResources();
			String txt = chn + res.getString(R.string.tv_no_such_chn);
			this.showDialog(txt);
			this.setLoadingPercent(100);
		}
		this.hideChannelNum();
	}
	
	private void showDialog(String text, int timeout) {
		if(timeout != 0)
		{
			int msg = MSG_DIALOG_TIMEOUT;
			this.mDialogView.setText(text);
			this.mDialogView.setVisibility(View.VISIBLE);
			this.mMsgHandler.removeMessages(msg);
			if(timeout != 0xff)
				this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout*1000);
		}
		else
		{
			this.hideDialog();
		}

	}


	void showDialog(String text) {
		int msg = MSG_DIALOG_TIMEOUT;
		this.mDialogView.setText(text);
		this.mDialogView.setVisibility(View.VISIBLE);
		this.mMsgHandler.removeMessages(msg);
		this.mMsgHandler.sendEmptyMessageDelayed(msg, DialogTimeout);
	}

	void showDialog() {
		if(getUdrm_info_timeout() == 0xff)
			this.showDialog(udrmStatusTxt,getUdrm_info_timeout());		
	}


	void hideDialog() {
		this.mMsgHandler.removeMessages(MSG_DIALOG_TIMEOUT);
		this.mDialogView.setVisibility(View.GONE);
	}
	
	private void hidePlaybar() {
		this.mPlaybarView.setVisibility(View.GONE);
		this.mMsgHandler.removeMessages(MSG_HIDE_PLAYBAR);
    	this.mMsgHandler.removeMessages(MSG_SEEK_TIMEOUT);
    	this.mSeekPos = -1;
    	this.mSeekKeyCount = 0;
    	this.mSeekKeyTime = 0;
	}
	
	private void showOptions() {
		int msg = MSG_HIDE_OPTION;
		int timeout = ShowListTimeout;
		this.mOptionView.show();
		this.mMsgHandler.removeMessages(msg);
		this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
		this.hideChannelNum();
		this.hidePlaybar();
	}
	
	public void toggleFavorite() {
		this.mChnManager.toggleFavorite();
		this.updateChannels();
	}
	
	private void updatePlaybar(TVChannel channel) {
		int nameId = R.id.tv_playbar_chn_name;
		int numId = R.id.tv_playbar_chn_num;
		TextView name = (TextView)this.mPlaybarView.findViewById(nameId);
		TextView num = (TextView)this.mPlaybarView.findViewById(numId);
		if (channel != null) {			
			name.setText(channel.getName());
			num.setText(channel.getNumber());
		} else {
			name.setText("");
			num.setText("");
		}
	}
	
	private void updatePlaybar(int duration, int current, int seek) {
		TVChannel chn = this.mChnManager.getSelChannel();
		if (null == chn) {
			return;
		}
		if (chn.getType() != TVChannel.NET_TURN_NODE && null == this.mEpgItem) {
			return;
		}
		
		class IntToStr {
			@SuppressLint("DefaultLocale")
			public String toTimeStr(int time) {
				int minute = time / 60;
				time %= 60;
				int second = time;
				return String.format("%02d:%02d", minute, second);
			}
		};
		
		int timeId = R.id.tv_playbar_time;
		TextView time = (TextView)this.mPlaybarView.findViewById(timeId);
		
		IntToStr timeutil = new IntToStr();
		String timestr = timeutil.toTimeStr(current / 1000);
		if (seek >= 0) {
			timestr = timeutil.toTimeStr(seek / 1000);
		}
		int timePercent = 0;
		int seekPercent = 0;
		if (duration > 0) {
			timestr += "/";
			timestr += timeutil.toTimeStr(duration / 1000);
			timePercent = current * 100 / duration;
			if (seek >= 0) {
				seekPercent = seek * 100 / duration;
			}
		}
		time.setText(timestr);
		int color = R.color.tv_white;
		if (seek >= 0) {			
			color = R.color.tv_yellow;			
		}
		Resources res = this.getResources();
		time.setTextColor(res.getColor(color));
		
		this.updateProgress(timePercent, seekPercent);
	}
	
	private void updateProgress(int curper, int seekper) {
		int progId = R.id.tv_playbar_progress;
		int seekId = R.id.tv_playbar_seek;
		int dotId = R.id.tv_playbar_dot;
		
		View prgrView = this.mPlaybarView.findViewById(progId);
		View seekView = this.mPlaybarView.findViewById(seekId);
		View dotView = this.mPlaybarView.findViewById(dotId);
		
		ViewGroup.LayoutParams prglp = prgrView.getLayoutParams();
		ViewGroup.LayoutParams seeklp = seekView.getLayoutParams();
		ViewGroup.LayoutParams dotlp = dotView.getLayoutParams();
		
		if (curper < 0) {
			curper = 0;
		}
		if (curper > 100) {
			curper = 100;
		}
		if (seekper < 0) {
			seekper = 0;
		}
		if (seekper > 100) {
			seekper = 100;
		}
		
		int maxLen = 922;
		prglp.width = maxLen * curper / 100;
		prgrView.setLayoutParams(prglp);
		seeklp.width = maxLen * seekper / 100;
		seekView.setLayoutParams(seeklp);
		
		RelativeLayout.LayoutParams rlp;
		rlp = new RelativeLayout.LayoutParams(dotlp);
		rlp.addRule(RelativeLayout.ALIGN_PARENT_LEFT);
		rlp.addRule(RelativeLayout.ALIGN_PARENT_TOP);
		rlp.topMargin = 43;
		if (seekper > 0) {
			rlp.leftMargin = seeklp.width + 198;
		} else {
			rlp.leftMargin = prglp.width + 198;
		}
		if (curper > seekper) {
			seekView.bringToFront();
		} else {
			prgrView.bringToFront();
		}
		
		TVChannel chn = this.mChnManager.getSelChannel();
		if (chn != null && TVChannel.NET_TURN_NODE != chn.getType() &&
				null == this.mEpgItem) {
			dotView.setVisibility(View.GONE);
		} else {
			dotView.setVisibility(View.VISIBLE);
		}		
		dotView.setLayoutParams(rlp);
		dotView.bringToFront();
	}
	
	private void updatePlaybar(EpgItem[] epgs) {
		int epg1Id = R.id.tv_playbar_epg1;
		int epg2Id = R.id.tv_playbar_epg2;
		int timeId = R.id.tv_playbar_time;
		TextView epg1 = (TextView)mPlaybarView.findViewById(epg1Id);
		TextView epg2 = (TextView)mPlaybarView.findViewById(epg2Id);
		TextView time = (TextView)mPlaybarView.findViewById(timeId);
		
		Resources res = this.getResources();
		TVChannel chn = this.mChnManager.getSelChannel();
		String epg2Str = res.getString(R.string.tv_epg_next_txt);
		
		if (chn != null && this.mEpgItem != null && 
				this.mEpgItem.canLiveBack() &&
				chn.getType() != TVChannel.NET_TURN_NODE) {
			String epglbStr = res.getString(R.string.tv_live_back_txt);
			String liveStr = res.getString(R.string.tv_live_txt);
			epg1.setText(epglbStr + this.mEpgItem.getTitle());
			epg2.setText(epg2Str + chn.getName() + liveStr);
			time.setText("00:00");
			this.updateProgress(0, 0);
			return;
		}
		
		class TimePercent {
			private int getHour(String time) {
				int pos = time.indexOf(":");
				if (pos > 0) {
					return Integer.parseInt(time.substring(0, pos), 10);
				}
				return 0;
			}
			private int getMinute(String time) {
				int pos = time.indexOf(":");
				if (pos > 0 && pos < time.length()) {
					return Integer.parseInt(time.substring(pos + 1), 10);
				}
				return 0;
			}
			public int getPercent(String start, String end) {
				if (!Pattern.matches("[0-2][0-9]:[0-5][0-9]", start)) {
					Log.e(Tag, "invalid input format for time:" + start);
					return 0;
				} 
				if (!Pattern.matches("[0-2][0-9]:[0-5][0-9]", end)) {
					Log.e(Tag, "invalid input format for time:" + end);
					return 0;
				}
				
				int h1 = this.getHour(start);
				int m1 = this.getMinute(start);
				
				int h2 = this.getHour(end);
				int m2 = this.getMinute(end);
				if (h2 < h1) {
					h2 += 24;
				}

				String now = new TimeUtil().getCurrentTime();
				int nh = this.getHour(now);
				int nm = this.getMinute(now);
				if (nh < h1) {
					nh += 24;
				}
				
				int c = Calendar.getInstance().get(Calendar.SECOND);
				int t1 = ((h2 - h1) * 60 + (m2 - m1)) * 60;
				int t2 = ((nh - h1) * 60 + (nm - m1)) * 60 + c;
				
				return 100 * t2 / t1;
			}
		};
		
		TimePercent tp = new TimePercent();
		EpgItem eitem = null;
		String epg1Str = res.getString(R.string.tv_epg_start_txt);
		epg1.setText(epg1Str);
		epg2.setText(epg2Str);
		
		if (chn != null && chn.getType() != TVChannel.NET_TURN_NODE) {
			time.setText(new TimeUtil().getCurrentTime());
			this.updateProgress(0, 0);
		}
		
		if (chn != null && chn.getType() == TVChannel.NET_TURN_NODE &&
				epgs != null && epgs.length > 2) {
			TVProgram program = this.mChnManager.getSelProgram();
			if (program != null) {
				int idx = -1;
				for (int i = 0; i < epgs.length; ++i) {
					if (epgs[i].getTitle().equals(program.getName())) {
						idx = i;
						break;
					}
				}
				if (idx != -1) {
					EpgItem[] tmp = epgs;
					epgs = new EpgItem[2];
					epgs[0] = tmp[idx];
					if (idx >= tmp.length - 1) {
						epgs[1] = tmp[0];
					} else {
						epgs[1] = tmp[idx + 1];
					}
				}
			}
		}
		
		if (epgs != null) {
			if (epgs.length > 0) {
				eitem = epgs[0];				
				epg1.setText(epg1Str + eitem.getTitle());
				if (chn != null && chn.getType() != TVChannel.NET_TURN_NODE) {
					String start = eitem.getStartTime();
					String end = eitem.getEndTime();
					int percent = tp.getPercent(start, end);
					this.updateProgress(percent, 0);
				}
			}
			if (epgs.length > 1) {
				eitem = epgs[1];
				epg2.setText(epg2Str + eitem.getTitle());
			}
		}
	}
		
	private void updateEpg() {
		TVChannel channel = this.mChnManager.getSelChannel();
		if (null == channel) {
			return;
		}
		if (this.mEpgItem != null) {
			EpgItem[] epgs = null;
			this.updatePlaybar(epgs);
			return;
		}
		
		if (this.mEpgTask != null) {
			this.mEpgTask.cancel(true);
		}
		this.mEpgTask = new EpgTask();
		Executor exec = Executors.newCachedThreadPool();
		this.mEpgTask.executeOnExecutor(exec, channel);
	}
	
	private void updateFavList() {
		long t = System.currentTimeMillis();
		t -= this.mLastPlayTime;
		if (t >= MinRecordTime) {
			this.mChnManager.addWatchElapse(t);
		}
		this.mLastPlayTime = Long.MAX_VALUE;
		this.mMsgHandler.removeMessages(MSG_RECORD_TIMEOUT);
	}
	
	private void refreshFavList() {
		long now = System.currentTimeMillis();
		long t = now - this.mLastPlayTime;
		if (t >= MinRecordTime) {
			this.mChnManager.addWatchElapse(t);
			this.mLastPlayTime = now;
		}
		int msg = MSG_RECORD_TIMEOUT;
		this.mMsgHandler.removeMessages(msg);
		this.mMsgHandler.sendEmptyMessageDelayed(msg, MinRecordTime);
	}

	@Override
	public void onPrepared(MediaPlayer mp) {
		this.setLoadingPercent(100);
		this.mVideoView.start();
		
		if (TV_NET == this.mTVType) { // DVB don't need it
			int cur = this.mChnManager.getCurrentTime();			
			if (cur > 0) {
				Log.d(Tag, "directly seek to time: " + cur);
				this.mVideoView.seekTo(cur);
				this.mCurrent = cur;
			}
		}
		
		// 确保播放起来后才开始计算隐藏playbar的时间
		int msg = MSG_HIDE_PLAYBAR;
		int timeout = ShowListTimeout;
		this.mMsgHandler.removeMessages(msg);
		this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
		// 确保播放起来后才保存之前的选源选集记录
		this.mChnManager.saveSrcHistory();
		this.mLastPlayTime = System.currentTimeMillis();
		this.refreshFavList();
	}

	@Override
	public void onSeekComplete(MediaPlayer mp) {
		this.setLoadingPercent(100);
	}

	@Override
	public boolean onInfo(MediaPlayer mp, int what, int extra) {
		return false;
	}
	
	public void notifyEvent(String event) {
		this.mOptionView.appNotify(event, null);
	}

	@Override
	public boolean onError(MediaPlayer mp, int what, int extra) {
		this.updateFavList();
		if (null == this.mEpgItem) { // 回看过程中播放出错不需要换源
			this.mChnManager.changeSelSource(1);
			if (0 == this.mChnManager.getSelSrcIdx()) {
				int msg = MSG_DELAY_PLAY;
				int timeout = DelayPlayTimeout;
				this.mMsgHandler.removeMessages(msg);
				this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout);
				
				Resources res = this.getResources();
				String txt = res.getString(R.string.tv_temp_invalid);
				this.showDialog(txt);
				this.setLoadingPercent(100);
				
				Log.d(Tag, "all sources is tried! delay play for 5 seconds!");
				return true;
			}
		}
		this.play(null);
		return true;
	}

	@Override
	public void onCompletion(MediaPlayer mp) {
		this.updateFavList();
		// 播放完成，如果是轮播则播放下一个节目，如果是直播，因为只有一个节目
		// 所以会使用当前源重新播放
		this.mChnManager.changeSelProgram(1);
		this.play(null);
	}

	@Override
	public void onBufferingUpdate(MediaPlayer mp, int percent) {
		// 节目源的下载百分比
	}

	@Override
	public void onUpdate(UpdateEvent event) {
		if (event == UpdateEvent.ProgramsUpdate) {
			this.mChnManager.setUpdateListener(null);
			this.play(null);
		} else if (event == UpdateEvent.GruopsUpdate) {
			this.updateGroups();
			this.play(null);
		}
	}



	void showUdrmOsd(String text,int timeout) {
		int msg = MSG_OSD_TIMEOUT;
		this.mUdrmOsdView.setText(text);
		this.mUdrmOsdView.setVisibility(View.VISIBLE);
		if(timeout != 0xff)
		{
			this.mMsgHandler.removeMessages(msg);
			this.mMsgHandler.sendEmptyMessageDelayed(msg, timeout*1000);
		}
	}


	void hideUdrmOsd() {
		this.mMsgHandler.removeMessages(MSG_OSD_TIMEOUT);
		this.mUdrmOsdView.setVisibility(View.GONE);
	}

	public int getUdrm_info_timeout() {
		return udrm_info_timeout;
	}


	public void setUdrm_info_timeout(int udrm_info_timeout) {
		this.udrm_info_timeout = udrm_info_timeout;
	}



}
