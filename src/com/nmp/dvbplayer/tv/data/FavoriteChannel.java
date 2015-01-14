package com.nmp.dvbplayer.tv.data;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.nmp.dvbplayer.R;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.util.SparseArray;

public class FavoriteChannel {
	private static final String PreferenceKey = "tv-preference";
	private static final String FavoriteKey   = "favorite_key";
	private static final int    MaxItems      = 27;
	
	public static class MyArrayList<T> extends ArrayList<T> {
		private static final long serialVersionUID = 4172762042842831276L;
		public interface Finder<T> {
			public boolean isThisOne(T type);
		};
		
		public MyArrayList() {
			super();
		}
		
		public T find(Finder<T> finder) {
			T target = null;
			for (T type : this) {
				if (finder.isThisOne(type)) {
					target = type;
					break;
				}
			}
			return target;
		}
		
		public int findIndex(Finder<T> finder) {
			int target = -1;
			int index = -1;
			for (T type : this) {
				++index;
				if (finder.isThisOne(type)) {
					target = index;
					break;
				}
			}
			return target;
		}
	};
	
	private static class ChnFinder implements MyArrayList.Finder<TVChannel> {
		private int mId;
		public ChnFinder(int id) {
			this.mId = id;
		}
		@Override
		public boolean isThisOne(TVChannel type) {
			return type.getId() == this.mId;
		}
	};
	
	private static class FavFinder implements MyArrayList.Finder<FavChn> {
		private int mId;
		public FavFinder(int id) {
			this.mId = id;
		}
		@Override
		public boolean isThisOne(FavChn type) {
			return type.getId() == this.mId;
		}
	};
	
	public static class FavChn {
		private static final String KeyCount  = "count";
		private static final String KeyElapse = "elapse";
		private static final String KeyType   = "type";
		private static final String KeyTime   = "time";
		private static final String KeyId     = "id";
		
		public static final int TypeAuto   = 0;
		public static final int TypeManual = 1;
		
		private int     mWatchCount;
		private long    mWatchElapse;
		private int     mAddType;
		private long    mAddTime;
		private int     mChnId;
		
		public FavChn(int id, int type) {
			this.mWatchCount = 1;
			this.mWatchElapse = 0;
			this.mAddType = type;
			this.mAddTime = System.currentTimeMillis();
			this.mChnId = id;
		}
		
		public int addWatchCount(int count) {
			this.mWatchCount += count;
			return this.mWatchCount;
		}
		
		public long addWatchElapse(long elapse) {
			this.mWatchElapse += elapse;
			return this.mWatchElapse;
		}
		
		public void setType(int type) {
			this.mAddType = type;
		}
		
		public int getType() {
			return this.mAddType;
		}
		
		public long getTime() {
			return this.mAddTime;
		}
		
		public int getId() {
			return this.mChnId;
		}
		
		public String toJSON() {
			JSONObject obj = new JSONObject();
			try {
				obj.put(KeyCount, this.mWatchCount);
				obj.put(KeyElapse, this.mWatchElapse);
				obj.put(KeyType, this.mAddType);
				obj.put(KeyTime, this.mAddTime);
				obj.put(KeyId, this.mChnId);
			} catch (JSONException e) {
				e.printStackTrace();
			}
			return obj.toString();
		}
		
		public static FavChn fromJSON(String json) {
			FavChn fchn = new FavChn(-1, TypeAuto);
			try {
				JSONObject obj = new JSONObject(json);
				fchn.mWatchCount = obj.optInt(KeyCount, 0);
				fchn.mWatchElapse = obj.optLong(KeyElapse, 0);
				fchn.mAddType = obj.optInt(KeyType, TypeAuto);
				fchn.mAddTime = obj.optLong(KeyTime, 0);
				fchn.mChnId = obj.optInt(KeyId, -1);
			} catch (JSONException e) {
				e.printStackTrace();
			}
			return fchn;
		}
	};
	
	public static class TVFavGroup extends TVGroup {
		public TVFavGroup(int id, String name) {
			super(id, name);
		}
	}
	
	private ChannelList          mChnList;
	private Context              mContext;
	
	private MyArrayList<FavChn>    mFavData;
	private MyArrayList<TVChannel> mChannels;
	
	public FavoriteChannel(Context ctx, ChannelList list) {
		this.mContext = ctx;
		this.mChnList = list;
		this.mFavData = new MyArrayList<FavChn>();
		this.mChannels = new MyArrayList<TVChannel>();
		
		SharedPreferences preference = this.getSharedPreferences();
		this.fromJSON(preference.getString(FavoriteKey, "[]"));
		this.addFavChn(null);
	}
	
	public ArrayList<TVChannel> findChnFromId(int chnId) {
		ArrayList<TVChannel> result = new ArrayList<TVChannel>();
		TVGroup[] groups = this.mChnList.getGroups();
		if (null == groups) {
			return result;
		}

		for (int i = 0; i < groups.length; ++i) {
			TVChannel[] channels = this.mChnList.getChannels(groups[i]);
			if (null == channels) {
				continue;
			}
			for (int j = 0; j < channels.length; ++j) {
				TVChannel tvChn = channels[j];
				if (tvChn.getId() == chnId) {
					result.add(tvChn);
				}
			}
		}
		
		return result;
	}
	
