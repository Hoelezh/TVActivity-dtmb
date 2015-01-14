package com.alitech.dvb;

import java.util.zip.CRC32;

import com.nmp.dvbplayer.tv.data.TVChannel;

import android.util.Log;

public class DvbChannelNode extends TVChannel {
	private static final String TAG = "DvbChannelNode";
	
	public static final int SERVICE_TYPE_DTV		        = 0x01;
	public static final int SERVICE_TYPE_DRADIO	            = 0x02;
	public static final int SERVICE_TYPE_TELTEXT		    = 0x03;
	public static final int SERVICE_TYPE_NVOD_REF		    = 0x04;
	public static final int SERVICE_TYPE_NVOD_TS		    = 0x05;
	public static final int SERVICE_TYPE_MOSAIC		        = 0x06;
	public static final int SERVICE_TYPE_FMRADIO	    	= 0x07;
	//advanced codec digital radio sound service
	public static final int SERVICE_TYPE_ACDRADIO		    = 0x0a;
	public static final int SERVICE_TYPE_DATABROAD          = 0x0C;
	public static final int SERVICE_TYPE_HD_MPEG2 		    = 0x11;
	public static final int SERVICE_TYPE_SD_MPEG4           = 0x16;
	public static final int SERVICE_TYPE_NVOD_TS_SD_MPEG4   = 0x17;
	public static final int SERVICE_TYPE_NVOD_REF_SD_MPEG4	= 0x18;
	public static final int SERVICE_TYPE_HD_MPEG4           = 0x19;
	public static final int SERVICE_TYPE_NVOD_TS_HD_MPEG4	= 0x1A;
	public static final int SERVICE_TYPE_NVOD_REF_HD_MPEG4	= 0x1B;
	public static final int SERVICE_TYPE_USER_DEFINED		= 0x80;
	public static final int SERVICE_TYPE_DATA_SERVICE       = 0xC0;
    //private defined advertise service
	public static final int SERVICE_TYPE_PRIVATE            = 0xFE;

	public static class DvbFrontend {	
		private int mType; // FRONTEND_TYPE_S，FRONTEND_TYPE_C，FRONTEND_TYPE_T
		private int mQam;
		private int mFrequency;
		private int mSymbolRate;

		public DvbFrontend(int type, int qam, int frq, int sym) {
			this.mType = type;
			this.mQam = qam;
			this.mFrequency = frq;
			this.mSymbolRate = sym;
		}

		public int getType() {
			return this.mType;
		}

		public int getQam() {
			return this.mQam;
		}
		
		public int getFrequency() {
			return this.mFrequency;
		}
		
		public int getSymbolRate() {
			return this.mSymbolRate;
		}
		
		public static native int setFrontend(DvbFrontend xpond, int timeout);
	}
	
	static class DvbPcr {
		private short mPcrPid;
		
		public DvbPcr(short pcrPid) {
			this.mPcrPid = pcrPid;
		}
		
		public short getPcrPid() {
			return this.mPcrPid;
		}			
	}	
	
	static class DvbVideo {
		private short mVideoType; // MPEG2_VIDEO_STREAM,H264_VIDEO_STREAM,AVS_VIDEO_STREAM...
		private short mVideoPid;	
		
		public DvbVideo(short videoType, short videoPid) {
			this.mVideoType = videoType;
			this.mVideoPid = videoPid;
		}
		
		public short getVideoType() {
			return this.mVideoType;
		}	

		public short getVideoPid() {
			return this.mVideoPid;
		}	
	}
	

	static class DvbAudio {
		static class DvbAudioTrack {
			private short mAudioPid;
			private short mAudioType;	// AUDIO_AC3, AUDIO_MPEG_AAC, AUDIO_MPEG2...
			private String mAudioLang;

			public DvbAudioTrack(short audioPid, short audioType, String audioLang) {
				this.mAudioPid = audioPid;
				this.mAudioType = audioType;
				this.mAudioLang = audioLang;
			}
			
