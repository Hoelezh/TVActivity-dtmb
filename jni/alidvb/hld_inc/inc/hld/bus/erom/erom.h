#ifndef _EROM_H_
#define _EROM_H_

#ifdef __cplusplus
extern "C" {
#endif

enum erom_sync_mode {
	DUPLEX_MODE ,
	SIMPLEX_MODE
};


int erom_sync(unsigned long sync_tmo, unsigned int simplex_mode);
int erom_rw(unsigned long mem_addr, void *buf, \
	 unsigned long len, unsigned int block_mode, unsigned int is_read);
int erom_read_tmo( unsigned long mem_addr, void *buf,unsigned long len,\
		 unsigned int block_mode, unsigned long tmo_us);
int erom_setpc(unsigned long new_pc);

void erom_enter(unsigned int waitforever);
 
#define erom_rm(a,b,c,d)  erom_rw(a,b,c,d,1)
#define erom_wm(a,b,c,d)  erom_rw(a,b,c,d,0)

#ifdef __cplusplus
}
#endif

#endif	/*_EROM_H_*/
