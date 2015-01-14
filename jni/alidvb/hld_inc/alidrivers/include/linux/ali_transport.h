/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2010 Copyright (C)
 *  (C)
 *  File: ali_transport.h
 *  (I)
 *  Description: ali transport driver helps to the communication between kernel 
 *			  and user space. it is build by the netlink
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2010.06.11				Sam		Create
 ****************************************************************************/

 #ifndef __ALI_TRANSPORT_H
#define __ALI_TRANSPORT_H

#define MAX_TRANSPORT_MSG_SIZE			1024
#define MAX_TRANSPORT_PORT_NUM			1000

int ali_transport_send_msg(int port_id, void *msg_buf, int msg_size);

#endif

