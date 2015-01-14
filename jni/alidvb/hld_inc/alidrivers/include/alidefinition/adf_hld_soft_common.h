/*****************************************************************************
          (c) copyrights 2003-. All rights reserved

           T-Square Design; Inc.

          Company confidential and Properietary information.
          This information may not be disclosed to unauthorized
          individual.
 *****************************************************************************/

/*****************************************************************************
 *
 *    PROJECT: audio decoder library
 *
 *    FILE NAME:  soft_common.h
 *
 *    DESCRIPTION: This library for decode WMA, MP3, AAC, OGG...
 *
 *    AUTHOR:  davil ding -- davil_ding@zh.t2-design.com
 *
 *    HISTORY:  11/25/03  created  by davil ding
 *              12/05/03  davil updated it.
 *              12/09/03  davil updated the xxxDecoder_decode() function define. 
 *                        It will more flexible for updating later.
 *              12/10/03  davil changed the functions name with prefix soft.
 *              10/03/08  Eric Li modify for external audio decoder API;
 *
 *****************************************************************************/


#ifndef _SOFT_COMMON_H_
#define _SOFT_COMMON_H_


typedef int bool;

typedef enum
{
    cAudio_NoErr,                       /* -> always first entry */
                                        /* remaining entry order is not guaranteed */
    cAudio_Failed,
    cAudio_BadArgument,
    cAudio_BadBye3Header,
    cAudio_BadAsfHeader,
    cAudio_BadPacketHeader,
    cAudio_BrokenFrame,
    cAudio_NoMoreFrames,
    cAudio_BadSamplingRate,
    cAudio_BadNumberOfChannels,
    cAudio_BadVersionNumber,
    cAudio_BadWeightingMode,
    cAudio_BadPacketization,

    cAudio_BadDRMType,
    cAudio_DRMFailed,
    cAudio_DRMUnsupported,

    cAudio_DemoExpired,

    cAudio_BadState,
    cAudio_Internal,                    /* really bad */
    cAudio_NoMoreDataThisTime,
    cAudio_NoMoreBuffer
} tAudioDecStatus;


typedef void *DecoderInstance;


typedef struct
{
    const void *pvEncodedData;          // pointer to the encoded MP3 data stream.
    unsigned long uiTotalEncodedBytes;  // total number of encoded MP3 data in byte.
    unsigned long uiPacketIndex;        //Packet index, start from 0, the MAX value is (total_packet_num - 1)

} Soft_DecoderIn;



typedef struct
{
    void *pvDecodedData;                /* pointer to decoded PCM data stream. */
    unsigned long uiMaxDecodedBytes;    /* PCM data buffer length in byte. It is used to put the decoded data.
                                           Out put format should be : 
                                           1. Each sample presented as a signed-16-bits-integer; 
                                           2. Byte order is little endian;
                                           3. PCM Sample order is LRLR...   */
    unsigned long uiBytesWritten;       /* real length copied decoded PCM data to PCM data buffer, in bytes. */
    unsigned long uiUsed_EncodedData;   /* used number of encoded MP3 data stream. User should move the MP3
                                           encoded data pointer according this value. This value tell the user how
                                           many encoded data the decoder used. If this value is zero, means decoder
                                           did not use any encoded data, that's because the decoder will decode the
                                           encoded data frame by frame, if the encoded data is less than one frame,
                                           the decoder will not decode it, it will wait the user send more data. 
                                        */
    int bMoreOutputAvailable;           /* flag of PCM data transfer end. */
} Soft_DecoderOut;



typedef enum tagBitsPerSample
{
    cAudio_BPS_8 = 8,
    cAudio_BPS_16 = 16

} tBitsPerSample;



/* sample data Signedness */
typedef enum tagSampleSignedness
{
    cAudio_Unsigned,
    cAudio_Signed

} tSampleSigness;