			public short getAudioPid() {
				return this.mAudioPid;
			}
			
			public short getAudioType() {
				return this.mAudioType;
			}

			public String getAudioLang() {
				return this.mAudioLang;
			}
		}
		
		private short mAudioChannel; // LEFT, RIGHT, STEREO, MONO
		private short mAudioVolume;	
		private short mAudioTrackIdx;
		private DvbAudioTrack[] mAudioTrack;

		public DvbAudio(short channel, short volume, short trackIdx, DvbAudioTrack[] tracks) {
			this.mAudioChannel = channel;
			this.mAudioVolume = volume;
			this.mAudioTrackIdx = trackIdx;
			this.mAudioTrack = tracks;
		}
		
		public short getAudioChannel() {
			return this.mAudioChannel;
		}	

		public short getAudioVolume() {
			return this.mAudioVolume;
		}
			
		public short getAudioTrackIdx() {
			return this.mAudioTrackIdx;
		}
		
		public DvbAudioTrack[] getAudioTrack() {
			return this.mAudioTrack;
		}	
	}
		
	static class DvbBouquet {
		private short[] mBouquetId; // 分组的bouquet id 	

		public DvbBouquet(short[] bouquetId) {
			this.mBouquetId = bouquetId;
		}

		public short[] getBouquetId() {
			return this.mBouquetId;
		}
	}

	DvbFrontend mFrontend;
	DvbPcr mPcr;
	DvbVideo mVideo;
	DvbAudio mAudio;
	DvbBouquet mBouquet;
	
	private int mTpId;
	private int mServiceId;
	private int mServiceType; // RADIO/TV/RADIOTV/DATA/NVOD

	private boolean mScramble; // scramble channel
	private boolean mLock; // parent lock	

	public DvbChannelNode(int progId, String name, String number)
	{		
		super(progId, name, number);
	}
	
	public DvbChannelNode(int progId, String name, String number, 
			DvbFrontend frontend, DvbPcr pcr, DvbVideo video, DvbAudio audio, 
			DvbBouquet bouquet,	int tpId, int serviceId, int serviceType,
			boolean scramble, boolean lock, boolean favorite) {
		
		super(progId, name, number);
		
		this.setFavorite(false);		
		this.mFrontend = frontend;
		this.mPcr = pcr;
		this.mVideo = video;
		this.mAudio = audio;
		this.mBouquet = bouquet;
		
		this.mTpId = tpId;
		this.mServiceId = serviceId;
		this.mServiceType = serviceType;
		this.setChnType(this.mServiceType);

		this.mScramble = scramble;
		this.mLock = lock;				
	}
	
	private void setChnType(int serviceType) {
		int type = TVChannel.DVB_RADIO_MODE;
		if (SERVICE_TYPE_DATABROAD == serviceType) {
			type = TVChannel.DVB_DATA_MODE;
		} else if (SERVICE_TYPE_NVOD_TS == serviceType ||
				SERVICE_TYPE_NVOD_TS_SD_MPEG4 == serviceType ||
				SERVICE_TYPE_NVOD_TS_HD_MPEG4 == serviceType) {
			type = TVChannel.DVB_NVOD_MODE;
		} else if (SERVICE_TYPE_DTV == serviceType ||
				SERVICE_TYPE_HD_MPEG2 == serviceType ||
				SERVICE_TYPE_SD_MPEG4 == serviceType ||
				SERVICE_TYPE_HD_MPEG4 == serviceType) {
			type = TVChannel.DVB_TV_MODE;
		}
		if((this.mVideo.mVideoPid!=8191)&&(type == TVChannel.DVB_RADIO_MODE))
			type = TVChannel.DVB_TV_MODE;
		this.setType(type);
	}

	public int getTpId() {
		return this.mTpId;
	}
	
	public int getServiceId() {
		return this.mServiceId;
	}
	
	public int getServiceType() {
		return this.mServiceType;
	}
	
	public boolean isScrambled() {
		return this.mScramble;
	}

