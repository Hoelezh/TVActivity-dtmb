
#ifndef _ALI_TEST_H_
#define _ALI_TEST_H_

#include <linux/types.h>

#ifndef SUCCESS
#define SUCCESS     	0x0000
#define UNSUCCESS     	0xFFFF
#endif

#define 	ALI_TEST_IOC_MAGIC  0xA5
#define 	MAX_BW_GROUP 		20 //18 //20
#define 	MAX_SINGLE_IP_IDX 	34		
#define 	MAX_IP_IDX 			(MAX_SINGLE_IP_IDX+1)


/* Used to config the monitered IP info */
struct test_ip_bw_cfg_info
{
     __u16 	time_gap;						  //the time gap to caculate IP bandwidth

     __u8 	ip_mode; 						  //choose the Total_IP_BW and Single_IP_BW mode; 
     										  //0, for Total_IP;1, for Single_IP 2, Both for Total_IP and Single_IP 
     __u32 	ip_enable_flag;					  //Enable the Single IP to be monitor (IP0~IP33);0, not be monitored; 1, be monitored

	 __u32 	ip_enable_flag_add;
};

/* Storage the materials to calculate BW */
struct test_ip_tmp_info
{
	__u32	ip_total_value[MAX_BW_GROUP];	  //The Theory Byte when calculate the total IP BW of two channels
											  //Only use to calc total IP BW with one DDR Channel
											  //If use two DDR channel, Please don't refer the param to calculate total BW directly

    __u32   ip_total_value_0[MAX_BW_GROUP];   //The Theory Byte when calculate the total IP BW of the first channel
                                              //Only use to calc total IP BW

    __u32   ip_total_value_1[MAX_BW_GROUP];   //The Theory Byte when calculate the total IP BW of the second channel
                                              //Only use to calc total IP BW
											
	__u32	ip_real_value[MAX_BW_GROUP];	  //The R/W Bytes of two channels
											  //Only use to calc total IP BW with one DDR Channel
											  //If use two DDR channel, Please don't refer the param  to calculate total BW directly

    __u32	ip_real_value_0[MAX_BW_GROUP];	  //The R/W Bytes of the first channel

    __u32	ip_real_value_1[MAX_BW_GROUP];	  //The R/W Bytes of the second channel
										
    __u32	ip_bw_jiff[MAX_BW_GROUP];		  //Save the MAX_BW_GROUP groups of jiff to the IP BW	

    __u32	ip_bw_time_gap[MAX_BW_GROUP];	  //The real time tag to caculate the single IP BW
    										  //The Real R/W Byte when calculate the total IP BW 
};


/*Transferd to user the bw info*/
struct test_ip_bw_info
{
	__u32	ip_bw_value[MAX_BW_GROUP];		 //Save the MAX_BW_GROUP groups of IP BW; Unit is KBps

	__u32	ip_bw_value_0[MAX_BW_GROUP];	 //Save the MAX_BW_GROUP groups of IP BW of the first chanel; Unit is KBps

	__u32	ip_bw_value_1[MAX_BW_GROUP];	 //Save the MAX_BW_GROUP groups of IP BW of the second channel; Unit is KBps

    __u32	ip_bw_jiff[MAX_BW_GROUP];		 //Save the MAX_BW_GROUP groups of jiff to the IP BW; Unit is ms	

    __u32	ip_bw_time_gap[MAX_BW_GROUP];	 //The real time tag to caculate the single IP BW; Unit is ms
};

struct test_ip_get_bw
{
	__u8 	ip_mode;						//choose the Total_IP_BW and Single_IP_BW mode; 0, for Total_IP;1, for Single_IP
											//2, Both for Total_IP and Single_IP 

	__u8	ip_chan_mode;					//choose the IP_BW for different channel 
											//0, for Total value of the IP BW of the two channel; Don't show IP BW of single channel
											//1, for Total value of the IP BW of the two channel; show IP BW of two channels
											//2, for Total value of the IP BW of the two channel; and show IP BW of the first channel only.
											//3, for Total value of the IP BW of the two channel; and show IP BW of the second channel only

	__u16	ip_bw_cnt; 
											//Count the valid number of IP BW
											
	__u32 	ip_idx_flag;					//Enable the Single IP to get BW value through (IP0~IP33);
    __u32 	ip_idx_flag_add; 					//0, disabled to get bw; 1, enabled to get bw
										
	struct 	test_ip_bw_info bw_info[MAX_IP_IDX];	//Buffer to Save the related info about BW:
							      					//bw_info[0]: Save the info about Total BW
							      					//bw_info[1]~bw_info[34]: Save the Bw info about single IP from IP_0 to IP_33
};



#define ALI_TEST_IP_TASK_START 		_IO(ALI_TEST_IOC_MAGIC, 11)

#define ALI_TEST_IP_TASK_STOP  		_IO(ALI_TEST_IOC_MAGIC, 12 )
	
#define ALI_TEST_IP_TASK_PAUSE 		_IO(ALI_TEST_IOC_MAGIC, 13)

#define ALI_TEST_IP_TASK_RESUME  	_IO(ALI_TEST_IOC_MAGIC, 14 )

#define ALI_TEST_IP_BW_CONFIG  		_IOW(ALI_TEST_IOC_MAGIC, 15 , struct test_ip_bw_cfg_info)
	
#define ALI_TEST_IP_BW_GET  		_IOWR(ALI_TEST_IOC_MAGIC, 16 , struct test_ip_get_bw)


#endif


