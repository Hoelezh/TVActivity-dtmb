package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.alitech.dvb.DvbSystem;
import com.alitech.dvb.DvbTpNode;
import com.nmp.dvbplayer.R;

import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

public class TVTpList extends Activity {
	private static final int    TpPageSize = 8;
	
	private int FocusID;
	private ArrayList<View> mTpLists;
	private int parent_focus;
	
	private DVBSatelliteNode[] parent_sat_node;
	private DvbTpNode[] tp_nodes;

	
	
	private class TunerStatusTask extends AsyncTask<Void, Void, int[]> {
		@Override
		protected int[] doInBackground(Void... params) {
			int lock = 0, SNR = 0, AGC = 0;
			int [] result;
			
			lock = DvbSystem.getTunerLock();
			SNR = DvbSystem.getTunerSNR();
			AGC = DvbSystem.getTunerAGC();
			
			result = new int [3];
			
			result[0] = lock;
			result[1] = SNR;
			result[2] = AGC;

			return result;
			
		}
		@Override
		protected void onPostExecute(int[] result) {
			Log.d("tuner status", "lock="+String.valueOf(result[0])+"SNR="+
					String.valueOf(result[1])+"agc="+String.valueOf(result[2]));
			
			updateTunerStatus(result[0], result[1], result[2]);
			
		}
	};
	
	
	private TunerStatusTask mTunerTask = null;
	
	private Thread mThread;
	
	private Handler mHandler; 
	