	public void setScramble(boolean flag) {
		this.mScramble = flag;
	}
	
	public boolean isLocked() {
		return this.mLock;
	}

	public void setlock(boolean flag) {
		this.mLock = flag;
	}

	public static String toUrl(DvbChannelNode node) {		
		int audioTrackIdx;
		StringBuffer sb = new StringBuffer(); 
		
		sb.append("Dvb://");

		sb.append("tpId="+node.getTpId());
		sb.append("&frq="+node.mFrontend.getFrequency());
		sb.append("&sym="+node.mFrontend.getSymbolRate());
		sb.append("&qam="+node.mFrontend.getQam());
		sb.append("&progId="+node.getId());
		sb.append("&serviceId="+node.getServiceId());
		sb.append("&serviceType="+node.getServiceType());
		sb.append("&pcrPid="+node.mPcr.getPcrPid());
		sb.append("&videoType="+node.mVideo.getVideoType());
		sb.append("&videoPid="+node.mVideo.getVideoPid());
		sb.append("&audioChannel="+node.mAudio.getAudioChannel());
		sb.append("&audioVolume="+node.mAudio.getAudioVolume());
		
		audioTrackIdx = node.mAudio.getAudioTrackIdx();		
		if (audioTrackIdx < node.mAudio.getAudioTrack().length) {
			sb.append("&audioType="+node.mAudio.getAudioTrack()[audioTrackIdx].getAudioType());
			sb.append("&audioPid="+node.mAudio.getAudioTrack()[audioTrackIdx].getAudioPid());
			sb.append("&audioLang="+node.mAudio.getAudioTrack()[audioTrackIdx].getAudioLang());
		}			
				
		String playUrl = sb.toString();
		Log.d(TAG, playUrl);
		
		return playUrl;
	}
	
	public static DvbChannelNode fromUrl(String playUrl) {
		short audioPid = 0;
		short audioType = 0;
		String audioLang = "";
		short audioChannel = 0;
		short audioVolume = 0;
		short audioTrackIdx = 0;
		short[] bouquetId = new short[0];
		int ftType = 0;
		int ftQam = 0;
		int ftFrequency = 0;
		int ftSymbolRate = 0;
		short pcrPid = 0;
		short videoType = 0;
		short videoPid = 0;
		int progId = 0;
		String name = "";
		String number = "";
		int tpId = 0;
		int serviceId = 0;
		int serviceType = 0;
		boolean scramble = false;
		boolean lock = false;
		boolean favorite = false;
		
		String[] arrSplit = playUrl.replaceAll("Dvb://", "").split("&");
		for (String str : arrSplit) {
			//Log.d(TAG, str);
			String[] param = str.split("=");
			if (param.length != 2) {
				Log.e(TAG,"url format invalid,"+"len "+param.length + ",param[0]:" +param[0]);
				continue;
			}
			
			if (param[0].equals("tpId")) {
				tpId = Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("frq")) {
				ftFrequency = Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("sym")) {
				ftSymbolRate = Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("qam")) {
				ftQam = Integer.parseInt(param[1]); 
			}		
			else if (param[0].equals("progId")) {
				progId = Integer.parseInt(param[1]); 
			}				
			else if (param[0].equals("serviceId")) {
				serviceId = Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("serviceType")) {
				serviceType = Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("pcrPid")) {
				pcrPid = (short)Integer.parseInt(param[1]); 
			}			
			else if (param[0].equals("videoType")) {
				videoType = (short)Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("videoPid")) {
				videoPid = (short)Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("audioChannel")) {
				audioChannel = (short)Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("audioVolume")) {
				audioVolume = (short)Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("audioType")) {
				audioType = (short)Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("audioPid")) {
				audioPid = (short)Integer.parseInt(param[1]); 
			}
			else if (param[0].equals("audioLang")) {
				audioLang = param[1]; 
			}	
		}
		
		/* audio track */	
		DvbAudio.DvbAudioTrack[] trackArr = new DvbAudio.DvbAudioTrack[1];
		trackArr[0] = new DvbAudio.DvbAudioTrack(audioPid, audioType, audioLang);

		/* audio */
		DvbAudio audio = new DvbAudio(audioChannel, audioVolume, audioTrackIdx, trackArr);				

		/* bouquet */		
		DvbBouquet bouquet = new DvbBouquet(bouquetId);		

		/* frontend */		
		DvbFrontend frontend = new DvbFrontend(ftType, ftQam, ftFrequency, ftSymbolRate);
		
		/* pcr */
		DvbPcr pcr = new DvbPcr(pcrPid);

		/* video */		
		DvbVideo video = new DvbVideo(videoType, videoPid);
	
		/* channel node */
		DvbChannelNode node = new DvbChannelNode(progId, name, number, 
					frontend, pcr, video, audio, 
					bouquet, tpId, serviceId, serviceType,
					scramble, lock, favorite);
		
		return node;
	}
	
