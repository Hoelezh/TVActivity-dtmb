#ifndef __ALI_DVB_SEARCH_H__
#define __ALI_DVB_SEARCH_H__

typedef struct
{
	int frequency_from;
	int frequency_to;
	int bandwidth;
	int symbol_rate;
	int modulation;
	int nit_search;
	int frontend_type;
	int search_method;
	int FTA_only;
	int program_type;//tv or radio
}ALiDVB_SearchParam;

typedef enum
{
	SEARCH_SUCCESS = 0,
	SEARCH_FAILED = -1,
}ALiDVB_SearchReturnCode;

typedef enum
{
	SEARCH_NOTIFY_PROGRESS,		//!< AS progress: 0-100

	SEARCH_NOTIFY_TP_TUNING,	//!< tuned to this tp for program search
	SEARCH_NOTIFY_TP_LOCK,		//!< tp lock status
	SEARCH_NOTIFY_TP_ADDED,		//!< if lock, add the tp into db
	SEARCH_NOTIFY_TP_FULL,		//!< DB TP full, can not store any TP

	SEARCH_NOTIFY_PROGRAM,			//!< program got, notify AP if need store into db or not.
	SEARCH_NOTIFY_PROGRAM_ADDED,	//!< stored into db & notify AP.
	SEARCH_NOTIFY_PROGRAM_FULL,		//!< DB stofull, can not store any program

	SEARCH_NOTIFY_ASCOMPLETE,		//!< AS complete
	SEARCH_NOTIFY_ASSTOP,           //!< user stop as
	SEARCH_NOTIFY_ERROR,            //!< ERROR Message
} ALiDVB_SearchNotifyType;

typedef enum
{
	SEARCH_METHOD_TP_SCAN,			   //manual scan(dvbc),tp scan (dvbs)
	SEARCH_METHOD_SAT_SCAN, 			   //full scan(dvbc),preset scan (dvbs)
	SEARCH_METHOD_BLIND_SCAN,		   //auto scan (dvbc),blind scan (dvbs)
	SEARCH_METHOD_ACCURATEBLIND_SCAN, //null(dvbc),accurate blind scan (dvbs)
} ALiDVB_SearchMethod;
typedef int(* ALiDVB_SearchNotifyFn)(int type, void *param);

int ALiDVB_SearchStart(ALiDVB_SearchParam *param, ALiDVB_SearchNotifyFn callback);
int ALiDVB_SearchStop(void);

#endif /* __ALI_DVB_SEARCH_H__ */

