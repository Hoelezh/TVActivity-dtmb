package com.alitech.dvb;

import java.util.Locale;


public class DvbTime {
    int mMjd;
    int mYear;
    int mMonth;
    int  mDay;
    int  mWeekday;
    public int  mHour;
    public int  mMin;
    int  mSec;
    
    public DvbTime(int year, int month, int day, int hour, int min, int sec) {
    	this.mYear = year;
    	this.mMonth = month;
    	this.mDay = day;
    	this.mHour = hour;
    	this.mMin = min;
    	this.mSec = sec;
    	
    	this.mMjd = 0;
    	this.mWeekday = 0;
    }
    
    public String getDateSting() {
    	return String.format(Locale.CHINA, "%04d-%02d-%02d", mYear, mMonth, mDay);
    }
    
    public String getTimeSting() {
    	return String.format(Locale.CHINA, "%02d:%02d", mHour, mMin);
    }
}
