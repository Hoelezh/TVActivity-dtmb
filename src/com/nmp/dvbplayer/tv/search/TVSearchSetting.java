package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.alitech.dvb.DvbSystem;
import com.nmp.dvbplayer.R;


import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Pair;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.View.OnKeyListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TabHost;
import android.widget.TabHost.OnTabChangeListener;
import android.widget.TabHost.TabContentFactory;
import android.widget.TabHost.TabSpec;
import android.widget.TextView;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.content.res.Resources;

public class TVSearchSetting extends Activity implements TabContentFactory {	

	final static int BOARD_NULL = 0;
	final static int BOARD_DVBC = 1;
	final static int BOARD_DTMB = 2;
	final static int BOARD_DVBS2 = 3;
	final static int BY_DETECT = 4;
	
	private static final String Tab1 = "auto";
	private static final String Tab2 = "manual";
	//private static final String Tab3 = "full";
	private static String Tab3;// = "singleSatSearch";
	private static final int    ReqCode = 1;
	private DVBSatelliteNode[] sat_nodes;
	private ArrayList<DVBSatelliteNode> mSatLists;
	
	private static class MySimpleAdapter extends SimpleAdapter {
		private boolean mEditMode;
		private int     mIndex;
		private TVParam mParam;
		public MySimpleAdapter(Context context,
				List<? extends Map<String, ?>> data, int resource,
				String[] from, int[] to) {
			super(context, data, resource, from, to);
		}
		
		public void setEditMode(boolean edit) {
			this.mEditMode = edit;
		}
		
		public void setCurrentIndex(int index) {
			this.mIndex = index;
		}
		
		public void setParam(TVParam param) {
			this.mParam = param;
		}
		
		@Override
		public View getView (int position, View convertView, ViewGroup parent) {
			View view =  super.getView(position, convertView, parent);
			if (position == this.mIndex && this.mEditMode &&
					TVParam.ParamType.Number == this.mParam.getType()) {
				view.findViewById(R.id.val_picker).setVisibility(View.VISIBLE);
				view.findViewById(R.id.value_field).setVisibility(View.GONE);
			} else {
				view.findViewById(R.id.val_picker).setVisibility(View.GONE);
				view.findViewById(R.id.value_field).setVisibility(View.VISIBLE);
			}
			return view;
		}
		
	};
	
	private HashMap<String, ArrayList<HashMap<String, Object>>> mData;
	private HashMap<String, MySimpleAdapter> mAdapters;
	private HashMap<String, ListView> mListViews;
	private HashMap<String, TVSearch> mParams;
	private Button                    mButton;
	private TabHost                   mTabHost;
	private boolean                   mEditMode;
	private int   				 FocusID = 0;

