package com.nmp.dvbplayer.tv;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Calendar;
import java.util.Locale;
import java.util.regex.Pattern;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.client.params.HttpClientParams;
import org.apache.http.entity.ByteArrayEntity;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import android.support.v4.util.LruCache;

public class TVUtility {
	/**
	 * 发送HTTP请求，如果data不为null,使用POST的方式，否则使用GET的方式
	 */
	public static byte[] httpRequest(String url, byte[] data) {
		HttpParams httpParams = new BasicHttpParams();
		HttpClientParams.setRedirecting(httpParams, true);
		HttpConnectionParams.setConnectionTimeout(httpParams, 30 * 1000);  
        HttpConnectionParams.setSoTimeout(httpParams, 30 * 1000);  
        HttpConnectionParams.setSocketBufferSize(httpParams, 8192);
		HttpClient httpClient = new DefaultHttpClient(httpParams);
		HttpUriRequest request;
		int maxRedirect = 5;
		int currentRedirect = 0;
		while (currentRedirect < maxRedirect) {
			++currentRedirect;
			if (data != null) {
				HttpPost postRequest = new HttpPost(url);
				postRequest.setEntity(new ByteArrayEntity(data));
				request = postRequest;
			} else {
				request = new HttpGet(url);
			}
			try {
				HttpResponse response = httpClient.execute(request);			
				int statuscode = response.getStatusLine().getStatusCode();
				if (statuscode >= HttpStatus.SC_OK && 
						statuscode <= HttpStatus.SC_MULTI_STATUS) {
					HttpEntity entity = response.getEntity();
					if (entity != null) {
						InputStream is = entity.getContent();
						data = readBytesFromStream(is);
						is.close();
						return data;
					}
				}
				if (HttpStatus.SC_MOVED_PERMANENTLY == statuscode ||
						HttpStatus.SC_MOVED_TEMPORARILY == statuscode) {
					url = response.getFirstHeader("Location").getValue();
					continue;
				}
			} catch (ClientProtocolException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
			break;
		}
		return null;
	}
	
	/**
	 * 计算MD5值
	 * @param file
	 * @return
	 */
	public static String md5(byte[] data) {
		MessageDigest digester;
		try {
			digester = MessageDigest.getInstance("MD5");
			digester.update(data);
			data = digester.digest();
			
			return bytesToHexString(data);
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		return null;
	}
	
	public static String getMacAddress() {
		// FIXME
		return "00-90-E6-00-08-F4";
	}
	
	public static String getLiveListURL() {
		// FIXME
		return "http://auth.playergetlist.com/ali/service";
	}
	
	public static String getTurnListURL() {
		// FIXME
		return "http://lunbo.playergetlist.com/nmpsp_server/ali/turn/service";
	}
	
	/**
	 * 从输入流中读取所有的内容
	 * @param input
	 * @return
	 */
	public static byte[] readBytesFromStream(InputStream input) {
		ByteArrayOutputStream outStream = new ByteArrayOutputStream();
		byte[] buf = new byte[4096];
		int len = 0;
		try {
			while((len = input.read(buf)) >= 0) {
				outStream.write(buf, 0, len);
			}
			return outStream.toByteArray();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return null;
	}
	
	public static boolean saveBytesToFile(byte[] data, File file) {
		boolean result = false;
		try {
			FileOutputStream fs = new FileOutputStream(file);
			fs.write(data);
			fs.close();
			result = true;
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return result;
	}
	
	/**
	 * 把字节数组转换成十六进制的字符串
	 * @param data
	 * @return
	 */
	public static String bytesToHexString(byte[] data) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < data.length; ++i) {
			int val = data[i] & 0xFF;
			sb.append(String.format("%02x", val));
		}
		return sb.toString();
	}
	
	public static String decodeFromUtf8(byte[] data) {
		String val;
		try {
			val = new String(data, "utf-8");
		} catch (UnsupportedEncodingException e) {
			val = "";
			e.printStackTrace();
		}
		return val;
	}
	
	public static class TimeUtil {
		public String getDate(int diff) {
			Calendar c = Calendar.getInstance();
			c.add(Calendar.DAY_OF_MONTH, diff);
			int year = c.get(Calendar.YEAR);
			int month = c.get(Calendar.MONTH) + 1;
			int day = c.get(Calendar.DAY_OF_MONTH);
			return String.format(Locale.CHINA, "%04d-%02d-%02d", year, month, day);
		}
		public String getCurrentTime() {
			Calendar c = Calendar.getInstance();
			int hour = c.get(Calendar.HOUR_OF_DAY);
			int minute = c.get(Calendar.MINUTE);
			return String.format(Locale.CHINA, "%02d:%02d", hour, minute);
		}
		public int compareTo(String date) {
			String now = this.getDate(0);
			if (!Pattern.matches("[0-9]{4}-[0-1][0-9]-[0-3][0-9]", now)) {
				return -2;
			}
			if (!Pattern.matches("[0-9]{4}-[0-1][0-9]-[0-3][0-9]", date)) {
				return -2;
			}
			
			String[] arr1 = now.split("-");
			String[] arr2 = date.split("-");
			
			int year1 = Integer.parseInt(arr1[0]);
			int month1 = Integer.parseInt(arr1[1]);
			int day1 = Integer.parseInt(arr1[2]);
			
			int year2 = Integer.parseInt(arr2[0]);
			int month2 = Integer.parseInt(arr2[1]);
			int day2 = Integer.parseInt(arr2[2]);
			
			if (year1 > year2) {
				return 1;
			}
			if (year1 < year2) {
				return -1;
			}
			if (month1 > month2) {
				return 1;
			}
			if (month1 < month2) {
				return -1;
			}
			if (day1 > day2) {
				return 1;
			}
			if (day1 < day2) {
				return -1;
			}
			
			return 0;
		}
		public int getHour(String time) {
			int pos = time.indexOf(":");
			if (pos > 0) {
				return Integer.parseInt(time.substring(0, pos), 10);
			}
			return 0;
		}
		public int getMinute(String time) {
			int pos = time.indexOf(":");
			if (pos > 0 && pos < time.length()) {
				return Integer.parseInt(time.substring(pos + 1), 10);
			}
			return 0;
		}
		public int getMinutes(String time) {
			if (!Pattern.matches("[0-2][0-9]:[0-5][0-9]", time)) {
				return 0;
			}
			int h = this.getHour(time);
			int m = this.getMinute(time);
			return h * 60 + m;
		}
	};
	
	public static class ImageCache extends LruCache<String, byte[]> {
		public ImageCache(int maxSize) {
			super(maxSize);
		}		
		@Override
		protected int sizeOf (String key, byte[] value) {
			return key.length() + value.length;
		}		
	};
}
