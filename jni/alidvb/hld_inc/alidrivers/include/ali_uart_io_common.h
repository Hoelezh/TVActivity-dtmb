#ifndef _ALI_UART_COMMON_H_
#define _ALI_UART_COMMON_H_

#include <linux/types.h>

struct uart_pars
{
    unsigned long tm;
	unsigned char ch;
};


#define ALI_UART_IO_READ 	 _IOR('U', 1, __u8)
#define ALI_UART_IO_READ_TM  _IOWR('U',2, __u32)
#define ALI_UART_IO_WRITE	 _IOW('U', 3, __u8)
#define ALI_UART_IO_SET      _IOW('U', 4, __u32)
#define ALI_UART_DISABLE     _IOW('U', 5, __u8)
#define ALI_UART_ENABLE      _IOW('U', 6, __u8)
#define ALI_UART_IO_READ_TIMEOUT  _IOWR('U', 7, __u32 )
#define ALI_UART_IO_CLEAR_SCI     _IOW('U', 8, __u32 )
#define ALI_UART_IO_SET_SCI       _IOW('U', 9, __u32 )
/* Keep backward compartibility with IBU SDK
*/
#define ALI_UART_SFU_MODE	_IOW('U', 10, __u8)


#endif
