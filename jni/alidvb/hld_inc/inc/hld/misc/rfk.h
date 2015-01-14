/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2010 Copyright (C)
 *  (C)
 *  File: rfk.c
 *  (I)
 *  Description: receive message from kenel
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2010.06.18			Sam			Create
 ****************************************************************************/
 
#ifndef __MISC_RFK_H__
#define __MISC_RFK_H__

#ifdef __cplusplus
extern "C" {
#endif


#include <sys/socket.h>
#include <linux/netlink.h>

#define MAX_RFK_MSG_SIZE			1024
#define MAX_RFK_PORT_NUM			1000

struct rfk_dev{
	int busy;
	int sock_id;
	int port_id;
	
	struct nlmsghdr *nlmsghdr;		
	struct sockaddr_nl saddr;
	struct sockaddr_nl daddr;	
	struct msghdr msg;
	struct iovec iov;		
};

void rfk_free_port(int port_id);
void rfk_init(void);
void rfk_exit(void);
int rfk_get_socket(int port_id);
int rfk_get_port(void);
unsigned char *rfk_receive_msg(int port_id);

#ifdef __cplusplus
}
#endif

#endif

