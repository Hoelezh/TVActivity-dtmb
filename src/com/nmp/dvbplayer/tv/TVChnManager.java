package com.nmp.dvbplayer.tv;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

import org.json.JSONException;
import org.json.JSONObject;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.util.SparseArray;
import android.util.SparseIntArray;

import com.alitech.dvb.DvbChannelList;
import com.nmp.dvbplayer.tv.data.ChannelList;
import com.nmp.dvbplayer.tv.data.FavoriteChannel;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.tv.data.TVGroup;
import com.nmp.dvbplayer.tv.data.TVProgram;
import com.nmp.dvbplayer.tv.data.TVSource;
import com.nmp.dvbplayer.tv.data.FavoriteChannel.FavChn;

public class TVChnManager implements ChannelList.UpdateListener {
	public enum UpdateEvent {
		GruopsUpdate,
		ChannelsUpdate,
		ProgramsUpdate,
		SourcesUpdate
	};
	
	public interface UpdateListener {
		void onUpdate(UpdateEvent event);
	};
	
	private static class ChannelItem {
		private TVChannel mChannel;
		private int mGroupIdx;
		private int mChannelIdx;
	}
	
	private static final String  Tag = TVChnManager.class.getName();
	private static final int     SaveInterval = 60 * 1000;
	private static final int     MSG_SAVE_POSITION   = 2;
	
	private static class ProgressHistory {
    	public int ProgramId;
    	public int Position;
    	public SparseIntArray SourceInfo;
    	
		public ProgressHistory() {
    		this.ProgramId = -1;
    		this.Position = 0;
    		this.SourceInfo = new SparseIntArray();
    	}
    }
	
	private class GetProgramsTask extends AsyncTask<TVChannel, Void, TVProgram[]> {
		@Override
		protected TVProgram[] doInBackground(TVChannel... params) {
			TVProgram[] result = null;
			if (mChnList != null) {
				result = mChnList.getPrograms(params[0]);
        	}
			return result;
		}
		@Override
		protected void onPostExecute(TVProgram[] result) {
			mPrograms = result;
			mSources = null;
			mProgramsTask = null;
			mProgramValid = true;
			restoreProgramIdx();
			if (mUpdateListener != null) {
				mUpdateListener.onUpdate(UpdateEvent.ProgramsUpdate);
			}
		}
	};
	