/* sample data endianness */
typedef enum tagSampleEndianness
{
    cAudio_BigEndian,
    cAudio_LittleEndian

} tSampleEndian;



/* sample data order */
typedef enum tagSampleDataOrder
{
    cAudio_LRLR,
    cAudio_RLRL

} tSampleDataOrder;



typedef struct tagTrack_Name
{
    bool bPresent;
    unsigned char *puiTrackName;        // Only valid if bPresent is true
    
} tTrack_Name;



typedef struct tagTrack_Duration
{
    bool bPresent;
    UINT32 uiTrackDuration;             // of the file in milliseconds, Only valid if bPresent is true

} tTrack_Duration;



typedef struct tagArtist
{
    bool bPresent;
    UINT32 uiArtist;                    // Only valid if bPresent is true
} tArtist;



typedef struct tagAlbum
{
    bool bPresent;
    UINT32 uiArtist;                    // Only valid if bPresent is true
    
} tAlbum;



typedef struct tagOriginal_Track_Number
{
    bool bPresent;
    UINT32 uiOriginalTrackNumber;       // Only valid if bPresent is true
    
} tOriginal_Track_Number;



typedef struct tagDate
{
    bool bPresent;
    UINT32 uiDate;                      // Only valid if bPresent is true
} tDate;



typedef struct tagTotal_file_size
{
    bool bPresent;
    UINT32 uiTotalfilesize;             // Only valid if bPresent is true
} tTotal_file_size;



/* audio info */
#define MAX_TITLE_NUM 256
#define MAX_AUTHOR_NUM 256


typedef struct tagFileHdrInfo
{
    unsigned char pTitle[MAX_TITLE_NUM];    /* Title of the file */
    unsigned char pAuthor[MAX_AUTHOR_NUM];  /* Author of the file */

    tTrack_Name track_name;
    tTrack_Duration track_duration;
    tArtist artist;
    tAlbum album;
    tOriginal_Track_Number original_track_num;
    tDate date;
    tTotal_file_size total_file_size;
    UINT32 first_packet_offset;             /* the offset of the first packet after header. */
    UINT32 packet_size;                     /* packet size for each packet. */
    UINT32 total_packet_num;                /* total packet number in the file. */

    bool is_vbr;
    unsigned long bitrate;                  /* bit-rate of the bitstream */
    UINT32 sample_rate;                     /* sampling rate in HZ */
    UINT32 num_channels;                    /* number of audio channels */
    tBitsPerSample bitspersample;           /* bits per sample */
    tSampleSigness sample_signed;           /* are samples signed or unsigned quantities? */
    tSampleEndian sample_endina;            /* are samples little- or big-endian? */
    tSampleDataOrder sample_data_order;     /* how is multi-channel data is emitted, e.g. is stereo output LRLRLR or RLRLRL? */

} tFileHdrInfo;



struct soft_decoder_callback
{
    tAudioDecStatus (*initialise)   (DecoderInstance *);
    tAudioDecStatus (*decode)       (DecoderInstance, Soft_DecoderIn *, Soft_DecoderOut *);
    void            (*seektime)     (DecoderInstance, long , unsigned char);
    tAudioDecStatus (*finalise)     (DecoderInstance *);
};



struct soft_decoder_callback2
{
    tAudioDecStatus (*initialise)   (DecoderInstance *);
    tAudioDecStatus (*decode)       (DecoderInstance, Soft_DecoderIn *, Soft_DecoderOut *);
    tAudioDecStatus (*seektime)     (DecoderInstance, unsigned long);
    tAudioDecStatus (*finalise)     (DecoderInstance *);
    bool            (*candecode)    (const void *,UINT32 , UINT32 *);
    tAudioDecStatus (*discontinuity)(DecoderInstance);
    tAudioDecStatus (*sync)         (char* , int *);
    bool            (*header)       (DecoderInstance , const void *, UINT32 , tFileHdrInfo *);
};



#endif




