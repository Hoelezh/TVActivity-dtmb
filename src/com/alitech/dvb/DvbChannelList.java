package com.alitech.dvb;

import java.util.ArrayList;

import android.content.Context;
import android.content.res.Resources;
import android.util.SparseArray;

import com.nmp.dvbplayer.tv.data.ChannelList;
import com.nmp.dvbplayer.tv.data.TVChannel;
import com.nmp.dvbplayer.tv.data.TVGroup;
import com.nmp.dvbplayer.tv.data.TVProgram;
import com.nmp.dvbplayer.tv.data.TVSource;
import com.nmp.dvbplayer.R;

public class DvbChannelList extends ChannelList {
	private static final int GroupType[] = { 
		DvbChannel.CHAN_GROUP_ALL | DvbChannel.CHAN_MODE_TV,
		DvbChannel.CHAN_GROUP_ALL | DvbChannel.CHAN_MODE_RADIO
	};	
	public static SparseArray<DvbChannelNode[]> DvbChannels;
	static {
		DvbChannels = new SparseArray<DvbChannelNode[]>();
	};
	
	private Context           mContext;
	private ArrayList<String> mGrpNames;
	
	public DvbChannelList(Context ctx) {
		super();
		this.mContext = ctx;
		Resources res = this.mContext.getResources();
		this.mGrpNames = new ArrayList<String>();
		this.mGrpNames.add(res.getString(R.string.tv_chn_tv));
		this.mGrpNames.add(res.getString(R.string.tv_chn_radio));
	}

	@Override
	public TVGroup[] getGroups() {
		int size = GroupType.length;
		if (DvbChannels.size() < 1) {
			boolean allNull = true;
			for (int i = 0; i < size; ++i) {
				DvbChannelNode[] nodes = null;
				nodes = DvbChannel.loadChannels(GroupType[i]);
				DvbChannels.put(i, nodes);
				if (nodes != null) {
					allNull = false;
					for (DvbChannelNode node : nodes) {
						node.genNewId();
					}
				}
			}
			if (allNull) {
				DvbChannels.clear();
			}
		}
		if (DvbChannels.size() < 1) {
			return null;
		}
		
		TVGroup[] groups = new TVGroup[size];
		for (int i = 0; i < size; ++i) {
			groups[i] = new TVGroup(i, this.mGrpNames.get(i));
		}
		
		return groups;
	}

	@Override
	public TVChannel[] getChannels(TVGroup group) {
		return DvbChannels.get(group.getId());
	}

	@Override
	public TVProgram[] getPrograms(TVChannel channel) {
		TVProgram[] programs = null;
		if (channel instanceof DvbChannelNode) {
			int chnId = channel.getId();
			String chnName = channel.getName();
			DvbProgram program = new DvbProgram(chnId, chnName);
			
			String url = DvbChannelNode.toUrl((DvbChannelNode)channel);
			TVSource source = new TVSource(chnId, chnName, url);
			program.setSource(source);
			
			programs = new TVProgram[1];
			programs[0] = program;
		}	
		return programs;
	}

	@Override
	public TVSource[] getSources(TVProgram program) {
		TVSource[] sources = null;
		if (program instanceof DvbProgram) {
			DvbProgram prg = (DvbProgram) program;
			sources = new TVSource[1];
			sources[0] = prg.getSource();
		}
		return sources;
	}

	@Override
	public String getType() {
		return "DVB";
	}
}
