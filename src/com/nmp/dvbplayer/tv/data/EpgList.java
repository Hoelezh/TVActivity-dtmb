package com.nmp.dvbplayer.tv.data;

public interface EpgList {
	public enum LangCode {
		English,
		Chinese,
		Unknown
	};
	
	public LangCode[] getLanguages();
	
	public EpgItem[] getEpg(int time, TVChannel channel, LangCode code);

	public EpgItem[] getCurrentEpg(TVChannel channel, LangCode code);

}