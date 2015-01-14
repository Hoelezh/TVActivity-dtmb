package com.alitech.dvb;

import com.nmp.dvbplayer.tv.data.TVProgram;
import com.nmp.dvbplayer.tv.data.TVSource;

public class DvbProgram extends TVProgram {
	private TVSource mSource;
	
	public DvbProgram(int id, String name) {
		super(id, name);
		this.mSource = null;
	}
	
	public void setSource(TVSource source) {
		this.mSource = source;
	}
	
	public TVSource getSource() {
		return this.mSource;
	}
}
