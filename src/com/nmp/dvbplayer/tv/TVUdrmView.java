package com.nmp.dvbplayer.tv;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import android.content.res.Resources;
import android.provider.ContactsContract.CommonDataKinds.Email;
import android.text.format.DateFormat;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.alitech.dvb.DvbUdrm;
import com.alitech.dvb.DvbUdrmInfo;
import com.nmp.dvbplayer.R;



public class TVUdrmView extends TVWidget implements OnClickListener, OnItemClickListener {
	private static final int viewIndex_info = 0;
	private static final int viewIndex_emaillist = 1;
	private static final int viewIndex_ppclist = 2;
	private static final int viewIndex_setting = 3;
	private TVActivity mActivity;
	private ArrayList<View> mSelfView;
	private View   mInfoView;
	private View   mSettingView;
	private View   mPpcListView;
	private View   mEmailListView;

	private String TAG = "TVUdrmView";
	private TextView textView;
	private int viewIndex;
	private int level;
	private int level_pre;

	private Button EmailBtn;
	private Button LicenceBtn;	
	private Button SettingBtn;
	private Button saveButton;
	private Button cancelButton;
	private String udrm_password_old;
	private String udrm_password_new;
	private int level_size = 6;
	private EditText password_old_edit;
	private EditText password_new_edit;
	private DvbUdrmInfo dvbUdrmInfo;
	private com.alitech.dvb.DvbUdrmInfo.Email[] dvbUdrmEmail;
	private SimpleAdapter email_list_simpleAdapter;
	private ArrayList<Map<String, String>> emaillist;




