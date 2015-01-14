package com.nmp.dvbplayer.tv.search;

import java.util.ArrayList;

import com.alitech.dvb.DVBSatellite;
import com.alitech.dvb.DVBSatelliteNode;
import com.alitech.dvb.DvbTpNode;
import com.nmp.dvbplayer.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;

public class TVSatelliteEdit extends Activity {
	
	private boolean is_edit;
	private int edit_type;// 1:sat edit, 2:sat add, 3:tp edit, 4:tp add 5:sat delete 6:tp delete
	
	private ArrayList<View> mEditLists;
	private int item_count;
	private int focus;
	private int tp_id_del;
	private int sat_id_del;
	
	private DVBSatelliteNode sat_node;
	private DvbTpNode tp_node;
	
	TVNumberParam mparam;
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.tv_satellite_edit);
		
		Intent intent = this.getIntent();
		this.edit_type = intent.getIntExtra("type", 0);
		LinearLayout lLayout = null;
		if(edit_type <= 4) {
			int rid = R.id.tv_satellite_edit_items;
			lLayout = (LinearLayout)this.findViewById(rid);
			this.mEditLists = new ArrayList<View>();
			TextView textView = (TextView)this.findViewById(R.id.tv_satellite_edit_content);
			textView.setVisibility(View.GONE);
		}
		TextView txtTitle = (TextView)this.findViewById(R.id.tv_satellite_edit_title);
		
		if(edit_type == 2 || edit_type == 1) {
			if(edit_type == 1) {
				txtTitle.setText(R.string.tv_satellite_edit);
				this.sat_node = (DVBSatelliteNode)intent.getSerializableExtra("satnode");
				//View.inflate(this, R.layout.tv_search_list_item, lLayout);
				//View.inflate(this, R.layout.tv_search_list_item, lLayout);
			}
			else if(edit_type == 2) {
				txtTitle.setText(R.string.tv_satellite_add);
				this.sat_node = new DVBSatelliteNode();
				//View.inflate(this, R.layout.tv_satellite_name, lLayout);
				//View.inflate(this, R.layout.tv_search_list_item, lLayout);
			}
			View.inflate(this, R.layout.tv_satellite_name, lLayout);
			View.inflate(this, R.layout.tv_search_list_item, lLayout);
		}
		else if(edit_type == 4 || edit_type == 3) {
			if(edit_type == 3) {
				txtTitle.setText(R.string.tv_tp_edit);
				this.tp_node = (DvbTpNode)intent.getSerializableExtra("tpnode");
			}
			else if(edit_type == 4) {
				txtTitle.setText(R.string.tv_tp_add);
				int snode_id = (int)intent.getIntExtra("snode_id", 1);
				this.tp_node = new DvbTpNode(snode_id);
			}
			View.inflate(this, R.layout.tv_search_list_item, lLayout);
			View.inflate(this, R.layout.tv_search_list_item, lLayout);
			View.inflate(this, R.layout.tv_search_list_item, lLayout);
			
		}
		else if(edit_type == 5) {
			this.sat_id_del = (int)intent.getIntExtra("snode_id", 0);
			txtTitle.setText(R.string.tv_satellite_delete);
			TextView textView = (TextView)this.findViewById(R.id.tv_satellite_edit_content);
			textView.setVisibility(View.VISIBLE);
			textView.setText(R.string.tv_info_delete_snode);
			this.findViewById(R.id.tv_satellite_edit_items).setVisibility(View.GONE);
			
			TextView button2 = (TextView)this.findViewById(R.id.tv_satellite_edit_help2);
			
			button2.setBackgroundResource(R.drawable.tv_list_item_focus);
			
			
			
			
		}
		else if(edit_type == 6) {
			this.tp_id_del = (int)intent.getIntExtra("tp_id", 0);
			this.sat_id_del = (int)intent.getIntExtra("sat_id", 0);
			
			txtTitle.setText(R.string.tv_tp_delete);
			TextView textView = (TextView)this.findViewById(R.id.tv_satellite_edit_content);
			textView.setVisibility(View.VISIBLE);
			textView.setText(R.string.tv_info_delete_tp);
			this.findViewById(R.id.tv_satellite_edit_items).setVisibility(View.GONE);
		}
		
		if(lLayout != null)
			item_count = lLayout.getChildCount();

		for (int i = 0; i < item_count; ++i) {
			this.mEditLists.add(lLayout.getChildAt(i));
		}	
		
		is_edit = false;
		//focus = 0;
		focus = item_count + 1;
	}
	
	@Override
	protected void onStart() {
		super.onStart();
		
		for(int i = 0; i < item_count; i++) {
			updateView(false, i);
		}
		
		if(edit_type ==2 || edit_type == 1 ) {
			initSatParam();
		}
		else if(edit_type == 4 || edit_type == 3) {
			initTpParam();
		}

	}
	
	private void updateView(boolean is_edit, int index) {
		int rid = R.id.tv_satellite_edit_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);
		View view = lLayout.getChildAt(index);
		
		if(edit_type <= 2 && index == 0) {
			//value_view = (TextView) view.findViewById(R.id.name_field);
		}
		else {
			if(is_edit == false) {
				view.findViewById(R.id.val_picker).setVisibility(View.GONE);
				view.findViewById(R.id.value_field).setVisibility(View.VISIBLE);
			}
			else {
				view.findViewById(R.id.val_picker).setVisibility(View.VISIBLE);
				view.findViewById(R.id.value_field).setVisibility(View.GONE);
			}			
		}

		if(index == focus) {
			view.setBackgroundResource(R.drawable.tv_search_list_focus);
		}
		else {
			view.setBackgroundResource(0);
		}
			
	}
	
	private void initSatParam() {
		LinearLayout lLayout = (LinearLayout)this.findViewById(R.id.tv_satellite_edit_items);
		View view = lLayout.getChildAt(0);
		TextView txt;
		
		txt = (TextView)view.findViewById(R.id.name_title);
		txt.setText(R.string.tv_satellite_name);
		
		if(edit_type == 2) {
			//txt = (TextView)view.findViewById(R.id.name_title);
			//txt.setText(R.string.tv_satellite_name);
		}
		else {
			//txt = (TextView)view.findViewById(R.id.text_field);
			//txt.setText(R.string.tv_satellite_name);
			txt = (TextView)view.findViewById(R.id.name_field);
			txt.setText(sat_node.getName());
		}
		
		
		view = lLayout.getChildAt(1);
		txt = (TextView)view.findViewById(R.id.text_field);
		txt.setText(R.string.tv_satellite_longitude);
		
		txt = (TextView)view.findViewById(R.id.value_field);

		int orbit = sat_node.getorbit();
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
			txt.setText(String.valueOf(forbit) + " E");
		}
		else {
			txt.setText(String.valueOf(forbit) + " W");
		}		
	}
	
	private void initTpParam() {
		
		LinearLayout lLayout = (LinearLayout)this.findViewById(R.id.tv_satellite_edit_items);
		View view = lLayout.getChildAt(0);
		TextView txt;
		txt = (TextView)view.findViewById(R.id.text_field);
		txt.setText(R.string.tv_search_freq);
		txt = (TextView)view.findViewById(R.id.value_field);
		txt.setText(String.valueOf(tp_node.getFreq()) + " MHz");
		
		view = lLayout.getChildAt(1);
		txt = (TextView)view.findViewById(R.id.text_field);
		txt.setText(R.string.tv_search_sym);
		
		txt = (TextView)view.findViewById(R.id.value_field);
		txt.setText(String.valueOf(tp_node.getSymbol()) + " Ks/s");
		
		view = lLayout.getChildAt(2);
		txt = (TextView)view.findViewById(R.id.text_field);
		txt.setText(R.string.tv_tp_polarity);
		
		txt = (TextView)view.findViewById(R.id.value_field);

		int orbit = tp_node.getPol();
		
		if(orbit == 0) {
			txt.setText("H");
		}
		else {
			txt.setText("V");
		}		
	}
	
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		boolean keyHandled = false;
		
		if (KeyEvent.KEYCODE_ENTER == keyCode ||
				keyCode == KeyEvent.KEYCODE_DPAD_CENTER) {
			if(is_edit) {
				is_edit = false;
				TextView txtTextView = getCurrentValueText(focus);
				txtTextView.setText(mparam.getDisplayValue());	
						
				updateView(is_edit, focus);
			}
			else if(focus == item_count ) {
				int value_int;
				if(edit_type == 2 || edit_type == 1) {
					TextView txt = getCurrentValueText(0);
					float orbat;
					
					sat_node.setName(txt.getText().toString());
					
					mparam = getCurrentValueParam(1);
					orbat = mparam.getValue();
					if(mparam.getUnit().equals("E")) {
						value_int = (int)orbat*10;
						sat_node.setorbit(value_int);
					}
					else {
						value_int = (int)(3600 - orbat*10);
						sat_node.setorbit(value_int);
					}
					DVBSatellite.updateSatellite(sat_node);
				}
				else if(edit_type == 3 || edit_type == 4) {
					mparam = getCurrentValueParam(0);
					value_int = (int)mparam.getValue();
					tp_node.setFreq(value_int);
					
					mparam = getCurrentValueParam(1);
					value_int = (int)mparam.getValue();
					tp_node.setSymbol(value_int);
					
					String pol = (String)getCurrentValueText(2).getText();
				
					if(pol.equals("H")) {
						tp_node.setPol(0);
					}
					else {
						tp_node.setPol(1);
					}
					DVBSatellite.updateTpNode(tp_node);
				}
				else if(edit_type == 5) {
					DVBSatellite.deleteSatellite(this.sat_id_del);
				}
				else if(edit_type == 6) {
					DVBSatellite.deleteTpNode(this.sat_id_del, this.tp_id_del);
				}
				this.finish();
			}
			else if(focus == item_count+1) {
				this.finish();
			}
			return true;
		}
		else if(KeyEvent.KEYCODE_DPAD_UP == keyCode ||
				KeyEvent.KEYCODE_DPAD_DOWN == keyCode ) {
			//修改以符合用户习惯
			onPressLeftRight(keyCode, event);
			return true;
		}
		else if(KeyEvent.KEYCODE_DPAD_LEFT == keyCode ||
				KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
			//修改以符合用户习惯
			onPressUpDown(keyCode, event);
			return true;
		}
		else if(keyCode >= KeyEvent.KEYCODE_0 && keyCode <= KeyEvent.KEYCODE_9) {
			if(((edit_type == 2 || edit_type == 1) && focus == 1) || 
					((edit_type == 4 || edit_type == 3) && focus < item_count -1)) {
				TVNumPicker picker = this.getCurrentNumPicker();
				if (is_edit) {				
					picker.onKeyDown(keyCode, event);
					return true;
				} 
				else {

					is_edit = true;
					mparam = getCurrentValueParam(focus);
					picker.setParam(mparam);
					picker.onKeyDown(keyCode, event);
					updateView(is_edit, focus);
					return true;
				}
			}
			return true;
		}
		
		keyHandled = super.onKeyDown(keyCode, event);
		
		return keyHandled;
	}
	
	private void changefucos(int diff) {
		focus = focus + diff;
		if(focus < 0) {
			if(item_count == 0)
				focus = 1;
			else
				focus = item_count - 1;
		}
		else if(focus == item_count + 2) {
			focus = 0;
		}
		
		if(edit_type <= 2 && focus != 0) {
			LinearLayout lLayout = (LinearLayout)this.findViewById(R.id.tv_satellite_edit_items);
			View view = lLayout.getChildAt(0);
			EditText txt;
			
			txt = (EditText)view.findViewById(R.id.name_field);
			txt.clearFocus();
			txt.setFocusable(false);
		}
		else if(edit_type <= 2 && focus == 0) {
			LinearLayout lLayout = (LinearLayout)this.findViewById(R.id.tv_satellite_edit_items);
			View view = lLayout.getChildAt(0);
			EditText txt;
			
			txt = (EditText)view.findViewById(R.id.name_field);
			txt.setFocusable(true);
			txt.requestFocus();
		}
	}
	
	//8.11.issue25517。改成左右键，以符合用户习惯，函数名暂时不改
	private void onPressUpDown(int keyCode, KeyEvent event){
		if(is_edit == false) {
			if(KeyEvent.KEYCODE_DPAD_LEFT == keyCode) {
				changefucos(-1);
			}
			else if(KeyEvent.KEYCODE_DPAD_RIGHT == keyCode) {
				changefucos(1);
			}
			updateAllView();
		}
		else {
			TVNumPicker picker = this.getCurrentNumPicker();
			picker.onKeyDown(keyCode, event);
		}
	}
	
	private void onPressLeftRight(int keyCode, KeyEvent event) {
		if(is_edit) {
			TVNumPicker picker = this.getCurrentNumPicker();
			picker.onKeyDown(keyCode, event);
		}
		else {
			if(focus == 1 && (edit_type == 2 || edit_type == 1)) {
				TextView txtTextView = getCurrentValueText(focus);
				String valueString = (String) txtTextView.getText();
				String[] arr = valueString.split(" ");
				if(arr[1].equals("E")) {
					txtTextView.setText(arr[0]+" W");
				}
				else {
					txtTextView.setText(arr[0]+" E");
				}
				updateView(is_edit, focus);
			}
			else if(focus == 2 && (edit_type == 3 || edit_type == 4)) {
				TextView txtTextView = getCurrentValueText(focus);
				String valueString = (String) txtTextView.getText();

				if(valueString.equals("H")) {
					txtTextView.setText("V");
				}
				else {
					txtTextView.setText("H");
				}
				updateView(is_edit, focus);
			}
		}
	}
	
	private void updateAllView() {
		
		for(int i = 0; i < item_count; i++) {
			updateView(is_edit, i);
		}
		
		TextView button1 = (TextView)this.findViewById(R.id.tv_satellite_edit_help1);
		TextView button2 = (TextView)this.findViewById(R.id.tv_satellite_edit_help2);
		
		button1.setBackgroundResource(0);
		button2.setBackgroundResource(0);
		if(focus == item_count) {
			button1.setBackgroundResource(R.drawable.tv_list_item_focus);
		}
		else if(focus == item_count+1) {
			button2.setBackgroundResource(R.drawable.tv_list_item_focus);
		}
			
	}
	
	private TVNumPicker getCurrentNumPicker() {
		int rid = R.id.tv_satellite_edit_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);

		View view = lLayout.getChildAt(focus);
		
		TVNumPicker picker = null;
		if (view != null) {
			picker = (TVNumPicker) view.findViewById(R.id.val_picker);
		}
		return picker;
	}
	
	private TVNumberParam getCurrentValueParam(int index) {

		TVNumberParam param; 
		TextView value_view = null;
		
		value_view = getCurrentValueText(index);
		if(value_view == null)
			return null;

		String valueString = (String) value_view.getText();
		String[] arr = valueString.split(" ");
		
		Float value = Float.valueOf(arr[0]);
		String unit = arr[1];
		param = new TVNumberParam(String.valueOf(index), arr[0]);
		
		param.setIntegerBits(5);
		
		param.setUnit(unit);
		param.setValue(value);
		
		return param;
	}
	
	private TextView getCurrentValueText(int index) {
		int rid = R.id.tv_satellite_edit_items;
		LinearLayout lLayout = (LinearLayout)this.findViewById(rid);

		View view = lLayout.getChildAt(index);
		
		TextView value_view = null;
		if (view == null) {
			return null;
		}
		
		if(edit_type <= 2 && index == 0) {
			value_view = (TextView) view.findViewById(R.id.name_field);
		}
		else
			value_view = (TextView) view.findViewById(R.id.value_field);

		return value_view;
	}
	
}
