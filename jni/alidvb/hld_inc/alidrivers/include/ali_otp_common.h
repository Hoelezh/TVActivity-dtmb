#ifndef _ALI_OTP_COMMON_H
#define _ALI_OTP_COMMON_H 

#define MAX_ALI_OTP_PARAS 0x80
struct otp_read_paras {
    unsigned long offset;
    unsigned char *buf;
    int len;
};                    

struct otp_write_paras {
    unsigned char *buf;
    unsigned long offset;
    int len;
};  

#define ALI_OTP_READ  _IOR('S', 1, struct otp_read_paras)
#define ALI_OTP_WRITE _IOW('S', 2, struct otp_write_paras)

int ali_otp_read(unsigned long offset, unsigned char *buf, int len);
int ali_otp_write(unsigned char *buf, unsigned long offset, int len);
int ali_otp_hw_init(void);

unsigned int otp_get_value(unsigned int addr);
unsigned int otp_get_control(void);

#define ENABLE   1
#define DISABLE  0
unsigned int is_otp_uart_enable(void); // if enable return 1, else return 0 ;
unsigned int is_otp_usb_enable(void);
unsigned int is_otp_ethernet_enable(void);

#endif 