	private int dvbType;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tv_search_setting);
		
		DvbSystem.PanelShow("SECH", 4);

		this.dvbType = DvbSystem.getboardType();
		if(this.dvbType != BOARD_DTMB && this.dvbType != BOARD_DVBS2)
			this.dvbType = BOARD_DVBC;
		

		if(this.dvbType == BOARD_DVBS2)
		{
			Tab3 = "singleSatSearch";
		}
		else
		{
			Tab3 = "full";
		}
		
		this.mEditMode = false;
		this.mTabHost = (TabHost)findViewById(R.id.tv_search_tab);
		this.mTabHost.setup();		
		this.mData = new HashMap<String, ArrayList<HashMap<String, Object>>>();
		this.mAdapters = new HashMap<String, MySimpleAdapter>();
		this.mListViews = new HashMap<String, ListView>();
		this.mParams = new HashMap<String, TVSearch>();
		
		this.mData.put(Tab1, new ArrayList<HashMap<String, Object>>());
		this.mData.put(Tab2, new ArrayList<HashMap<String, Object>>());
		this.mData.put(Tab3, new ArrayList<HashMap<String, Object>>());
		//this.mData.put(Tab4, new ArrayList<HashMap<String, Object>>());
		if(this.dvbType == BOARD_DVBS2){
			this.mParams.put(Tab1, new TVAutoSearch_S(this));
			this.mParams.put(Tab2, new TVManualSearch_S(this));
//		this.mParams.put(Tab3, new TVFullSearch(this));
			this.mParams.put(Tab3, new TVSingleSatSearch(this));
		}
		else {
			this.mParams.put(Tab1, new TVAutoSearch(this));
			this.mParams.put(Tab2, new TVManualSearch(this));
			this.mParams.put(Tab3, new TVFullSearch(this));	
		}
		FocusID = 0;
		//Resources res = this.getResources();
		Resources res = this.getBaseContext().getResources();  
		Configuration config = res.getConfiguration();  
		Locale locale = null;
		config.locale = locale;  
		DisplayMetrics dm = res.getDisplayMetrics();  
		res.updateConfiguration(config, dm);
		LayoutInflater inflater = LayoutInflater.from(this);
		
		View tabView = inflater.inflate(R.layout.tv_search_tab_item, null);
		TextView tabText = (TextView)tabView.findViewById(R.id.tabtext);
		tabText.setText(res.getString(R.string.tv_search_auto));
		TabSpec tabSpec = this.mTabHost.newTabSpec(Tab1);
		tabSpec.setIndicator(tabView).setContent(this);
		this.mTabHost.addTab(tabSpec);		
		
		tabView = inflater.inflate(R.layout.tv_search_tab_item, null);
		tabText = (TextView)tabView.findViewById(R.id.tabtext);
		tabText.setText(res.getString(R.string.tv_search_manual));
		tabSpec = this.mTabHost.newTabSpec(Tab2);
		tabSpec.setIndicator(tabView).setContent(this);
		this.mTabHost.addTab(tabSpec);
		
		tabView = inflater.inflate(R.layout.tv_search_tab_item, null);
		tabText = (TextView)tabView.findViewById(R.id.tabtext);
		if(this.dvbType == BOARD_DVBS2){
			tabText.setText(res.getString(R.string.tv_search_singleSatSearch));
		}
		else {
			tabText.setText(res.getString(R.string.tv_search_full));
		}
		tabSpec = this.mTabHost.newTabSpec(Tab3);
		tabSpec.setIndicator(tabView).setContent(this);
		this.mTabHost.addTab(tabSpec);
		
		this.mTabHost.setOnTabChangedListener(new OnTabChangeListener(){
			@Override
			public void onTabChanged(String arg0) {
				clearTabBgExcept(mTabHost.getCurrentTab());
				mTabHost.getTabWidget().requestFocus();
			}
		});
		this.mTabHost.getTabWidget().setOnFocusChangeListener(
		new OnFocusChangeListener(){
			@Override
			public void onFocusChange(View v, boolean hasFocus) {
				int idx = hasFocus ? mTabHost.getCurrentTab() : - 1;
				clearTabBgExcept(idx);
			}
		});
		this.mTabHost.getTabWidget().setOnKeyListener(new OnKeyListener(){
			@Override
			public boolean onKey(View arg0, int keyCode, KeyEvent event) {
				if (KeyEvent.ACTION_DOWN == event.getAction()) {
					if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode ||
							KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
						int count = mTabHost.getTabWidget().getChildCount();
						int cur = mTabHost.getCurrentTab();
						if (KeyEvent.KEYCODE_DPAD_LEFT == keyCode &&
								cur > 0) {
							cur -= 1;
						}
						if (KeyEvent.KEYCODE_DPAD_RIGHT == keyCode &&
								cur < count - 1) {
							cur += 1;
						}
						mTabHost.setCurrentTab(cur);
						return true;
					}
				}
				return false;
			}			
		});
		clearTabBgExcept(FocusID);//first in search wig have focus of auto
		this.mButton = (Button)this.mTabHost.findViewById(R.id.tv_search_btn);
		this.mButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				Context ctx = TVSearchSetting.this;
				Intent intent = new Intent(ctx, TVSearchProgress.class);
				TVSearch search = mParams.get(mTabHost.getCurrentTabTag());
				intent.putExtra("param", search.getSearchParams().toString());
				startActivityForResult(intent, ReqCode);
			}
		});
	}
	
	@Override
    protected void onStart() {
		super.onStart();
		//this.mButton.requestFocus();
	}
	
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (ReqCode == requestCode && resultCode == Activity.RESULT_OK) {
			int result = data.getIntExtra("result", 0);
			if (result > 0) {
				setResult(RESULT_OK, data);
				finish();
			}
		}
		if(this.dvbType == BOARD_DVBS2){
		if( this.FocusID == 0 )
		{
			DVBSatelliteNode sNode;
			int j;
			this.sat_nodes = DVBSatellite.loadSatelliteNodes();
			if(this.sat_nodes == null || this.sat_nodes.length == 0) {
				return;
			}
			this.mSatLists = new ArrayList<DVBSatelliteNode>();
			for (j = 0; j< this.sat_nodes.length;j++) {
				sNode = this.sat_nodes[j];
				if(sNode.isselect()) {
					mSatLists.add(sNode);
					break;
				}
			}
			int sat_count;
			sat_count = this.mSatLists.size();
			if(sat_count == 0 && this.sat_nodes.length > 0) {
				sNode = this.sat_nodes[0];
				mSatLists.add(sNode);
				sat_count = this.mSatLists.size();
				sNode.setselect(true);
				sNode.settuner1(true);
				DVBSatellite.updateSatellite(sNode);
			}
			String tag;
			TVSearch search;
			TVStringParam strParam;
			TVParam param;
			int count = mTabHost.getTabWidget().getChildCount();
			int cur = mTabHost.getCurrentTab();
			for(int i=0;i<count;i++)
			{
				mTabHost.setCurrentTab(i);
				tag = this.mTabHost.getCurrentTabTag();
				search = this.mParams.get(tag);
				param = search.getCurrentParam();
				strParam = (TVStringParam)param;
				strParam.clearValue();
				strParam.addValue(this.mSatLists.get(0).getName());
				updateListView(tag);
			}
			mTabHost.setCurrentTab(cur);
			{
				{
				}
			}
		}
		}
	}
	
	private void clearTabBgExcept(int idx) {
		int count = this.mTabHost.getTabWidget().getChildCount();
		for (int i = 0; i < count; ++i) {
			View v = this.mTabHost.getTabWidget().getChildAt(i);			
			if (i == idx) {
				v.setBackgroundResource(R.drawable.tv_search_tab_focus);
			} else {
				v.setBackgroundResource(0);
			}
		}
	}
	
	@Override
	public View createTabContent(String tag) {
		LayoutInflater inflater = LayoutInflater.from(this);
		int layoutId = R.layout.tv_search_list;		
		ArrayList<HashMap<String, Object>> data = this.mData.get(tag);
		View view = inflater.inflate(layoutId, null);
		ListView listView = (ListView) view.findViewById(R.id.tv_search_list);
		
		MySimpleAdapter adapter = new MySimpleAdapter(
			this,
			data,
			R.layout.tv_search_list_item,
			new String[] { "field" , "value" },
			new int[] { R.id.text_field, R.id.value_field }
		);
		listView.setAdapter(adapter);
		this.mAdapters.put(tag, adapter);
		this.mListViews.put(tag, listView);
		listView.setOnKeyListener(new OnKeyListener(){
			@Override
			public boolean onKey(View view, int keyCode, KeyEvent event) {
				return listViewKeyEvent(keyCode, event);
			}
		});
		this.updateListView(tag);
		
		return view;
	}
	
	private boolean listViewKeyEvent(int keyCode, KeyEvent event) {
		boolean result = false;
		
		if (event.getAction() != KeyEvent.ACTION_DOWN) {
			return result;
		}
		
		String tag = this.mTabHost.getCurrentTabTag();
		ListView listView = this.mListViews.get(tag);
		TVSearch search = this.mParams.get(tag);
		int selectedIndex = listView.getSelectedItemPosition();
		
		if (selectedIndex < 0) {
			return result;
		}
		
		search.setIndex(selectedIndex);
		TVParam param = search.getCurrentParam();		
		
		if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT ||
				keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
			handleLeftRight(keyCode, event);
			result = true;
		}		
		
		if (keyCode == KeyEvent.KEYCODE_DPAD_UP ||
				keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
			if (mEditMode && TVParam.ParamType.Number == param.getType()) {
				handleLeftRight(keyCode, event);
				result = true;
			}
			if(this.dvbType == BOARD_DVBS2){
				if(!mEditMode)
				{
					if( keyCode == KeyEvent.KEYCODE_DPAD_UP )
					{
						if( this.FocusID>0 )
							this.FocusID-=1;
					}		
					else if( keyCode == KeyEvent.KEYCODE_DPAD_DOWN )
					{
						if( this.FocusID<(this.mParams.size()-1) )
							this.FocusID+=1;
					}
				}
			}
			
		}		
		
		if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||
				keyCode == KeyEvent.KEYCODE_ENTER ||
				keyCode == KeyEvent.KEYCODE_ESCAPE ||
				keyCode == KeyEvent.KEYCODE_BACK) 
		{
			if (mEditMode) 
			{
				mEditMode = false;
				updateListView(mTabHost.getCurrentTabTag());
				result = true;
			} 
			else if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER ||
			keyCode == KeyEvent.KEYCODE_ENTER) 
			{
				if (TVParam.ParamType.Number == param.getType()) 
				{
					mEditMode = true;
					TVNumPicker picker = this.getCurrentNumPicker();
					picker.setParam((TVNumberParam)param);
					updateListView(mTabHost.getCurrentTabTag());
					result = true;
				}
				else if( this.FocusID == 0 && this.dvbType == BOARD_DVBS2)
				{
					Intent intent = new Intent(this, TVSatelliteList.class);
					startActivityForResult(intent, ReqCode);
				}
			}
		}
		
		if (keyCode >= KeyEvent.KEYCODE_0 && keyCode <= KeyEvent.KEYCODE_9) {
			TVNumPicker picker = this.getCurrentNumPicker();
			if (this.mEditMode) {				
				picker.onKeyDown(keyCode, event);
				result = true;
			} else if (TVParam.ParamType.Number == param.getType()) {
				mEditMode = true;
				picker.setParam((TVNumberParam)param);
				picker.onKeyDown(keyCode, event);
				updateListView(mTabHost.getCurrentTabTag());
				result = true;
			}
		}
		
		return result;
	}
	
	private void handleLeftRight(int keyCode, KeyEvent event) {
		String tag = this.mTabHost.getCurrentTabTag();
		TVSearch search = this.mParams.get(tag);
		TVParam param = search.getCurrentParam();
		
		if (TVParam.ParamType.Number == param.getType()) {
			TVNumPicker picker = this.getCurrentNumPicker();
			if (this.mEditMode) {
				picker.onKeyDown(keyCode, event);
			} else {
				this.mEditMode = true;
				picker.setParam((TVNumberParam)param);
			}
		} else {
			this.mEditMode = false;
			TVStringParam strParam = (TVStringParam)param;
			int dir = 0;
			if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT) {
				dir = -1;
			} else if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
				dir = 1;
			}
			strParam.changeIdx(dir);
		}
		updateListView(tag);
	}
	
	private TVNumPicker getCurrentNumPicker() {
		String tag = this.mTabHost.getCurrentTabTag();
		ListView listView = this.mListViews.get(tag);
		View view = listView.getSelectedView();
		TVNumPicker picker = null;
		if (view != null) {
			picker = (TVNumPicker) view.findViewById(R.id.val_picker);
		}
		return picker;
	}
	
	private void updateListView(String tag) {
		MySimpleAdapter adapter = this.mAdapters.get(tag);
		ListView lstView = this.mListViews.get(tag);
		TVSearch search = this.mParams.get(tag);
		
		adapter.setEditMode(this.mEditMode);
		adapter.setCurrentIndex(lstView.getSelectedItemPosition());
		adapter.setParam(search.getCurrentParam());
		
		ArrayList<HashMap<String, Object>> data = this.mData.get(tag);
		data.clear();
		
		ArrayList<Pair<String, String>> values = search.getDataList();
		if (null == values || values.size() < 1) {			
			adapter.notifyDataSetChanged();
			return;
		}
		
		for (Pair<String, String> pair : values) {
			HashMap<String, Object> map = new HashMap<String, Object>();
			map.put("field", pair.first);
			map.put("value", pair.second);
			data.add(map);
		}		
		adapter.notifyDataSetChanged();
		
		int resId = R.drawable.tv_search_list_item_bg;
		if (this.mEditMode) {
			resId = R.drawable.tv_search_empty;
		}
		lstView.setSelector(resId);
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		boolean keyHandled = false;
		if (keyCode == KeyEvent.KEYCODE_MUTE ||
				keyCode == KeyEvent.KEYCODE_VOLUME_UP ||
				keyCode == KeyEvent.KEYCODE_VOLUME_DOWN ||
				keyCode == KeyEvent.KEYCODE_VOLUME_MUTE) {
			keyHandled = true;
		}
		else if(keyCode == KeyEvent.KEYCODE_F11 && this.dvbType == BOARD_DVBS2) {
			Intent intent = new Intent(this, TVSatelliteList.class);
			//this.startActivity(intent);
			startActivityForResult(intent, ReqCode);
			keyHandled = true;
		}
		
		if(keyHandled == false)
			keyHandled = super.onKeyDown(keyCode, event);
		
		return keyHandled;
	}
}
