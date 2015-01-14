package com.alitech.dvb;


 
import com.alitech.dvb.DvbUdrmInfo.Email;

import android.os.Handler;
import android.os.Message;
import android.text.format.DateFormat;
import android.util.Log;

public class DvbUdrm {
	private static final String TAG = "DvbUdrm";

	public DvbUdrm() {
		// TODO Auto-generated constructor stub
	}
	
	public native  int getUdrmPpcNum() ;
	public native  int getUdrmPpcId(int index) ;
	public native boolean setUdrmWatchClass(int udrm_watch_class,String password);
	public native int getUdrmWatchClass( );
	public native boolean setUdrmPassword(String udrm_password_old,String udrm_password_new);
	public native boolean checkUdrmPassword(String udrm_password);

	
	public native static DvbUdrmInfo getUdrmInfo();
 	public static Handler h = null;
	public native  Email[] getUdrmEmailInfo() ;
	public native  boolean	 deleteUdrmEmail(int index) ;

	public void set_handler(Handler mhandler)
	{
		h = mhandler;
	}
	
	public static void  callback(int msg_type, int msg_code ,int utc,byte[] title,byte[] contend) throws Throwable
	{
		String strtime = DateFormat.format("yyyy-MM-dd", utc).toString();
		String strtitle = new String(title,"gb2312");
		String strcontent = new String(contend,"gb2312");
		Log.d(TAG, ""+  msg_type+" "+ msg_code +" "   +" " +strtime +" ");

		String[] msg_cont = {strtime,strtime,strcontent};
		if(null != h)
		{
			Message msg = new Message();
	        msg.what = msg_type+128;
 	        msg.arg1 = msg_code;
 	        msg.obj = msg_cont;
	        h.sendMessage(msg);
		}
	}
	
	static {
		
		System.loadLibrary("dvbagent");
	}

}