	@SuppressLint("HandlerLeak")
	private Handler mMsgHandler = new Handler() {
		@Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case MSG_SAVE_POSITION:
            	saveSrcHistory();
            	break;
            default:
            	super.handleMessage(msg);
            	break;
            }
        }
	};
	
	private TVActivity           mTV;
	private ChannelList          mChnList;
	private UpdateListener       mUpdateListener;
	private GetProgramsTask      mProgramsTask;
	private FavoriteChannel      mFavChns;
	
	private TVGroup[]            mGroups;
	private TVChannel[]          mChannels;
	private TVChannel[]          mFocusChannels;
	private TVProgram[]          mPrograms;
	private TVSource[]           mSources;
	
	private boolean              mProgramValid;
	private int                  mFocusGrpIdx;
	private int                  mSelGrpIdx;	
	private int                  mFocusChnIdx;
	private int                  mSelChnIdx;	
	private int                  mSelPrgIdx;
	private int                  mSelSrcIdx;
	private boolean              mProgressDirty;
	
	private SparseArray<ProgressHistory> mProgressHistory;
	private ArrayList<ChannelItem>       mChannelInfo;
	
	public TVChnManager(TVActivity tv) {
		this.mTV = tv;
		if (TVActivity.TV_DVB == this.mTV.getTVType()) {
			this.mChnList = new DvbChannelList(this.mTV);
		} else {
			//this.mChnList = new NetChannelList(this.mTV);
		}
		this.mChnList.setUpdateListener(this);
		int msg = MSG_SAVE_POSITION;
		this.mMsgHandler.sendEmptyMessageDelayed(msg, SaveInterval);
		this.mFavChns = new FavoriteChannel(this.mTV, this.mChnList);
		
		this.mProgramsTask = null;
		
		this.mGroups = null;
		this.mChannels = null;
		this.mFocusChannels = null;
		this.mPrograms = null;
		this.mSources = null;
		this.mProgramValid = false;
		
		this.mFocusGrpIdx = 0;
		this.mSelGrpIdx = 0;		
		this.mFocusChnIdx = 0;
		this.mSelChnIdx = 0;		
		this.mSelPrgIdx = 0;
		this.mSelSrcIdx = 0;
		this.mProgressDirty = false;
		
		this.mProgressHistory = new SparseArray<ProgressHistory>();
		this.mChannelInfo = this.buildList();
		this.restoreSelectedIdx();
		this.restoreSrcHistory();
	}
	
	public void setUpdateListener(UpdateListener listener) {
		this.mUpdateListener = listener;
	}
	
	public String getselchnum() {
		return this.getSelChannel().getNumber();
		//return this.mSelSrcIdx;
	}
	
	public ChannelList getChannelList() {
		return this.mChnList;
	}
	
	public void destroy() {
		this.mMsgHandler.removeMessages(MSG_SAVE_POSITION);
		if (this.mProgramsTask != null) {
			this.mProgramsTask.cancel(true);
			this.mProgramsTask = null;
		}
		this.mChnList.destroy();
		this.saveSrcHistory();
	}
    
	public TVGroup[] getGroups() {
		if (null == this.mGroups) {
			this.mGroups = this.mChnList.getGroups();
			this.mChannels = null;
			this.mFocusChannels = null;
			this.mPrograms = null;
			this.mSources = null;
			this.mProgramValid = false;
			
			TVGroup[] groups = this.mGroups;
			if (groups != null && groups.length > 0) {
				int len = groups.length;
				this.mGroups = new TVGroup[len + 1];
				for (int i = 0; i < len; ++i) {
					this.mGroups[i] = groups[i];
				}
				this.mGroups[len] = this.mFavChns.getGroup();
			}
		}
		return this.mGroups;
	}
	
	public TVGroup getFocusGroup() {
		TVGroup[] groups = this.getGroups();
    	if (null == groups || groups.length < 1) {
    		Log.e(Tag, "no group data!");
    		return null;
    	}
    	if (this.mFocusGrpIdx < 0 || this.mFocusGrpIdx >= groups.length) {
    		Log.e(Tag, "invalid group index!");
    		return null;
    	}
    	
    	return groups[this.mFocusGrpIdx];
	}
	
	public TVChannel[] getFocusChannels() {
		if (null == this.mFocusChannels) {
			TVGroup group = this.getFocusGroup();
			if (group != null) {
				if (group instanceof FavoriteChannel.TVFavGroup) {
					this.mFocusChannels = this.mFavChns.getChannels();
				} else {
					this.mFocusChannels = this.mChnList.getChannels(group);
				}
			}
		}
		return this.mFocusChannels;
	}
	
    public TVGroup getSelGroup() {
    	TVGroup[] groups = this.getGroups();
    	if (null == groups || groups.length < 1) {
    		Log.e(Tag, "no group data!");
    		return null;
    	}
    	if (this.mSelGrpIdx < 0 || this.mSelGrpIdx >= groups.length) {
    		Log.e(Tag, "invalid group index!");
    		return null;
    	}
    	return groups[this.mSelGrpIdx];
    }
    
    public TVChannel getFocusChannel() {
    	TVChannel[] channels = this.getFocusChannels();
    	if (null == channels || channels.length < 1) {
    		Log.e(Tag, "no focus channel data!");
    		return null;
    	}
    	if (this.mFocusChnIdx < 0 || this.mFocusChnIdx >= channels.length) {
    		Log.e(Tag, "invalid focus group index!");
    		return null;
    	}
    	return channels[this.mFocusChnIdx];
    }
	
	public TVChannel[] getSelChannels() {
		if (null == this.mChannels) {
			TVGroup group = this.getSelGroup();
			if (group != null) {
				if (group instanceof FavoriteChannel.TVFavGroup) {
					this.mChannels = this.mFavChns.getChannels();
				} else {
					this.mChannels = this.mChnList.getChannels(group);
				}
				this.mPrograms = null;
				this.mSources = null;
				this.mProgramValid = false;
			}
		}
		return this.mChannels;
	}
	
	public TVProgram[] getSelPrograms() {
		if (null == this.mPrograms && !this.mProgramValid) {
			TVChannel channel = this.getSelChannel();
			if (channel != null) {
				if (channel.getType() != TVChannel.NET_TURN_NODE) {
					this.mPrograms = this.mChnList.getPrograms(channel);
					this.mSources = null;
					this.mProgramValid = true;
					this.restoreProgramIdx();
				} else {
					if (this.mProgramsTask != null) {
						this.mProgramsTask.cancel(true);
					}
					this.mProgramsTask = new GetProgramsTask();
					Executor exec = Executors.newCachedThreadPool();
					this.mProgramsTask.executeOnExecutor(exec, channel);
				}
			}
		}
		return this.mPrograms;
	}
	
	public TVSource[] getSelSources() {
		if (null == this.mSources) {
			TVProgram program = this.getSelProgram();
			if (program != null) {
				this.mSources = this.mChnList.getSources(program);
				this.reorderSource();
			}
		}
		return this.mSources;
	}
    
    public TVChannel getSelChannel() {
    	TVChannel[] channels = this.getSelChannels();
    	if (null == channels || channels.length < 1) {
    		Log.e(Tag, "no channel data!");
    		return null;
    	}
    	if (this.mSelChnIdx < 0 || this.mSelChnIdx >= channels.length) {
    		Log.e(Tag, "invalid channel index!");
    		return null;
    	}
    	return channels[this.mSelChnIdx];
    }
    
    public TVProgram getSelProgram() {
    	TVProgram[] programs = this.getSelPrograms();
    	if (null == programs || programs.length < 1) {
    		Log.e(Tag, "current program is null");
    		return null;
    	}
    	if (this.mSelPrgIdx < 0 || this.mSelPrgIdx >= programs.length) {
    		Log.e(Tag, "invalid program index!");
    		return null;
    	}
    	return programs[this.mSelPrgIdx];
    }
    
    public TVSource getSelSource() {
    	TVSource[] sources = this.getSelSources();
    	if (null == sources || sources.length < 1) {
    		Log.e(Tag, "no source data");
    		return null;
    	}
    	if (this.mSelSrcIdx < 0 || this.mSelSrcIdx >= sources.length) {
    		Log.e(Tag, "invalid source index!");
    		return null;
    	}
    	return sources[this.mSelSrcIdx];
    }
    
    public int getFocusGrpIdx() {
    	return this.mFocusGrpIdx;
    }
    
    public int getSelGrpIdx() {
    	return this.mSelGrpIdx;
    }
    
    public int getFocusChnIdx() {
    	return this.mFocusChnIdx;
    }
    
    public int getSelChnIdx() {
    	return this.mSelChnIdx;
    }
    
    public int getSelPrgIdx() {
    	return this.mSelPrgIdx;
    }
    
    public int getSelSrcIdx() {
    	return this.mSelSrcIdx;
    }
    
    public void changeFocusGroup(int diff) {
    	TVGroup[] groups = this.getGroups();
    	if (null == groups || groups.length < 1) {
    		return;
    	}
    	
    	int grpLen = groups.length;
    	this.mFocusGrpIdx += diff;
    	if (this.mFocusGrpIdx < 0) {
    		this.mFocusGrpIdx += grpLen;
    	}
    	if (this.mFocusGrpIdx >= grpLen) {
    		this.mFocusGrpIdx -= grpLen;
    	}
    	
    	this.mFocusChnIdx = 0;
    	this.mFocusChannels = null;
    }
    
    public boolean isFirstChannel() {
    	return this.mFocusChnIdx == 0;
    }
    
    public boolean isLastChannel() {
    	TVChannel[] channels = this.getFocusChannels();
    	if (null == channels) {
    		return true;
    	}
    	return this.mFocusChnIdx == channels.length - 1;
    }
    
    public void changeFocusChannel(int diff) {
    	TVChannel[] channels = this.getFocusChannels();
    	if (null == channels) {
    		return;
    	}
    	this.mFocusChnIdx += diff;
    	if (this.mFocusChnIdx < 0) {
    		this.mFocusChnIdx = 0;
    	}
    	if (this.mFocusChnIdx >= channels.length) {
    		this.mFocusChnIdx = channels.length - 1;
    	}
    }
    
    public boolean findChannel(int diff, String num) {
    	boolean result = false;
    	TVGroup group = this.getSelGroup();
    	if (null == group) {
    		return false;
    	}
    	
    	if (TVActivity.TV_DVB == this.mTV.getTVType() ||
    			(group instanceof FavoriteChannel.TVFavGroup && diff != 0)) {
    		result = this.findChnInGroup(diff, num);
    	} else {
    		result = this.findChnInAllGroups(diff, num);
    	}
    	return result;
    }
    
    private boolean findChnInAllGroups(int diff, String num) {
    	boolean result = false;
    	TVChannel chn = this.getSelChannel();
    	ChannelItem resultItem = null;
    	
    	for (ChannelItem chnItem : this.mChannelInfo) {
    		if (num != null && chnItem.mChannel != null) {
    			int num1 = 0;
    			int num2 = 0;
    			try {
    				num1 = Integer.valueOf(chnItem.mChannel.getNumber());
    				num2 = Integer.valueOf(num);    				
    			} catch (Exception e) {
    				e.printStackTrace();
    			}
    			if (num1 == num2) {
					resultItem = chnItem;
	    			result = true;
	    			break;
				}
    		}
    		if (diff != 0 && chn != null && chn == chnItem.mChannel) {
    			resultItem = chnItem;
    			result = true;
    			break;
    		}
    	}
    	
    	if (result && diff != 0 && resultItem != null) {
    		int size = this.mChannelInfo.size();
    		int oldIdx = this.mChannelInfo.indexOf(resultItem);
    		String oldNum = resultItem.mChannel.getNumber();
   		
    		int dir = diff > 0 ? 1 : -1;
    		int count = 0;
    		int index = oldIdx;
    		while (count < Math.abs(diff)) {
    			index += dir;
    			index %= size;
    			index += size;
    			index %= size;    			
    			if (index == oldIdx) {
    				break;
    			}    			
    			resultItem = this.mChannelInfo.get(index);
    			if (!oldNum.equals(resultItem.mChannel.getNumber())) {
    				count += 1;
    			}
    		}    		
    	}
    	
    	if (result && resultItem != null) {
        	if (this.mSelGrpIdx != resultItem.mGroupIdx) {
        		this.mChannels = null;
        	}
        	this.mSelChnIdx = resultItem.mChannelIdx;
        	this.mSelGrpIdx = resultItem.mGroupIdx;
        	this.mPrograms = null;
    		this.mSources = null;
    		this.mProgramValid = false;
        	this.mSelPrgIdx = 0;
        	this.mSelSrcIdx = 0;
        	this.resetFocusChannel();
        	this.saveSelectedIdx();
        	this.mTV.notifyEvent(TVRelatedView.ChnEvent);
    	}
    	
    	return result;
    }
    
    private boolean findChnInGroup(int diff, String num) {
    	TVChannel[] channels = this.getSelChannels();
    	if (null == channels || (0 == diff && null == num)) {
    		return false;
    	}
    	
    	boolean found = false;
    	int counter = 0;
    	int len = channels.length;
    	int dir = diff > 0 ? 1 : -1;
    	int chnIdx = this.mSelChnIdx;
    	do {
    		this.mSelChnIdx += dir;
    		this.mSelChnIdx %= len;
    		this.mSelChnIdx += len;
    		this.mSelChnIdx %= len;
    		if (diff != 0) {
	    		counter += 1;
	    		if (counter >= Math.abs(diff)) {
	    			found = true;
	    			break;
	    		}
			}
    		if (num != null) {
				TVChannel chn = this.getSelChannel();
				if (chn != null) {
					int num1 = 0;
					int num2 = 0;
					try {
						num1 = Integer.valueOf(chn.getNumber());
						num2 = Integer.valueOf(num);
					} catch (Exception e) {
						e.printStackTrace();
					}
					if (num1 == num2) {
						found = true;
						break;
					}
				}
			}    		
    	} while (chnIdx != this.mSelChnIdx);
    	
    	if (found) {
    		this.mPrograms = null;
    		this.mSources = null;
    		this.mProgramValid = false;
        	this.mSelPrgIdx = 0;
        	this.mSelSrcIdx = 0;
        	this.resetFocusChannel();
        	this.saveSelectedIdx();
        	this.mTV.notifyEvent(TVRelatedView.ChnEvent);
    	} else {
    		this.mSelChnIdx = chnIdx;
    	}
    	
    	return found;
    }
    
    private ArrayList<ChannelItem> buildList() {
    	ArrayList<ChannelItem> chnItems = new ArrayList<ChannelItem>();
    	TVGroup[] groups = this.mChnList.getGroups();
    	if (null == groups || groups.length < 1) {
    		return chnItems;
    	}
    	
    	for (int i = 0; i < groups.length; ++i) {
    		TVChannel[] chns = this.mChnList.getChannels(groups[i]);
    		if (null == chns || chns.length < 1) {
    			continue;
    		}
    		
    		if (groups[i] instanceof FavoriteChannel.TVFavGroup) {
    			continue;
    		}
    		
    		for (int j = 0; j < chns.length; ++j) {
	    		ChannelItem chnItem = new ChannelItem();
	    		chnItem.mChannel = chns[j];
	    		chnItem.mGroupIdx = i;
	    		chnItem.mChannelIdx = j;
	    		chnItems.add(chnItem);
    		}
    	}
    	
    	Comparator<ChannelItem> comp = new Comparator<ChannelItem>() {
			@Override
			public int compare(ChannelItem chn1, ChannelItem chn2) {
				int num1 = Integer.valueOf(chn1.mChannel.getNumber());
				int num2 = Integer.valueOf(chn2.mChannel.getNumber());
				Integer integer = num1;
				return integer.compareTo(num2);
			}
		};
		Collections.sort(chnItems, comp);
    	
    	return chnItems;
    }
    /*
    private boolean findChnAllGroups(int diff, String num) {
    	TVGroup[] groups = this.getGroups();
    	TVChannel[] channels = this.getSelChannels();
    	
    	if (null == groups || null == channels ||
    			(0 == diff && null == num)) {
    		return false;
    	}
    	
    	int grpIdx = this.mSelGrpIdx;
    	int chnIdx = this.mSelChnIdx;    	
    	// 备份状态信息，在没有找到对应的频道时需要恢复！
    	TVChannel[] oldChns = this.mChannels;
    	TVProgram[] oldPrgs = this.mPrograms;
    	TVSource[] oldSrcs = this.mSources;
    	boolean oldValid = this.mProgramValid;
    	int oldPrgIdx = this.mSelPrgIdx;
    	int oldSrcIdx = this.mSelSrcIdx;
    	
    	this.mPrograms = null;
		this.mSources = null;
		this.mProgramValid = false;
    	this.mSelPrgIdx = 0;
    	this.mSelSrcIdx = 0;
    	
    	int dir = diff > 0 ? 1 : -1;
    	int grpLen = groups.length;
    	
    	boolean found = false;
    	int counter = 0;    	
    	do {
    		boolean changeGrp = false;
    		int chnLen = channels.length;
    		this.mSelChnIdx += dir;
			if (this.mSelChnIdx < 0 || this.mSelChnIdx >= chnLen) {
				changeGrp = true;
				int tmpGrp = this.mSelGrpIdx;
				do {
					this.mSelGrpIdx += dir;
					if (this.mSelGrpIdx < 0) {
	    				this.mSelGrpIdx = grpLen - 1;
	    			}
	    			if (this.mSelGrpIdx >= grpLen) {
	    				this.mSelGrpIdx = 0;
	    			}
	    			
	    			this.mChannels = null;	    			
					channels = this.getSelChannels();
					
					if (channels != null) {
						break;
					}
				} while (tmpGrp != this.mSelGrpIdx);
				
				if (null == channels) { // no channel data!
					break;
				}
			}
			
			chnLen = channels.length;
			if (changeGrp && this.mSelChnIdx < 0) {
    			this.mSelChnIdx = chnLen - 1;
			} else if (changeGrp && this.mSelChnIdx >= 0) {
    			this.mSelChnIdx = 0;
    		}
    		
			if (diff != 0) {
	    		counter += 1;
	    		if (counter >= Math.abs(diff)) {
	    			found = true;
	    			break;
	    		}
			}
			
			if (num != null) {
				TVChannel chn = this.getSelChannel();
				if (chn != null && num.equalsIgnoreCase(chn.getNumber())) {
					found = true;
					break;
				}
			}
    		
    	} while (grpIdx != this.mSelGrpIdx || chnIdx != this.mSelChnIdx);
    	
    	if (found) {    	
	    	this.resetFocusChannel();
	    	this.saveSelectedIdx();
    	} else {
    		this.mSelGrpIdx = grpIdx;
        	this.mSelChnIdx = chnIdx;
        	this.mChannels = oldChns;
        	this.mPrograms = oldPrgs;
        	this.mSources = oldSrcs;
        	this.mProgramValid = oldValid;
        	this.mSelPrgIdx = oldPrgIdx;
        	this.mSelSrcIdx = oldSrcIdx;
    	}
    	
    	return found;
    }
    */
    
    public void changeSelProgram(int diff) {
    	TVProgram[] programs = this.getSelPrograms();
    	if (null == programs || programs.length < 1) {
    		return;
    	}

    	this.mSelPrgIdx += diff;
    	if (this.mSelPrgIdx < 0) {
    		this.mSelPrgIdx += programs.length;
    	}
    	if (this.mSelPrgIdx >= programs.length) {
    		this.mSelPrgIdx -= programs.length;
    	}
    	
    	this.mSelSrcIdx = 0;
    	this.mSources = null;
    	
    	this.saveCurrentProgress(true);
    }
    
    public void changeSelSource(int diff) {
    	TVSource[] sources = this.getSelSources();
    	if (null == sources || sources.length < 1) {
    		return;
    	}
    	
    	this.mSelSrcIdx += diff;
    	if (this.mSelSrcIdx < 0) {
    		this.mSelSrcIdx += sources.length;
    	}
    	if (this.mSelSrcIdx >= sources.length) {
    		this.mSelSrcIdx -= sources.length;
    	}
    	
    	this.saveCurrentProgress(false);
    	this.mTV.notifyEvent(TVSourceView.SrcEvent);
    }
    
    public void toggleFavorite() {
    	TVChannel chn = this.getFocusChannel();
    	if (null == chn) {
    		return;
    	}
    	if (chn.isFavorite()) {
    		this.mFavChns.removeFavChn(chn.getId());
    	} else {
    		FavChn fchn = new FavChn(chn.getId(), FavChn.TypeManual);
    		this.mFavChns.addFavChn(fchn);
    	}
    	this.mFocusChannels = null;
    }
    
    public void addWatchElapse(long elapse) {
    	TVChannel chn = this.getSelChannel();
    	if (null == chn) {
    		return;
    	}
    	FavChn fchn = new FavChn(chn.getId(), FavChn.TypeAuto);
    	fchn.addWatchElapse(elapse);
    	this.mFavChns.addFavChn(fchn);
    }
    
    public boolean faultSelect() {
    	return (this.mSelGrpIdx == this.mFocusGrpIdx &&
    			this.mSelChnIdx == this.mFocusChnIdx);
    }
    
    public void selectChannel() {
    	this.mSelChnIdx = this.mFocusChnIdx;
    	this.mSelGrpIdx = this.mFocusGrpIdx;
    	this.mChannels = null;
    	this.mPrograms = null;
    	this.mSources = null;
    	this.mProgramValid = false;
    	this.mSelPrgIdx = 0;
    	this.mSelSrcIdx = 0;
    	this.saveSelectedIdx();
    	this.mTV.notifyEvent(TVRelatedView.ChnEvent);
    }
    
    public void resetFocusChannel() {
    	this.mFocusChnIdx = this.mSelChnIdx;
    	this.mFocusGrpIdx = this.mSelGrpIdx;
    	this.mFocusChannels = this.mChannels;
    }
    
    private static final String PreferenceKey  = "tv-preference-history";
    private static final String SelectedGrpKey = "selected-group";
    private static final String SelectedChnKey = "selected-channel";
    private static final String TVProgressKey  = "progress-history";
    private static final String ProgramIdKey   = "programId";
    private static final String PositionKey    = "position";
    private static final String SourcesKey     = "sources";
    
    private SharedPreferences getSharedPreferences() {
    	String key = PreferenceKey + "-" + this.mChnList.getType();
    	int mode = Context.MODE_PRIVATE;
    	Context ctx = this.mTV;
    	return ctx.getSharedPreferences(key, mode);
    }
    
    private void saveSelectedIdx() {
    	TVGroup grp = this.getSelGroup();
    	TVChannel chn = this.getSelChannel();
    	if (null == grp || null == chn) {
    		Log.d(Tag, "no focus data to save!");
    		return;
    	}
    	
    	SharedPreferences preference = this.getSharedPreferences();
    	SharedPreferences.Editor editor = preference.edit();
    	editor.putInt(SelectedGrpKey, grp.getId());
    	editor.putInt(SelectedChnKey, chn.getId());
    	editor.commit();
    }
    
    private void restoreSelectedIdx() {
    	SharedPreferences preference = this.getSharedPreferences();
    	int grpId = preference.getInt(SelectedGrpKey, -1);
    	int chnId = preference.getInt(SelectedChnKey, -1);
    	this.restoreSelectedIdx(grpId, chnId);
    }
    
    private void restoreSelectedIdx(int grpId, int chnId) {
    	TVGroup[] grps = this.getGroups();
    	if (null == grps) {
    		Log.d(Tag, "no group data for restore history!");
    		return;
    	}
    	int idx = -1;
    	for (int i = 0; i < grps.length; ++i) {
    		if (grpId == grps[i].getId()) {
    			idx = i;
    			break;
    		}
    	}
    	if (-1 == idx) {
    		Log.d(Tag, "history selected group not found!");
    		return;
    	}
    	this.mSelGrpIdx = idx;
    	TVChannel[] chns = this.getSelChannels();
    	if (null == chns) {
    		Log.d(Tag, "no channel data for restore history!");
    		return;
    	}
    	idx = -1;
    	for (int i = 0; i < chns.length; ++i) {
    		if (chnId == chns[i].getId()) {
    			idx = i;
    			break;
    		}
    	}
    	if (-1 == idx) {
    		Log.d(Tag, "history selected channel not found!");
    		return;
    	}
    	this.mSelChnIdx = idx;
    	this.resetFocusChannel();
    }
    
    private void saveCurrentProgress(boolean resetPos) {
    	TVChannel chn = this.getSelChannel();
    	TVProgram prg = this.getSelProgram();
    	TVSource src = this.getSelSource();
    	if (chn != null && prg != null && src != null) {
    		ProgressHistory progress = new ProgressHistory();    		
    		if (this.mProgressHistory.indexOfKey(chn.getId()) >= 0) {
    			progress = this.mProgressHistory.get(chn.getId());
    		}
    		progress.ProgramId = prg.getId();
    		if (resetPos) {
    			progress.Position = 0;
    		}
    		progress.SourceInfo.put(prg.getId(), src.getId());
    		this.mProgressHistory.put(chn.getId(), progress);
    		this.mProgressDirty = true;
    	}
    }
    
    public void saveSrcHistory() {
    	if (!this.mProgressDirty) {
    		return;
    	}
    	
    	JSONObject jsonProgress = new JSONObject();
    	
    	int hsize = this.mProgressHistory.size();
    	for (int i = 0; i < hsize; ++i) {
    		int channelId = this.mProgressHistory.keyAt(i);
    		ProgressHistory progress = this.mProgressHistory.get(channelId);
    		if (null == progress) {
    			continue;
    		}
    		try {
    			JSONObject jsonProgressItem = new JSONObject();
				jsonProgressItem.put(ProgramIdKey, progress.ProgramId);
				jsonProgressItem.put(PositionKey, progress.Position);				
				JSONObject jsonSources = new JSONObject();
				
				int keySize = progress.SourceInfo.size();
				for (int j = 0; j < keySize; ++j) {
					int programId = progress.SourceInfo.keyAt(j);
					int sourceId = progress.SourceInfo.get(programId);
					jsonSources.put(String.valueOf(programId), String.valueOf(sourceId));
				}
				
				jsonProgressItem.put(SourcesKey, jsonSources);				
				jsonProgress.put(String.valueOf(channelId), jsonProgressItem);
			} catch (JSONException e) {
				e.printStackTrace();
			}
    	}
    	
    	SharedPreferences preference = this.getSharedPreferences();
    	SharedPreferences.Editor editor = preference.edit();
    	editor.putString(TVProgressKey, jsonProgress.toString());
    	editor.commit();
    	this.mProgressDirty = false;
    }
    
    private void restoreSrcHistory() {
    	SharedPreferences preference = this.getSharedPreferences();
    	String jsonStr = preference.getString(TVProgressKey, "{}");
    	try {
			JSONObject jsonProgress = new JSONObject(jsonStr);
			@SuppressWarnings("rawtypes")
			Iterator progressIter = jsonProgress.keys();
			while (progressIter.hasNext()) {
				String channelId = progressIter.next().toString();
				JSONObject jsonProgressItem = jsonProgress.getJSONObject(channelId);
				ProgressHistory progress = new ProgressHistory();
				progress.ProgramId = jsonProgressItem.getInt(ProgramIdKey);
				progress.Position = jsonProgressItem.getInt(PositionKey);
				JSONObject jsonSrcs = jsonProgressItem.getJSONObject(SourcesKey);
				@SuppressWarnings("rawtypes")
				Iterator srcIter = jsonSrcs.keys();
				while (srcIter.hasNext()) {
					String programId = srcIter.next().toString();
					String sourceId = jsonSrcs.getString(programId);
					progress.SourceInfo.put(
						Integer.valueOf(programId),
						Integer.valueOf(sourceId)
					);
				}
				this.mProgressHistory.put(Integer.valueOf(channelId), progress);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
    }
    
    private void restoreProgramIdx() {
    	TVChannel chn = this.getSelChannel();
    	if (null == this.mPrograms || null == chn) {
    		return;
    	}
		if (this.mProgressHistory.indexOfKey(chn.getId()) < 0) {
			return;
		}
		ProgressHistory history = this.mProgressHistory.get(chn.getId());
		if (history != null) {
			for (int i = 0; i < this.mPrograms.length; ++i) {
				if (history.ProgramId == this.mPrograms[i].getId()) {
					this.mSelPrgIdx = i;
					break;
				}
			}
		}
    }
    
    private void reorderSource() {
    	TVChannel chn = this.getSelChannel();
    	TVProgram prg = this.getSelProgram();
    	if (null == this.mSources || null == chn || null == prg) {
    		return;
    	}
		if (this.mProgressHistory.indexOfKey(chn.getId()) < 0) {
			return;
		}
		// FIXME 删除失效频道相关的数据，防止历史记录数据越来越多
		ProgressHistory history = this.mProgressHistory.get(chn.getId());
		if (history != null && history.SourceInfo.indexOfKey(prg.getId()) >= 0) {
			int srcId = history.SourceInfo.get(prg.getId());
			for (int i = 0; i < this.mSources.length; ++i) {
				if (srcId == this.mSources[i].getId()) {
					this.mSelSrcIdx = i;
					break;
				}
			}
			if (this.mSelSrcIdx != 0) {
				TVSource[] oldSrcs = this.mSources;
				TVSource src = oldSrcs[this.mSelSrcIdx];
				this.mSources = new TVSource[oldSrcs.length];
				int idx = 0;
				this.mSources[idx++] = src;
				for (int i = 0; i < oldSrcs.length; ++i) {
					if (this.mSelSrcIdx != i) {
						this.mSources[idx++] = oldSrcs[i];
					}
				}
				this.mSelSrcIdx = 0;
			}
		}
    }
    
    public void setCurrentTime(int time) {
    	TVChannel chn = this.getSelChannel();
    	TVProgram prg = this.getSelProgram();
    	if (null == prg || null == chn || TVChannel.NET_TURN_NODE != chn.getType()) {
    		return;
    	}
    	
    	if (time > 5000) { // 至少播放5秒后才保存进度
	    	ProgressHistory history = new ProgressHistory();
	    	if (this.mProgressHistory.indexOfKey(chn.getId()) >= 0) {
	    		history = this.mProgressHistory.get(chn.getId());
	    	}
	    	history.ProgramId = prg.getId();
	    	history.Position = time;
	    	this.mProgressHistory.put(chn.getId(), history);
	    	this.mProgressDirty = true;
    	}
    }
    
    public int getCurrentTime() {
    	TVChannel chn = this.getSelChannel();
    	TVProgram prg = this.getSelProgram();
    	if (null == prg || null == chn || TVChannel.NET_TURN_NODE != chn.getType()) {
    		return 0;
    	}

    	if (this.mProgressHistory.indexOfKey(chn.getId()) >= 0) {
    		ProgressHistory history = this.mProgressHistory.get(chn.getId());
    		if (history != null) {
    			return history.Position;
    		}
    	}
    	return 0;
    }

	@Override
	public void onListUpdate() {
		if (null == this.mGroups) {
			this.mChannelInfo = this.buildList();
			this.getGroups();
			this.mUpdateListener.onUpdate(UpdateEvent.GruopsUpdate);
		}
	}
}