	private boolean mRunning = false;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.tv_tp_list);
		
		int rid = R.id.tv_tp_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);
		
		this.mTpLists = new ArrayList<View>();
		for (int i = 0; i < TpPageSize; ++i ) {
			View.inflate(this, R.layout.tv_tp_item, lLayout);
		}
		for (int i = 0; i < lLayout.getChildCount(); ++i) {
			this.mTpLists.add(lLayout.getChildAt(i));
		}	
		
		FocusID = 0;

		Intent intent = this.getIntent(); 
		//this.parent_sat_node = (DVBSatelliteNode [])intent.getSerializableExtra("satnode");
		this.parent_focus = intent.getIntExtra("fucos", 0);
		this.parent_sat_node = DVBSatellite.loadSatelliteNodes();
		
		/*
		//HandlerThread thread = new HandlerThread("MyHandlerThread"); 

		//mHandler = new Handler(thread.getLooper());//使用HandlerThread的looper对象创建Handler，如果使用默认的构造方法，很有可能阻塞UI线程 
		//mHandler.post(mBackgroundRunnable);//将线程post到Handler中
		
		//thread.start();//创建一个HandlerThread并启动它 
		  mThread = new Thread(mBackgroundRunnable, "CancelableThread");
          mThread.start();
          //mBackgroundRunnable.run();
           */
		mRunning = true;
		mHandler = new Handler() {
			int lock = 0, SNR = 0, AGC = 0;
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                case 0:
    				lock = DvbSystem.getTunerLock();
    				SNR = DvbSystem.getTunerSNR();
    				AGC = DvbSystem.getTunerAGC();
    				updateTunerStatus(lock, SNR, AGC);
    				break;
                }
            }
        };
      
        mThread = new Thread(new Runnable() {

            @Override
            public void run() {
                try {
                    while (mRunning) {
                        Thread.currentThread().sleep(1000);
                        Message message = new Message();
                        message.what = 0;
                        mHandler.sendMessage(message);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

            }
        });
        mThread.start();


	}
	
	
	//实现耗时操作的线程 
	Runnable mBackgroundRunnable = new Runnable() { 

		int lock = 0, SNR = 0, AGC = 0;
		@Override 
		public void run() { 
	//----------模拟耗时的操作，开始--------------- 
			while(mRunning) { 

				
				lock = DvbSystem.getTunerLock();
				SNR = DvbSystem.getTunerSNR();
				AGC = DvbSystem.getTunerAGC();
				
				updateTunerStatus(lock, SNR, AGC);
				
				try { 
					Thread.sleep(200); 
				} catch (InterruptedException e) { 
					e.printStackTrace(); 
				} 
			} 
	//----------模拟耗时的操作，结束--------------- 
		} 
	}; 

	
	@Override
	protected void onStart() {
		super.onStart();
		
	}
	
	@Override
	protected void onResume() {
		super.onResume();

		updateTitle();
		updateTplist();
		mRunning = true;
		
		/*
		if (this.mTunerTask != null) {
			this.mTunerTask.cancel(true);
		}
		this.mTunerTask = new TunerStatusTask();
		Executor exec = Executors.newCachedThreadPool();
		this.mTunerTask.executeOnExecutor(exec);
		*/
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		if (this.mTunerTask != null) {
    		this.mTunerTask.cancel(true);
    	}
		mRunning = false;
	}
	
	@Override
	protected void onStop() {
		super.onStop();
		
		mRunning = false;
	}
	
	@Override 
	protected void onDestroy() { 
		super.onDestroy(); 
	} 

	
	private void updateTitle() {
		if(this.parent_sat_node != null) {
			this.tp_nodes = this.parent_sat_node[parent_focus].getChildrenNodes();
			
			TextView title = (TextView) this.findViewById(R.id.tv_tplist_satname);
			
			title.setText(this.parent_sat_node[parent_focus].getName());
		}
	}
	
	private void updateTplist() {
		
		int startIdx = 0;
		DvbTpNode tp;
		
    	if (this.tp_nodes != null && this.tp_nodes.length > 0) {
	    	int halfLen = this.mTpLists.size() / 2;
	    	int endIdx = FocusID + halfLen;
	    	if (endIdx >= this.tp_nodes.length) {
	    		if((this.mTpLists.size()%2)==1)
	    		endIdx = this.tp_nodes.length - 1;
	    		else
	    			endIdx = this.tp_nodes.length;
	    	}
	    	startIdx = endIdx - halfLen * 2;
	    	if (startIdx < 0) {
	    		startIdx = 0;
	    	}
    	}
    	else {
			return;
		}
    	
    	for (int i = 0; i < this.mTpLists.size(); ++i) {
    		View v = this.mTpLists.get(i);

       		TextView txtid = (TextView)v.findViewById(R.id.tv_tp_item_id);
       		TextView txtfreq = (TextView)v.findViewById(R.id.tv_tp_item_freq);
       		TextView txtsymble = (TextView)v.findViewById(R.id.tv_tp_item_symbol);
      		TextView txtpol = (TextView)v.findViewById(R.id.tv_tp_item_pol);
    		  		
    		int defColor = this.getResources().getColor(R.color.tv_white);
    		
    		txtid.setVisibility(View.GONE);
    		txtid.setTextColor(defColor);
    		txtsymble.setVisibility(View.GONE);
    		txtsymble.setTextColor(defColor);
    		txtfreq.setVisibility(View.GONE);
    		txtfreq.setTextColor(defColor);
    		txtpol.setVisibility(View.GONE);
    		txtpol.setTextColor(defColor); 	
    		
			v.setBackgroundResource(0);
    		
    		if (this.tp_nodes != null && i + startIdx < this.tp_nodes.length) {
    			tp = this.tp_nodes[startIdx + i];

    			txtid.setVisibility(View.VISIBLE);
    			txtsymble.setVisibility(View.VISIBLE);
    			txtfreq.setVisibility(View.VISIBLE);
    			txtpol.setVisibility(View.VISIBLE);
    			
    			txtid.setText(String.valueOf(i+startIdx+1));
    			
    			int freq = tp.getFreq();
    			txtfreq.setText(String.valueOf(freq)+" MHz");
    			
    			int symbol = tp.getSymbol();
    			txtsymble.setText(String.valueOf(symbol)+" Ks/s");
    			
    			int pol = tp.getPol();
    			if(pol == 0) {
    				txtpol.setText("H");
    			}
    			else {
    				txtpol.setText("V");
    			}
    			
    			if (startIdx + i == FocusID) {
    				v.setBackgroundResource(R.drawable.tv_list_item_focus);
    			}

    		}
    	}
    	
    	tp = this.tp_nodes[FocusID];
    	
    	DvbSystem.LockFreq(tp.getParentId(), tp.getId());
    	/*
		if (this.mTunerTask != null) {
			this.mTunerTask.cancel(true);
		}
		this.mTunerTask = new TunerStatusTask();
		Executor exec = Executors.newCachedThreadPool();
		this.mTunerTask.executeOnExecutor(exec);
*/
	}

	private void updateTunerStatus(int lock, int snr, int agc) {
		
		int rid = R.id.tv_tp_bar1_value;
		TextView intensity = (TextView)this.findViewById(rid);
		rid = R.id.tv_tp_bar2_value;
		TextView quality = (TextView)this.findViewById(rid);
		
		ProgressBar intensityBar = (ProgressBar) this.findViewById(R.id.tv_tp_bar1_bar);
		ProgressBar qualityBar = (ProgressBar) this.findViewById(R.id.tv_tp_bar2_bar);
		
		if(agc>90)
			agc = 90;
		
		if (agc < 10)
			agc = agc * 11/2;
		else 
			agc = agc / 2 + 50;       
		
		if(agc>90)
			agc = 90;
		
		if(lock == 0)
			agc = agc/2;
		
	 	if(lock != 0)    
	 	{
	 	    if (snr < 30)
	 	    	snr = snr * 7/ 3;
	 	    else
	 	    	snr = snr / 3 + 60; 
	 	}
	 	else
	 	{
	 		if (snr >= 20)
	 			snr =  snr * 3/ 7;
	  	}
	 	
	 	if(snr>90)
	 		snr = 90;
	 	
	 	intensity.setText(String.valueOf(agc)+"%");
	 	quality.setText(String.valueOf(snr)+"%");
	 	
	 	
	 	if(lock == 0) {
		 	intensityBar.setProgress(0);
		 	qualityBar.setProgress(0);
	 		intensityBar.setSecondaryProgress(agc);
	 		qualityBar.setSecondaryProgress(snr);
	 		
	 	}
	 	else {
	 		intensityBar.setProgress(agc);
		 	qualityBar.setProgress(snr);
	 		intensityBar.setSecondaryProgress(0);
	 		qualityBar.setSecondaryProgress(0);
	 	}
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		boolean keyHandled = false;
		
		if (keyCode == KeyEvent.KEYCODE_1) {
			if (this.tp_nodes == null || this.tp_nodes.length == 0) {
				return true;
			}
			DvbTpNode tp = this.tp_nodes[FocusID];
			
			if(tp == null) {
				return true;
			}
			
			
			Intent intent = new Intent(TVTpList.this, TVSatelliteEdit.class);
			
			Bundle bundle = new Bundle();
			bundle.putSerializable("tpnode", tp);
			intent.putExtra("type", 3);
			
			intent.putExtras(bundle);

			this.startActivity(intent);
			
			return true;
		}	
		else if(KeyEvent.KEYCODE_2 == keyCode) {
			Intent intent = new Intent(TVTpList.this, TVSatelliteEdit.class);
			intent.putExtra("type", 4);
			intent.putExtra("snode_id", this.parent_sat_node[parent_focus].getId());
			this.startActivity(intent);
			return true;
		}
		else if(KeyEvent.KEYCODE_3 == keyCode) {
			DvbTpNode tp = this.tp_nodes[FocusID];
			Intent intent = new Intent(TVTpList.this, TVSatelliteEdit.class);
			intent.putExtra("type", 6);
			intent.putExtra("tp_id", tp.getId());
			intent.putExtra("sat_id", tp.getParentId());
			this.startActivity(intent);

			return true;
		}
		else if (KeyEvent.KEYCODE_DPAD_UP == keyCode ||
				KeyEvent.KEYCODE_DPAD_DOWN == keyCode ) {
			onPressUpDown(keyCode, event);
			return true;
		}
		else if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode ||
				KeyEvent.KEYCODE_DPAD_RIGHT == keyCode ) {
			onPressLeftRight(keyCode, event);
			return true;
		}
		
		if(keyHandled == false)
			keyHandled = super.onKeyDown(keyCode, event);
		
		return keyHandled;
	}
	
	
	private void onPressUpDown(int keyCode, KeyEvent event) {
		if (KeyEvent.KEYCODE_DPAD_UP == keyCode) {
			this.changeFocus(-1);
		}
		
		if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode) {
			this.changeFocus(1);
		}
		
		this.updateTplist();
	}
	
	private void onPressLeftRight(int keyCode, KeyEvent event) {
		if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
			this.changeGroup(-1);
		}
		
		if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			this.changeGroup(1);
		}
		
		this.updateTplist();
	}
	
	private void changeGroup(int diff) {
    	if (this.parent_sat_node != null && this.parent_sat_node.length > 0) {
    		parent_focus = parent_focus+diff;
    		if(parent_focus < 0) {
    			parent_focus = this.parent_sat_node.length - 1;
    		}
    		else if(parent_focus == this.parent_sat_node.length) {
    			parent_focus = 0;
    		}
    		
    		updateTitle();
    		updateTplist();
    	}
	}
	
	private void changeFocus(int diff) {
    	if (this.tp_nodes != null && this.tp_nodes.length > 0) {
    		FocusID = FocusID+diff;
    		if(FocusID < 0) {
    			FocusID = this.tp_nodes.length - 1;
    		}
    		else if(FocusID == this.tp_nodes.length) {
    			FocusID = 0;
    		}
    	}
	}
	
}