	public TVUdrmView(TVActivity activity) {
		this.mActivity = activity;
		View view = activity.findViewById(R.id.tv_main);
		View.inflate(activity, R.layout.tv_udrm_info, (RelativeLayout)view);
		View.inflate(activity, R.layout.tv_udrm_sys_setting, (RelativeLayout)view);
		View.inflate(activity, R.layout.tv_udrm_ppc_list, (RelativeLayout)view);
		View.inflate(activity, R.layout.tv_udrm_email_list, (RelativeLayout)view);

		this.mInfoView = this.mActivity.findViewById(R.id.tv_udrm_info);
		this.mSettingView = this.mActivity.findViewById(R.id.tv_udrm_sys_setting);
		this.mPpcListView = this.mActivity.findViewById(R.id.tv_udrm_ppc_list);
		this.mEmailListView = this.mActivity.findViewById(R.id.tv_udrm_email_list);

		this.mInfoView.setVisibility(View.VISIBLE);
		this.mSettingView.setVisibility(View.GONE);
		this.mPpcListView.setVisibility(View.GONE);
		this.mEmailListView.setVisibility(View.GONE);
		mSelfView = new ArrayList<View>();
		mSelfView.add(mInfoView);
		mSelfView.add(mEmailListView);
		mSelfView.add(mPpcListView);
		mSelfView.add(mSettingView);		

		this.mActivity.dvbUdrm = new DvbUdrm();
		saveButton  = (Button) this.mActivity.findViewById( R.id.udrm_set_savebutton);
		cancelButton  = (Button) this.mActivity.findViewById( R.id.udrm_set_cancelbutton);
		saveButton.setOnClickListener(this);
		cancelButton.setOnClickListener(this);
		password_old_edit = (EditText) this.mActivity.findViewById( R.id.tv_udrm_old_pin);
		password_new_edit = (EditText) this.mActivity.findViewById( R.id.tv_udrm_new_pin);
		this.EmailBtn = (Button) this.mActivity.findViewById(R.id.Udrm_Email_Buttion);
		this.SettingBtn = (Button) this.mActivity.findViewById(R.id.Udrm_Setting_Buttion);
		this.LicenceBtn = (Button) this.mActivity.findViewById(R.id.Udrm_Licence_Buttion);
		this.EmailBtn.setOnClickListener(this);
		this.SettingBtn.setOnClickListener(this);
		this.LicenceBtn.setOnClickListener(this);


		this.hide();	
	}
	private void load_info() {
		dvbUdrmInfo = DvbUdrm.getUdrmInfo();

		textView = (TextView) this.mActivity.findViewById(R.id.tv_udrm_sn);
		textView.setText(""+dvbUdrmInfo.getUdrm_user_sn());
		textView = (TextView) this.mActivity.findViewById(R.id.tv_udrm_remain_money);
		textView.setText(""+dvbUdrmInfo.getUdrm_WalletPoint());
		textView = (TextView) this.mActivity.findViewById(R.id.tv_udrm_sw_version);
		textView.setText( ""+dvbUdrmInfo.getUdrm_dev_sn());	
	}
	private void load_email_list() {
		ListView listView = (ListView) this.mActivity.findViewById(R.id.email_listview);
		String[] from ={"id","info","date"};
		int[] to = {R.id.email_list_id,R.id.email_list_info,R.id.email_list_date};
		emaillist = new ArrayList<Map<String, String>>();
		email_list_uptade();

		email_list_simpleAdapter =  new SimpleAdapter(this.mActivity,emaillist, R.layout.email_list_item, from, to);
		listView.setAdapter(email_list_simpleAdapter);
		listView.setOnItemClickListener(this);
	}
	private void email_list_uptade() {
		emaillist.clear();
		dvbUdrmEmail =  this.mActivity.dvbUdrm.getUdrmEmailInfo();
		for (int i = 0; i <dvbUdrmEmail.length; i++) {
			if(dvbUdrmEmail[i].getReadstatus() !=0  )
			{
				Map<String, String> m = new HashMap<String, String>();
				m.put("id", "" + (i+1));
				m.put("info",""+dvbUdrmEmail[i].Content());
				m.put("date",  DateFormat.format("yyyy-MM-dd", dvbUdrmEmail[i].getUtc()).toString());
				emaillist.add(m);	
			}

		}
	}
	private void load_ppc_list() {
		ListView listView = (ListView) this.mActivity.findViewById(R.id.ppc_listview);
		String[] from ={"id","cont"};
		int[] to = {R.id.email_list_id,R.id.email_list_info,};
		List<Map<String, String>> ppclist = new ArrayList<Map<String, String>>();
		this.mActivity.dvbUdrm = new DvbUdrm();

		for (int i = 0; i < this.mActivity.dvbUdrm.getUdrmPpcNum(); i++) {
			Map<String, String> m = new HashMap<String, String>();
			m.put("id", "" + (i+1));
			m.put("cont",""+this.mActivity.dvbUdrm.getUdrmPpcId(i));
			ppclist.add(m);
		}

		SimpleAdapter  simpleAdapter = new SimpleAdapter(this.mActivity, ppclist, R.layout.email_list_item, from, to);
		listView.setAdapter(simpleAdapter);
		listView.setOnItemClickListener(this);
	}
	private void load_sys_setting() {
		level_pre = level = this.mActivity.dvbUdrm.getUdrmWatchClass();
		set_level_str();

	}
	private void set_level_str() {
		TextView textview = (TextView) this.mActivity.findViewById( R.id.tv_udrm_class_value);
		switch (level) {
		case 1:
			textview.setText(R.string.rs_watch_glass_u);
			break;
		case 2:
			textview.setText(R.string.rs_watch_glass_uc);
			break;
		case 3:
			textview.setText(R.string.rs_watch_glass_pg);
			break;
		case 4:
			textview.setText(R.string.rs_watch_glass_12);
			break;
		case 5:
			textview.setText(R.string.rs_watch_glass_15);
			break;
		case 6:
			textview.setText(R.string.rs_watch_glass_18);
			break;
		default:
			break;
		}		
	}
	private void changeLevel(int diff) {
		this.level += diff;
		if (this.level >= this.level_size) {
			this.level -= level_size;
		}
		if (this.level < 0) {
			this.level += level_size;
		}
		set_level_str();
	}
	@Override
	protected View getView() {
		return mSelfView.get(viewIndex);
	}

	@Override
	public boolean accept(int keyCode) {

		if (KeyEvent.KEYCODE_DPAD_DOWN == keyCode &&
				SettingBtn.isFocused()  ) {
			return false;
		}
		return true;
	}

	@Override
	public boolean onKeyDown(int keyCode) {
		switch (viewIndex) {
		case viewIndex_info:
			return onKeyDown_info(keyCode);	
		case viewIndex_emaillist:
			return onKeyDown_emaillist(keyCode);			
		case viewIndex_ppclist:
			return onKeyDown_ppclist(keyCode);	
		case viewIndex_setting:
			return onKeyDown_setting(keyCode);		
		default:
			return false;
		}
	}

	@Override
	public void focus(boolean f) {
		if(f)
		{

			SettingBtn.requestFocus();
		}
		else
		{
			SettingBtn.clearFocus();
			EmailBtn.clearFocus();
			LicenceBtn.clearFocus();
		}
	}
	public int getViewIndex() {
		return viewIndex;
	}
	public void setViewIndex(int Index) {
		this.hide();
		this.viewIndex = Index;
		mSelfView.get(viewIndex).setVisibility(View.VISIBLE);
	}
	@Override
	public void show() {
		// TODO Auto-generated method stub
		load_info();
		super.show();
	}
	
