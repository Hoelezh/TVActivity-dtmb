package com.nmp.dvbplayer.tv.data;

public abstract class ChannelList {
	public interface UpdateListener {
		public void onListUpdate();
	};
	
	protected UpdateListener mListener;
	
	public ChannelList() {
		this.mListener = null;
	}
	
	public void setUpdateListener(UpdateListener listener) {
		this.mListener = listener;
	}
	
	public void destroy() { }
	
	public abstract TVGroup[] getGroups();
	
	public abstract TVChannel[] getChannels(TVGroup group);
	
	public abstract TVProgram[] getPrograms(TVChannel channel);
	
	public abstract TVSource[] getSources(TVProgram program);
	
	public abstract String getType();
}