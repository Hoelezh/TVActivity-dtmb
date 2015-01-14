#ifndef _ALI_GPIO_H_
#define _ALI_GPIO_H_

#if defined(CONFIG_ARM)
	#define ALI_SOC_BASE	0x18000000
	#include <linux/ali_reg.h>
#elif defined(CONFIG_MIPS)
	#define ALI_SOC_BASE	0xb8000000
	#define __REGALIRAW(x)        (x)
#endif

#define GPIO_GROUP_MAX	    5
#define GPIO_PORT_MAX		159


extern bool gpio_is_valid(int gpio);
extern int gpio_request(unsigned gpio, const char *label);
extern void gpio_free(unsigned gpio);

extern int gpio_direction_input(unsigned gpio);
extern int gpio_direction_output(unsigned gpio, int value);
extern int gpio_get_value(unsigned gpio);
extern int gpio_set_value(unsigned gpio, int value);
extern int gpio_get_interrupt_status(unsigned gpio);
extern int gpio_clear_interrupt_status(unsigned gpio);
extern int gpio_interrupt_enable(unsigned gpio,int rise_en, int fall_en);
extern int gpio_interrupt_disable(unsigned gpio);


#endif /* _ALI_GPIO_H_ */
