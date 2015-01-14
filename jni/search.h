#ifndef _Included_search
#define _Included_search

struct DvbSearchParam {
	int frq_from;
	int frq_to;
	int bandwidth;
	int sym;
	int qam;
	int nit_search;
	int frontend_type;
};


typedef int(* search_notify_t)(int type, void *param);

int search_register(search_notify_t callback);
int search_unregister();

int search_start(struct DvbSearchParam *param);
int search_stop();

#endif // _Included_search