	public void addFavChn(FavChn fchn) {
		if (fchn != null) {
			FavChn oldfchn = this.mFavData.find(new FavFinder(fchn.getId()));
			if (null == oldfchn) {
				this.mFavData.add(fchn);
			} else {
				oldfchn.mWatchCount += fchn.mWatchCount;
				oldfchn.mWatchElapse += fchn.mWatchElapse;
				oldfchn.mAddTime = fchn.mAddTime;
				if (oldfchn.mAddType != FavChn.TypeManual) {
					oldfchn.mAddType = fchn.mAddType;
				}
			}
			this.sort();
		}
		
		// 使用Hash来加快从ID查找频道的速度！因为频道列表随时有可能变化，不能缓存这个Hash, 这个操作太昂贵啦！
		// 可恨的是同一个ID会有多个频道，比如央视台的CCTV-1，在高清台也有一个CCTV-1，并且他们的ID
		// 是一样的，如果用户需要收藏CCTV-1，显然两个CCTV-1都要在UI上显示心号！
		SparseArray<ArrayList<TVChannel>> chnMap;
		chnMap = new SparseArray<ArrayList<TVChannel>>();
		TVGroup[] groups = this.mChnList.getGroups();
		if (groups != null) {
			for (int i = 0; i < groups.length; ++i) {
				TVChannel[] channels = this.mChnList.getChannels(groups[i]);
				if (channels != null) {
					for (int j = 0; j < channels.length; ++j) {
						TVChannel tvChn = channels[j];
						ArrayList<TVChannel> chlst = chnMap.get(tvChn.getId());
						if (null == chlst) {
							chlst = new ArrayList<TVChannel>();
							chnMap.put(tvChn.getId(), chlst);
						}
						chlst.add(tvChn);
					}
				}
			}
		}
		
		this.mChannels.clear();
		for (FavChn chn : this.mFavData) {
			ArrayList<TVChannel> chlst = chnMap.get(chn.getId());
			if (chlst != null && chlst.size() > 0) {
				for (TVChannel tchn : chlst) {
					tchn.setFavorite(true);
				}
				this.mChannels.add(chlst.get(0));
			}
		}
		
		removeFavChn(-1);
	}
	
	public void removeFavChn(int chnId) {		
		int idx = this.mChannels.findIndex(new ChnFinder(chnId));
		if (idx >= 0) {
			this.mChannels.remove(idx);
			ArrayList<TVChannel> chnlist = this.findChnFromId(chnId);
			for (TVChannel chn : chnlist) {
				chn.setFavorite(false);
			}
		}
		
		MyArrayList<FavChn> tmpChns = new MyArrayList<FavChn>();
		for (TVChannel chn : this.mChannels) {
			FavChn fchn = this.mFavData.find(new FavFinder(chn.getId()));
			if (fchn != null) {
				tmpChns.add(fchn);
			}
		}
		this.mFavData = tmpChns;
		
		SharedPreferences preference = this.getSharedPreferences();
    	SharedPreferences.Editor editor = preference.edit();
    	editor.putString(FavoriteKey, this.toJSON());
    	editor.commit();
	}
	
	private SharedPreferences getSharedPreferences() {
    	String key = PreferenceKey + "-" + this.mChnList.getType();
    	int mode = Context.MODE_PRIVATE;
    	Context ctx = this.mContext;
    	return ctx.getSharedPreferences(key, mode);
    }
	
	private String toJSON() {
		JSONArray arr = new JSONArray();
		for (FavChn chn: this.mFavData) {
			arr.put(chn.toJSON());
		}
		return arr.toString();
	}
	
	private void fromJSON(String json) {
		this.mFavData.clear();
		try {
			JSONArray arr = new JSONArray(json);
			for (int i = 0; i < arr.length(); ++i) {
				String str = arr.optString(i, "{}");
				FavChn chn = FavChn.fromJSON(str);
				this.mFavData.add(chn);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}
	
	private void sort() {
		Collections.sort(this.mFavData, new Comparator<FavChn>() {
	        @Override
	        public int compare(FavChn chn1, FavChn chn2) {
	        	if (chn1.mAddType > chn2.mAddType) {
	        		return -1;
	        	}
	        	if (chn1.mAddType < chn2.mAddType) {
	        		return 1;
	        	}
	        	
	        	if (FavChn.TypeManual == chn1.mAddType) {
	        		if (chn1.mAddTime > chn2.mAddTime) {
	        			return -1;
	        		}
	        		if (chn1.mAddTime < chn2.mAddTime) {
	        			return 1;
	        		}
	        	}
	        	
	        	if (chn1.mWatchElapse > chn2.mWatchElapse) {
	        		return -1;
	        	}	        	
	        	if (chn1.mWatchElapse < chn2.mWatchElapse) {
	        		return 1;
	        	}
	        	
	        	if (chn1.mWatchCount > chn2.mWatchCount) {
	        		return -1;
	        	}
	        	if (chn1.mWatchCount < chn2.mWatchCount) {
	        		return 1;
	        	}        	
	        	
	            return 0;
	        }
	    });
		if (this.mFavData.size() > MaxItems) {
			this.mFavData.subList(MaxItems, this.mFavData.size()).clear();
		}
	}
	
	public TVChannel[] getChannels() {
		if (this.mChannels.size() < 1) {
			return null;
		}
		TVChannel[] chns = new TVChannel[this.mChannels.size()];
		this.mChannels.toArray(chns);
		return chns;
	}
	
	public TVGroup getGroup() {
		Resources res = this.mContext.getResources();
		String name = res.getString(R.string.tv_fav_name);
		return new TVFavGroup(0, name);
	}
}
