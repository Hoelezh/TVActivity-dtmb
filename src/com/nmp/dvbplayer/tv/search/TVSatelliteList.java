package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.nmp.dvbplayer.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class TVSatelliteList extends Activity {
	
	
	private static final int    SatPageSize = 9;
	
	
	
	private DVBSatelliteNode[] sat_nodes;
	private ArrayList<View> mSatLists;
	private int    FocusID = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		this.sat_nodes = null;
		setContentView(R.layout.tv_satellite_list);
		
		int rid = R.id.tv_satellite_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);
		this.mSatLists = new ArrayList<View>();
		for (int i = 0; i < SatPageSize; ++i ) {
			View.inflate(this, R.layout.tv_satlist_item, lLayout);
		}
		for (int i = 0; i < lLayout.getChildCount(); ++i) {
			this.mSatLists.add(lLayout.getChildAt(i));
		}	
		
		FocusID = 0;
		
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		
		
		
	}
	@Override
	protected void onResume() {
		super.onStart();
		this.sat_nodes = DVBSatellite.loadSatelliteNodes();
		updateSats();
	}
	
	private void updateSats() {
		
		int startIdx = 0;
    	if (this.sat_nodes != null && this.sat_nodes.length > 0) {
	    	int halfLen = this.mSatLists.size() / 2;
	    	int endIdx = FocusID + halfLen;
	    	if (endIdx >= this.sat_nodes.length) {
	    		endIdx = this.sat_nodes.length - 1;
	    	}
	    	startIdx = endIdx - halfLen * 2;
	    	if (startIdx < 0) {
	    		startIdx = 0;
	    	}
    	}
    	
    	for (int i = 0; i < this.mSatLists.size(); ++i) {
    		View v = this.mSatLists.get(i);

       		TextView txtid = (TextView)v.findViewById(R.id.tv_satlist_item_id);
       		TextView txtname = (TextView)v.findViewById(R.id.tv_satlist_item_name);
       		TextView txtorbit = (TextView)v.findViewById(R.id.tv_satlist_item_orbit);
       		
    		ImageView imglnb1 = (ImageView)v.findViewById(R.id.tv_satlist_item_lnb1);
    		ImageView imglnb2 = (ImageView)v.findViewById(R.id.tv_satlist_item_lnb2);
    		
    		int defColor = this.getResources().getColor(R.color.tv_white);
    		
    		imglnb1.setVisibility(View.GONE);
    		imglnb2.setVisibility(View.GONE);
    		txtid.setVisibility(View.GONE);
    		txtid.setTextColor(defColor);
    		txtname.setVisibility(View.GONE);
    		txtname.setTextColor(defColor);
    		txtorbit.setVisibility(View.GONE);
    		txtorbit.setTextColor(defColor);
    		
			v.setBackgroundResource(0);
    		
    		if (this.sat_nodes != null && i + startIdx < this.sat_nodes.length) {
    			DVBSatelliteNode sat = this.sat_nodes[startIdx + i];

    			txtid.setVisibility(View.VISIBLE);
    			txtname.setVisibility(View.VISIBLE);
    			txtorbit.setVisibility(View.VISIBLE);
    			
    			txtid.setText(String.valueOf(i+startIdx+1));
    			txtname.setText(sat.getName());
    			
    			int orbit = sat.getorbit();
    			boolean flag = false;
    			float forbit;
    			if(orbit > 1800) {
    				orbit = 3600 - orbit;
    				flag = false;
    			}
    			else {
    				flag = true;
				}
    			
    			forbit = (float)orbit/10;
    			
    			if(flag) {
    				txtorbit.setText("E " + String.valueOf(forbit));
    			}
    			else {
    				txtorbit.setText("W " + String.valueOf(forbit));
    			}
    			
    			//if(sat.istuner1valid()) {
    			if(sat.isselect()) {
    				imglnb1.setVisibility(View.VISIBLE);
    			}
    			
    				
    			if (startIdx + i == FocusID) {
    				v.setBackgroundResource(R.drawable.tv_list_item_focus);
    			}

    		}
    	}

	}
	
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		boolean keyHandled = false;
		
		if (keyCode == KeyEvent.KEYCODE_1) {
			if (this.sat_nodes == null || this.sat_nodes.length == 0) {
				return true;
			}
			DVBSatelliteNode sat = this.sat_nodes[FocusID];
			
			if(sat == null) {
				return true;
			}
			
			//View view = this.findViewById(R.layout.tv_satellite_edit);
			
			//if(view.getVisibility() != View.VISIBLE)
			//	view.setVisibility(View.VISIBLE);
			
			
			Intent intent = new Intent(TVSatelliteList.this, TVSatelliteEdit.class);
			
			Bundle bundle = new Bundle();
			bundle.putSerializable("satnode", sat);
			intent.putExtra("type", 1);
			
			intent.putExtras(bundle);

			this.startActivity(intent);
			
			return true;
		}			
		else if (KeyEvent.KEYCODE_2 == keyCode) {
			Intent intent = new Intent(TVSatelliteList.this, TVSatelliteEdit.class);
			
			intent.putExtra("type", 2);

			this.startActivity(intent);
			return true;
		}
		else if (KeyEvent.KEYCODE_3 == keyCode) {
			DVBSatelliteNode sat = this.sat_nodes[FocusID];
			Intent intent = new Intent(TVSatelliteList.this, TVSatelliteEdit.class);
			
			intent.putExtra("type", 5);
			intent.putExtra("snode_id", sat.getId());
			this.startActivity(intent);
			return true;
		}
		else if (KeyEvent.KEYCODE_F11 == keyCode) {
			Intent intent = new Intent(TVSatelliteList.this, TVAntenna.class);

			this.startActivity(intent);
			return true;
		}
		else if (KeyEvent.KEYCODE_DPAD_UP == keyCode ||
				KeyEvent.KEYCODE_DPAD_DOWN == keyCode ) {
			onPressUpDown(keyCode, event);
			return true;
		}
		else if (KeyEvent.KEYCODE_MENU == keyCode ) {
			if (this.sat_nodes != null && this.sat_nodes.length > 0) {
				DVBSatelliteNode sat = this.sat_nodes[FocusID];
				if(sat == null) {
					return true;
				}
				//if(sat.istuner1valid()) {
				//	sat.settuner1(false);
				if(sat.isselect()) {
					sat.setselect(false);				
				}
				else {
					sat.settuner1(true);
					sat.setselect(true);				
				}
				
				DVBSatellite.updateSatellite(sat);
				
				for(int i = 0; i < this.sat_nodes.length; i++) {
					if(i == FocusID)
						continue;
					sat = this.sat_nodes[i];
					//sat.settuner1(false);
					sat.setselect(false);	
					DVBSatellite.updateSatellite(sat);
				}
				
				this.updateSats();
			}
			
			return true;
		}
		else if (KeyEvent.KEYCODE_ENTER == keyCode ||
				keyCode == KeyEvent.KEYCODE_DPAD_CENTER) {
			if (this.sat_nodes == null || this.sat_nodes.length == 0) {
				return true;
			}
			DVBSatelliteNode sat = this.sat_nodes[FocusID];
			
			if(sat == null) {
				return true;
			}
			
			Intent intent = new Intent(TVSatelliteList.this, TVTpList.class);
			
			//Bundle bundle = new Bundle();
			//bundle.putSerializable("satnodes", sat);
			intent.putExtra("fucos", FocusID);
			
			//intent.putExtras(bundle);

			this.startActivity(intent);
			
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
		
		this.updateSats();
	}
	
	private void changeFocus(int diff) {
    	if (this.sat_nodes != null && this.sat_nodes.length > 0) {
    		FocusID = FocusID+diff;
    		if(FocusID < 0) {
    			FocusID = this.sat_nodes.length - 1;
    		}
    		else if(FocusID == this.sat_nodes.length) {
    			FocusID = 0;
    		}
    	}
	}
}
