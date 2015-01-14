/****************************************************************************(I)(S)
 *  (C)
 *  ALi (Shanghai) Corporation, All Rights Reserved. 2010 Copyright (C)
 *  (C)
 *  File: ali_pe.h
 *  (I)
 *  Description: ali play engine header for media player library
 *  (S)
 *  History:(M)
 *      	Date        			Author         	Comment
 *      	====        			======		=======
 * 0.		2010.05.31				Sam		Create
 ****************************************************************************/

#ifndef __ALI_PE_COMMON_H
#define __ALI_PE_COMMON_H

/* io commands for PE driver */
/* misc control */
#define ALIPEIO_MISC_BASE_KERNEL							(0x00006000)
#define ALIPEIO_MISC_TRANSPORT_ID					(ALIPEIO_MISC_BASE_KERNEL + 0)
#define ALIPEIO_MISC_SET_FILE_SIZE					(ALIPEIO_MISC_BASE_KERNEL + 1)
#define ALIPEIO_MISC_PAUSE_MODULE					(ALIPEIO_MISC_BASE_KERNEL + 2)
#define ALIPEIO_MISC_RESUME_MODULE				(ALIPEIO_MISC_BASE_KERNEL + 3)
#define ALIPEIO_MISC_RPC_OPERATION				(ALIPEIO_MISC_BASE_KERNEL + 4)
#define ALIPEIO_MISC_SELECT_CACHE					(ALIPEIO_MISC_BASE_KERNEL + 5)
#define ALIPEIO_MISC_GET_FREE_CACHE				(ALIPEIO_MISC_BASE_KERNEL + 6)
#define ALIPEIO_MISC_FREE_CACHE					(ALIPEIO_MISC_BASE_KERNEL + 7)
#define ALIPEIO_MISC_GET_PE_MEM_INFO				(ALIPEIO_MISC_BASE_KERNEL + 8)

/* ALIPEIO_MISC_RPC_OPERATION :
it do Remote Process Call operation to the pe engine */
/* RPC API type definition */
#define RPC_IMAGE				1
#define RPC_MUSIC				2
#define RPC_VIDEO				3

/* ALIPEIO_MISC_GET_PE_MEM_INFO */
struct ali_pe_mem_info
{
	void *mem_start;
	unsigned long mem_size;
};

/* IMAGE RPC API index definition */
#define RPC_IMAGE_ENGINE_INIT					1
#define RPC_IMAGE_ENGINE_CLEANUP				2
#define RPC_IMAGE_ENGINE_ROTATE				3
#define RPC_IMAGE_ENGINE_DECODE				4
#define RPC_IMAGE_ENGINE_SHOW				5
#define RPC_IMAGE_ENGINE_ABOUT				6
#define RPC_IMAGE_ENGINE_ZOOM					7
#define RPC_IMAGE_ENGINE_GET_INFO			8
#define RPC_IMAGE_ENGINE_IOCTL				9

/* MUISC RPC API index definition */
#define RPC_MUSIC_ENGINE_INIT					1
#define RPC_MUSIC_ENGINE_RELEASE				2
#define RPC_MUSIC_ENGINE_PLAY					3
#define RPC_MUSIC_ENGINE_SEEK					4
#define RPC_MUSIC_ENGINE_STOP					5
#define RPC_MUSIC_ENGINE_PAUSE				6
#define RPC_MUSIC_ENGINE_GET_TIME				7
#define RPC_MUSIC_ENGINE_SET_EQ				8
#define RPC_MUSIC_ENGINE_GET_SONG_INFO		9
#define RPC_MUSIC_ENGINE_GET_DECODER_INFO	10

/* VIDEO RPC API index defintion */
#define RPC_VIDEO_ENGINE_INIT					1
#define RPC_VIDEO_ENGINE_DECODE				2
#define RPC_VIDEO_ENGINE_SET_OUT				3
#define RPC_VIDEO_ENGINE_PLAY					4
#define RPC_VIDEO_ENGINE_PAUSE				5
#define RPC_VIDEO_ENGINE_RESUME				6
#define RPC_VIDEO_ENGINE_FF					7
#define RPC_VIDEO_ENGINE_FB					8
#define RPC_VIDEO_ENGINE_SLOW					9
#define RPC_VIDEO_ENGINE_STOP					10
#define RPC_VIDEO_ENGINE_SEARCH				11
#define RPC_VIDEO_ENGINE_CHANGE_AUDIO_TRACK 12
#define RPC_VIDEO_ENGINE_CHANGE_PROG			13
#define RPC_VIDEO_ENGINE_GET_STREAM_INFO	14
#define RPC_VIDEO_ENGINE_GET_PLAY_TIME		15
#define RPC_VIDEO_ENGINE_GET_TOTAL_TIME		16
#define RPC_VIDEO_ENGINE_RELEASE_CACHE		17

#define MAX_PE_RPC_ARG_NUM		4

#define MAX_PE_RPC_ARG_SIZE		512

struct ali_pe_rpc_arg
{
	void *arg;
	int arg_size;
	int out;
};

struct ali_pe_rpc_pars
{
	int type;
	int API_ID;
	struct ali_pe_rpc_arg arg[MAX_PE_RPC_ARG_NUM];
	int arg_num;
};

/*
pe message is used by the application to communicate with this module. it is transfered by netlink.
the arrangement of the message is as below:
1st byte : type --> the message is from cache , image, music or video
2nd byte : command type or null value
3rd byte : size of the command data
4 ~ xx byte: command data. the size of this data is decided by 3rd byte value
*/
/* message type */
#define ALIPE_MSG_CACHE							1
#define ALIPE_MSG_IMAGE							2
#define ALIPE_MSG_MUSIC							3
#define ALIPE_MSG_VIDEO							4

/* command type of cache */
#define ALIPE_CACHE_OPEN							1
#define ALIPE_CACHE_CLOSE							2
#define ALIPE_CACHE_SEEK							3
#define ALIPE_CACHE_REQ_NEW_DATA					4

#endif