	public void genNewId() {
		int freq = this.mFrontend.mFrequency;
		String name = this.getName();
		CRC32 crc32 = new CRC32();
		crc32.update(name.getBytes());
		long sum = crc32.getValue() + freq;
		this.setId((int)sum);
	}
	
	public static void printChannelNode(DvbChannelNode node) {
		Log.d(TAG, "start list node "+ node.getNumber());
		Log.d(TAG, "\ttp_id:\t"+node.getTpId());
		Log.d(TAG, "\tprog_id:\t"+node.getId());
		Log.d(TAG, "\tservice_id:\t"+node.getServiceId());
		Log.d(TAG, "\tservice_type:\t"+node.getServiceType());
		Log.d(TAG, "\tservice_name:\t"+node.getName());
		Log.d(TAG, "\tfavorite:\t"+node.isFavorite());
		Log.d(TAG, "\tscramble:\t"+node.isScrambled());
		Log.d(TAG, "\tlock:\t"+node.isLocked());
		Log.d(TAG, "\tfrontend.ft_type:\t"+node.mFrontend.getType());
		Log.d(TAG, "\tfrontend.qam:\t"+node.mFrontend.getQam());
		Log.d(TAG, "\tfrontend.frq:\t"+node.mFrontend.getFrequency());
		Log.d(TAG, "\tfrontend.sym:\t"+node.mFrontend.getSymbolRate());
		Log.d(TAG, "\tpcr.pcr_pid:\t"+node.mPcr.getPcrPid());
		Log.d(TAG, "\tvideo.video_type:\t"+node.mVideo.getVideoType());
		Log.d(TAG, "\tvideo.video_pid:\t"+node.mVideo.getVideoPid());

		Log.d(TAG, "\taudio.audio_channel:\t"+node.mAudio.getAudioChannel());
		Log.d(TAG, "\taudio.audio_volume:\t"+node.mAudio.getAudioVolume());
		Log.d(TAG, "\taudio.audio_current:\t"+node.mAudio.getAudioTrackIdx());
		Log.d(TAG, "\taudio.audio_count:\t"+node.mAudio.getAudioTrack().length);
		int i;
		for (i=0; i<node.mAudio.getAudioTrack().length; i++) {
			Log.d(TAG, "\t\taudio.audio_pid:\t"+node.mAudio.getAudioTrack()[i].getAudioPid());
			Log.d(TAG, "\t\taudio.audio_type:\t"+node.mAudio.getAudioTrack()[i].getAudioType());
			Log.d(TAG, "\t\taudio.audio_lang:\t"+node.mAudio.getAudioTrack()[i].getAudioLang());			
		}

		Log.d(TAG, "\tbouquet.bouquet_count:\t"+node.mBouquet.getBouquetId().length);
		for (i=0; i<node.mBouquet.getBouquetId().length; i++)
			Log.d(TAG, "\tbouquet.bouquet_id:\t"+node.mBouquet.getBouquetId()[i]);	

		Log.d(TAG, "list node"+node.getNumber()+"end");
	}
}
