#ifndef _ALI_IR_COMMON_H_
#define _ALI_IR_COMMON_H_

/* ALI25C01 key code, 60keys & ali new RC */
#define IR_ALI01_HKEY_0			0x60df926d
#define IR_ALI01_HKEY_1			0x60dfc837
#define IR_ALI01_HKEY_2			0x60df08f7
#define IR_ALI01_HKEY_3			0x60df8877
#define IR_ALI01_HKEY_4			0x60dff00f
#define IR_ALI01_HKEY_5			0x60df30cf
#define IR_ALI01_HKEY_6			0x60dfb04f
#define IR_ALI01_HKEY_7			0x60dfd02f
#define IR_ALI01_HKEY_8			0x60df10ef
#define IR_ALI01_HKEY_9			0x60df906f

#define IR_ALI01_HKEY_LEFT		0x60df38c7
#define IR_ALI01_HKEY_RIGHT	0x60df12ed
#define IR_ALI01_HKEY_UP		0x60df22dd
#define IR_ALI01_HKEY_DOWN	0x60dfb847

#define IR_ALI01_HKEY_V_UP		0x60df48b7//0x60df12ed
#define IR_ALI01_HKEY_V_DOWN	0x60df01fe//0x60df38c7
//no channel key, use pre ,next
#define IR_ALI01_HKEY_C_UP		0x60df20df
#define IR_ALI01_HKEY_C_DOWN	0x60df0af5

#define IR_ALI01_HKEY_ENTER	0x60df3ac5
#define IR_ALI01_HKEY_P_UP		0x60dfd22d
#define IR_ALI01_HKEY_P_DOWN	0x60dfe01f

#define IR_ALI01_HKEY_TEXT		0x60df827d
#define IR_ALI01_HKEY_POWER	0x60df708f
#define IR_ALI01_HKEY_PREV		0x60df20df
#define IR_ALI01_HKEY_NEXT		0x60df0af5

#define IR_ALI01_HKEY_AUDIO	0x60df629d

#define IR_ALI01_HKEY_SUBTITLE	0x60df807f


//MP(60key RC)
#define IR_ALI01_HKEY_NEWS		0x60df50af
//SLEEP(60key RC)
#define IR_ALI01_HKEY_VOD		0x60df9867
//PIP(60key RC)
#define IR_ALI01_HKEY_MAIL		0x60df6a95
#define IR_ALI01_HKEY_LOCALPLAY	    0x60df7887	

#define IR_ALI01_HKEY_FIND		0x60dfe21d
#define IR_ALI01_HKEY_MUTE		0x60dfa05f
#define IR_ALI01_HKEY_PAUSE	0x60df7a85
#define IR_ALI01_HKEY_INFOR	0x60df6897
#define IR_ALI01_HKEY_EXIT		0x60df42bd
#define IR_ALI01_HKEY_TVSAT	0x60df52ad
#define IR_ALI01_HKEY_TVRADIO	0x60df02fd
#define IR_ALI01_HKEY_FAV		0x60dfc23d
#define IR_ALI01_HKEY_ZOOM		0x60df40bf
#define IR_ALI01_HKEY_EPG		0x60df00ff
#define IR_ALI01_HKEY_MENU		0x60df2ad5
#define IR_ALI01_HKEY_RECALL	0x60dfc03f

#define IR_ALI01_HKEY_RED		0x60df609f
#define IR_ALI01_HKEY_GREEN	0x60df7887
#define IR_ALI01_HKEY_YELLOW	0x60dff807
#define IR_ALI01_HKEY_BLUE		0x60dfba45

#define IR_ALI01_HKEY_V_FORMAT 0x60dfa25d
#define IR_ALI01_HKEY_PLAY		0x60df18e7
#define IR_ALI01_HKEY_STOP		0x60dfe817	

#define IR_ALI01_HKEY_RECORD        0x60dfa857
#define IR_ALI01_HKEY_PVR_INFO		0x60dfca35	
#define IR_ALI01_HKEY_FILELIST		0x60dfb24d	
#define IR_ALI01_HKEY_DVRLIST		0x60df8a75	
#define IR_ALI01_HKEY_USBREMOVE	0x60df1ae5	
#define IR_ALI01_HKEY_PIP_LIST		0x60df9a65	
#define IR_ALI01_HKEY_SWAP			0x60df5aa5	
#define IR_ALI01_HKEY_MOVE			0x60dfda25	
#define IR_ALI01_HKEY_REPEATAB		0x60dfea15	
#define IR_ALI01_HKEY_FB			0x60df58a7	
#define IR_ALI01_HKEY_FF		    0x60dfd827
#define IR_ALI01_HKEY_SLOW  	0x60dfaa55
#define IR_ALI01_HKEY_B_SLOW  0x60df4ab5


/*this struct is for config pan driver, it tells the map between H_KEY code and linux defined keys*/
struct linux_ir_key_map_t
{
	unsigned long ir_code;
	unsigned short key;
};


#endif /*_ALI_IR_COMMON_H_*/
