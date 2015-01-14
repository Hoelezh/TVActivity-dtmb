package com.alitech.dvb;

import java.io.UnsupportedEncodingException;

public class DvbUdrmInfo {
	public static class Email{
		byte[] content ;	// end with '\0'
		char readstatus; //  1: NOT READ 2: READ  other: 0: NOT USE
		byte[] title ;		// end with '\0'
		int utc;
		
		public Email() {
			super();
			// TODO Auto-generated constructor stub
		}
		public Email(byte[] content, char readstatus, byte[] title, int utc) {
			super();
			this.content = content;
			this.readstatus = readstatus;
			this.title = title;
			this.utc = utc;
		}
		public String Content()  
		{
 			String strcontend = null;
			try {
				strcontend = new String(content,"gb2312");
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return strcontend;			
		}
		public String Title()  
		{
			String strtitle  = null;
			try {
				strtitle = new String(title,"gb2312");
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
 			return strtitle;			
		}
		public char getReadstatus() {
			return readstatus;
		}
	 
		public int getUtc() {
			return utc;
		}
 
		
	}
	private int udrm_area_id;
	private int udrm_dev_sn;
	Email[] udrm_email;
	private int udrm_factory_id;
	private int udrm_loder_ver;
	private int udrm_model_id;
	private int udrm_operator_id;
	private int udrm_password;
	private int udrm_sw_ver;
	private String udrm_user_sn;
	private int udrm_WalletPoint;

	private int udrm_watch_class;

	public DvbUdrmInfo( ) {
		super();

	}
	public DvbUdrmInfo(String udrm_user_sn,  int udrm_dev_sn, int udrm_sw_ver,
			int udrm_factory_id, int udrm_model_id, int udrm_loder_ver,
			int udrm_operator_id, int udrm_area_id, int udrm_password,
			int udrm_watch_class,int udrm_WalletPoint) {
		super();
		this.udrm_user_sn = udrm_user_sn;
		this.udrm_dev_sn = udrm_dev_sn;
		this.udrm_sw_ver = udrm_sw_ver;
		this.udrm_factory_id = udrm_factory_id;
		this.udrm_model_id = udrm_model_id;
		this.udrm_loder_ver = udrm_loder_ver;
		this.udrm_operator_id = udrm_operator_id;
		this.udrm_area_id = udrm_area_id;
		this.udrm_password = udrm_password;
		this.udrm_watch_class = udrm_watch_class;
		this.udrm_WalletPoint = udrm_WalletPoint;
 
	}
	public int getUdrm_dev_sn() {
		return udrm_dev_sn;
	}
	public String getUdrm_user_sn() {
		return udrm_user_sn;
	}
	public int getUdrm_WalletPoint() {
		return udrm_WalletPoint;
	}
}