	@Override
	public void hide() {
		this.viewIndex = viewIndex_info;
		for (int i = 0; i <mSelfView.size(); i++) {
			if(View.VISIBLE == mSelfView.get(i).getVisibility())
				mSelfView.get(i).setVisibility(View.GONE);
		}		
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {


		case R.id.udrm_set_savebutton:
			udrm_password_old = password_old_edit.getText().toString();
			udrm_password_new = password_new_edit.getText().toString();
			if(udrm_password_old.isEmpty())
			{
				Toast.makeText(this.mActivity, "请输入旧的密码!", Toast.LENGTH_SHORT).show();  
				break;
			}
			if(true!=this.mActivity.dvbUdrm.checkUdrmPassword(udrm_password_old))
			{
				Toast.makeText(this.mActivity, "密码错误!", Toast.LENGTH_SHORT).show();  
				password_old_edit.setText("");
				break;				
			}	

			if( level_pre !=level  )
			{
				if(this.mActivity.dvbUdrm.setUdrmWatchClass(level, udrm_password_old))
					Toast.makeText(this.mActivity, "观看等级已修改!", Toast.LENGTH_SHORT).show();  
			}
			if( !udrm_password_new.isEmpty())
			{
				if( udrm_password_new.length() != 6  )
				{
					Toast.makeText(this.mActivity, "新的密码长度必须6位!", Toast.LENGTH_SHORT).show();  
					break;
				}else
					if (this.mActivity.dvbUdrm.setUdrmPassword(udrm_password_old, udrm_password_new)) {
						Toast.makeText(this.mActivity, "密码已修改!", Toast.LENGTH_SHORT).show();  
					}
			}

		case R.id.udrm_set_cancelbutton:	
			setViewIndex(viewIndex_info);
			SettingBtn.requestFocus();
			break;

		case R.id.Udrm_Email_Buttion:
			load_email_list();
			setViewIndex(viewIndex_emaillist);
			mSelfView.get(viewIndex).requestFocus();
			break;
		case R.id.Udrm_Licence_Buttion:
			load_ppc_list();
			setViewIndex(viewIndex_ppclist);
			mSelfView.get(viewIndex).requestFocus();
			break;		
		case R.id.Udrm_Setting_Buttion:
			load_sys_setting();
			password_old_edit.setText("");
			password_new_edit.setText("");
			setViewIndex(viewIndex_setting);	
			mSelfView.get(viewIndex).requestFocus();
			break;
		default:
			break;
		}

	}
	@Override
	public void onItemClick(AdapterView<?> arg0, View arg1, int arg2, long arg3) {
		if(email_list_simpleAdapter == arg0.getAdapter() )
		{
			this.mActivity.dvbUdrm.deleteUdrmEmail(arg2);
			email_list_uptade();
			email_list_simpleAdapter.notifyDataSetChanged();
			Toast.makeText(this.mActivity, "邮件已删除!", Toast.LENGTH_SHORT).show();  
			Log.d(TAG, "deleteUdrmEmail idx "+ arg2  );
		}
	}
	private boolean onKeyDown_emaillist(int keyCode) {
		if (KeyEvent.KEYCODE_MENU == keyCode){
			setViewIndex(viewIndex_info);
			EmailBtn.requestFocus();
			return false;
		}
		KeyEvent event = null;
		return this.getView().onKeyDown(keyCode, event);
	}
	private boolean onKeyDown_ppclist(int keyCode) {
		if (KeyEvent.KEYCODE_MENU == keyCode){
			setViewIndex(viewIndex_info);
			LicenceBtn.requestFocus();
			return false;
		}
		KeyEvent event = null;
		return this.getView().onKeyDown(keyCode, event);

	}
	private boolean onKeyDown_setting(int keyCode) {
		int focus_id = this.getView().getRootView().findFocus().getId();
		if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT && focus_id ==R.id.udrm_watch_class ){
			changeLevel(-1);
			return true;
		}
		if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT 	&& focus_id ==R.id.udrm_watch_class ){
			changeLevel(1);
			return true;
		}
		if (KeyEvent.KEYCODE_MENU == keyCode){
			setViewIndex(viewIndex_info);
			SettingBtn.requestFocus();
			return false;
		}	
		KeyEvent event = null;
		return this.getView().onKeyDown(keyCode, event);
	}
	private boolean onKeyDown_info(int keyCode) {
		if (KeyEvent.KEYCODE_MENU == keyCode)
			return true;

		KeyEvent event = null;
		return this.getView().onKeyDown(keyCode, event);
	}



}