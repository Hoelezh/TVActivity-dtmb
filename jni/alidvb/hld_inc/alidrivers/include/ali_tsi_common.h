
#ifndef _ALI_TSI_COMMON_H_
#define _ALI_TSI_COMMON_H_

#include <linux/types.h>

enum ali_tsi_input_id
{    
    ALI_TSI_INPUT_SPI_0   = 0x0,
    ALI_TSI_INPUT_SPI_1   = 0x1,

    ALI_TSI_INPUT_TSG     = 0x2,
	ALI_TSI_INPUT_SPI_3   = 0x3,
	
    ALI_TSI_INPUT_SSI_0   = 0x4,
    ALI_TSI_INPUT_SSI_1   = 0x5,

    ALI_TSI_INPUT_PARA    = 0x6,

    ALI_TSI_INPUT_SPI2B_0 = 0x8,
    ALI_TSI_INPUT_SPI2B_1 = 0x9,

    ALI_TSI_INPUT_SPI4B_0 = 0xA,
    ALI_TSI_INPUT_SPI4B_1 = 0xB,

    ALI_TSI_INPUT_SSI_2   = 0xC,
    ALI_TSI_INPUT_SSI_3   = 0xD,

    ALI_TSI_INPUT_SPI2B_2 = 0xE,
    ALI_TSI_INPUT_SPI2B_3 = 0xF,

    ALI_TSI_INPUT_SPI4B_2 = 0x10,
    ALI_TSI_INPUT_SPI4B_3 = 0x11,
	
};

enum ali_tsi_channel_id
{
    ALI_TSI_CHANNEL_0,

    ALI_TSI_CHANNEL_1,

    ALI_TSI_CHANNEL_2,

    ALI_TSI_CHANNEL_3,

    
};


enum ali_tsi_output_id
{
    ALI_TSI_OUTPUT_DMX_0,

    ALI_TSI_OUTPUT_DMX_1,
    
    ALI_TSI_OUTPUT_DMX_2,

    ALI_TSI_OUTPUT_DMX_3,    
};


enum ali_tsi_ci_id
{
    ALI_TSI_CI_0,

    ALI_TSI_CI_1,
};

enum ali_tsi_ci_link_mode
{
    ALI_TSI_CI_LINK_CHAIN,

    ALI_TSI_CI_LINK_PARALLEL,
};

struct ali_tsi_input_set_param
{
    enum ali_tsi_input_id id;

    __u32 attribute;
};


struct ali_tsi_channel_set_param
{
    enum ali_tsi_channel_id channel_id;

    enum ali_tsi_input_id input_id;
};


struct ali_tsi_output_set_param
{
    enum ali_tsi_output_id output_id;

    enum ali_tsi_channel_id channel_id;
};


struct ali_tsi_ci_bypass_set_param
{
    enum ali_tsi_ci_id ci_id;

    __u32 is_bypass;
};

#define ALI_TSI_IOC_MAGIC  0xA2

#define ALI_TSI_INPUT_SET _IOW(ALI_TSI_IOC_MAGIC, 41, struct ali_tsi_input_set_param)

#define ALI_TSI_CHANNEL_SET _IOW(ALI_TSI_IOC_MAGIC, 42, struct ali_tsi_channel_set_param)

#define ALI_TSI_OUTPUT_SET _IOW(ALI_TSI_IOC_MAGIC, 43, struct ali_tsi_output_set_param)

#define ALI_TSI_CI_LINK_MODE_SET _IOW(ALI_TSI_IOC_MAGIC, 44, enum ali_tsi_ci_link_mode)

#define ALI_TSI_CI_BYPASS_SET _IOW(ALI_TSI_IOC_MAGIC, 45, struct ali_tsi_ci_bypass_set_param)

#define ALI_TSI_CI_SPI_0_1_SWAP _IOW(ALI_TSI_IOC_MAGIC, 46, __s32)


#define ALI_TSI_INPUT_GET _IOWR(ALI_TSI_IOC_MAGIC, 81, struct ali_tsi_input_set_param)

#define ALI_TSI_CHANNEL_GET _IOWR(ALI_TSI_IOC_MAGIC, 82, struct ali_tsi_channel_set_param)

#define ALI_TSI_OUTPUT_GET _IOWR(ALI_TSI_IOC_MAGIC, 83, struct ali_tsi_output_set_param)

#define ALI_TSI_CI_LINK_MODE_GET _IOR(ALI_TSI_IOC_MAGIC, 84, enum ali_tsi_ci_link_mode)

#define ALI_TSI_CI_BYPASS_GET _IOWR(ALI_TSI_IOC_MAGIC, 85, struct ali_tsi_ci_bypass_set_param)

#endif

