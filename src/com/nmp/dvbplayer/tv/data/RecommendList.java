package com.nmp.dvbplayer.tv.data;

import android.support.v4.util.LruCache;

public class RecommendList {
	public static class RecCache extends LruCache<String, RecommendItem[]> {
		public RecCache(int maxSize) {
			super(maxSize);
		}	
	};	
	private static RecCache mCache = new RecCache(20);
	
	public RecommendItem[] getRecommendList(String name) {
		RecommendItem[] recItems = mCache.get(name);
		if (recItems != null) {
			return recItems;
		}
		
		recItems = new RecommendItem[6];
		for (int i = 0; i < recItems.length; ++i) {
			recItems[i] = new RecommendItem(i, "大话西游大话西游大话西游大话西游" + i);
			recItems[i].setPosterURL("http://p1.qhimg.com/d/_hao360/video/vimg0106.jpg");
		}
		mCache.put(name, recItems);
		
		return recItems;
	}
}