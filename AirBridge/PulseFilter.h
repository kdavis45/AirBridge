//
//  PulseFilter.h
//  nVoker
//
//  Created by Kerry Davis on 7/20/13.
//  Copyright (c) 2013 mVeloce. All rights reserved.
//

#ifndef nVoker_PulseFilter_h
#define nVoker_PulseFilter_h


#include <MacTypes.h>
#include <string.h>	// for memset, memcpy
#include <stdlib.h>	// for abs, fabs
#include "PulseFilterAPI.h"

#define TARGET_OS_IPHONE 1

//#define kServerName @"tablejock.com"
#define kServerName @"www.tablejock.com"

// Pulse Monitor States
#define PMONON  AIRBRIDGERUNNING
#define PMONOFF AIRBRIDGEPAUSED

//#define NSLog(...) /**/
/*
typedef unsigned char                   UInt8;
typedef signed char                     SInt8;
typedef unsigned short                  UInt16;
typedef signed short                    SInt16;

#if __LP64__
typedef unsigned int                    UInt32;
typedef signed int                      SInt32;
#else
typedef unsigned long                   UInt32;
typedef signed long                     SInt32;
#endif
*/


#define DOPSHIfTNUM     4800

#define THIRTY2BITS (0xffffffff)
#define FORTYBITS (0xffffffffff)
#define FORTYONEBITS (0x1ffffffffff)
#define BITSKEWEVEN    (1948) // use this if the 40 bits is even; even divisible by 4 plus even not divisible by 4 is even not divisible by 4
#define BITSKEWODD     (1954) // use this if the 40 bits is odd; odd plus even is still odd
#define BITSKEW3       (1953) // use this if the 40 bits is divisible by 3
#define BITSKEW4       (1952) // use this if the 40 bits is divisible by 4

#define SAMPLE_RATE44 44100
#define SAMPLE_RATE48 48000
#define SAMPLE_RATE SAMPLE_RATE44

#define AUDIO_BUFFER_SIZE (SAMPLE_RATE*2) // buffer 5 seconds
#define BIT_INVERSION 0x3c // this is just the starter bit inversion.
#define BIT_NINV_FLAG 0x40
#define PALETTE_SIZE 12
//#define CUSTID_PULSE_SIZE 15
//#define CUSTID_BASE PALETTE_SIZE
//#define PULSE_FLAGS 2
//#define CHECKOUT_TERMINATOR 0xFF

// macros to translate between the two channel sets low 6 and high 6 in the pallette
//#define CHANNEL0(a) (a)
//#define CHANNEL1(a) (PALETTE_SIZE/2+a)
//#define CHANNELX(a) (isServer?a:(PALETTE_SIZE/2+a))
//#define CHANNELY(a) (isServer?(PALETTE_SIZE/2+a):a)

//#define		PULSESPERCYCLE	22
//Time is defined in terms of received 48Khz samples which is why ONEMS is 48
//Samples are transmitted at 44.1Khz
//#define		ONEMS			(SAMPLE_RATE/1000)
//#if SAMPLE_RATE == 48000
//#define		ONEMS			48 //NOTE this might have been OK with the one line define but I was worried about it being used in a float
//#else
#define		ONEMS			44
//#endif

#define     CDBANDSELECTED  0
#define     FMBANDSELECTED  1
#define     AMBANDSELECTED  2

#define		TENMS			(ONEMS*10)
#define		ONEHUNDREDMS	(TENMS*10)
#define		TWENTYMS		(TENMS*2)
#define		THIRTYMS		(TENMS*3)
#define		FIFTYMS			(TENMS*5)
#define		FIVEMS			(ONEMS*5)
#define		TWOMS			(ONEMS*2)
//#define		TDOASIZE		(2*TENMS) // TWENTYMS

#define		PULSEWIDTH		(6)	// Pulsewidth in ms GOOD FOR CD quality
#define     GZTONESBASE     (16000) // CD Quality

//#define     GTRIM           (2)
#define     GTRIM           (1)
#define     GZDIVISOR       (1)

/*
 #define     BCASTPULSES     (20)  // 16 pulses; each base 4 (2 bits) then 4 more pulses for checksum
 #define     BCASTFREQS      (4)   // top two frequencies toggle the clock
 #define     BCASTINC        (247)
 #define     BROADCASTBASE   (14000)             // base frequency for Broadcast Pulse
 #define     BROADCASTSPACE  (ONEMS*50)          // size of broadcast pulse and message marker
 #define     BROADCASTGWINDOWSIZE  ((3*BROADCASTSPACE)/4)          // size of broadcast pulse and message marker
 */


#define		PULSESPACE		(ONEMS*PULSEWIDTH)	// single DTMF block size

#define TRITONE_ON 1

#define     TRITONEBASE     (16000)  // base frequency for tritone signalling
#define     TRITONEFREQS    (11)  // combin (13,3) = 286 combinations
#define     TRITONENUM      (4)   // combin (13,3) = 286 combinations
#define     TRITONEINC      (150) // 150 HZ frequency separation
#define     TTMFSPACE       (4*ONEMS)   // 4 ms pulse
#define     TTMFCOMBINATIONS (330)     // combin (11,4) = 330 combinations
#define     TTMFWINDOWSIZE ((3*TTMFSPACE)/4)
#define     MARKERSPACE     (ONEMS*50) // size of beginning of message marker: every third frequency is high on each band (server and client)
#define     MARKERWINDOWSIZE    ((3*MARKERSPACE)/4)
#define     MARKERCODE          256    // 4 of 11 code to mark beginning of client message
#define     MARKERCODEACK       259    // 4 of 11 code to mark server responses

// combin (9,4) = 126; for 1 card guts this allows for 0-51 to be card number while
// 52-103 is an ack to a card which eliminates the need for a 7th bit leaving 104-125
// as special values. Likewise, short codes typically use 0-63 which covers all of the
// lower case and upper case letter and numbers 0-9 (27+27+10 = 64); then we still have
// 64-125 as special characters OR we can use combin (9,3) = 84 using the same number
// of USERFREQS but one fewer active frequencies
#define     GAMEFREQS      (8)   // 8 bit pairs (redundant and inverted so really 32 frequencies per channel
//#define     GAMEFREQS      (9)   // combin (GAMEFREQS,GAMENUM)
//#define     GAMENUM        (5)

// NOTE: BASE must be an even multiple of INC and INC must be an even multiple of 48000 and preferrably also 44100
//#define     GAMEBASE          (17400)  // Base frequency for user channels
#define     GAMEBASE          (20200)  // Base frequency for user channels
#define     GAMEINC           (10)   // GAMEINC is the frequency separation between bit pairs
// Game band is between 19860 and 9 frequencies per channel with 10 Hz separation and 5 x 2 channels or 900 Hz in the band
#define     GAMECHANS         (2)   // Number of user channels; but actually 10 because there is another set of channels redundant to these
//#define     GAMEBEACONWINDOWSIZE  (20*TENMS)     // size of broadcast pulse and

#define     BEACONSPACE       SAMPLE_RATE       // size of broadcast pulse and message marker
//#define     BEACONWINDOWSIZE  (4410*6)     // 600 ms window
#define     BEACONWINDOWSIZE  (20*TENMS)     // size of broadcast pulse and
//#define     DOPPLERRANGE       (8)      // Extra frequencies on each side of the base
#define     DTMFPULSE       (PULSESPACE/2)      // Dual Tone Pulse width
#define     DTMFGWINDOWSIZE ((3*DTMFPULSE)/4)   // window for Goertzel
#define     GFLOOR          (5000*PULSEWIDTH)
#define     PSINCREMENT     (PULSESPACE/20)

typedef struct
{
    char    chunkID[4];
    UInt32  chunkSize;          // only this field needs to be calculated
    char    format[4];
    char    subchunk1ID[4];
    UInt32  subchunk1Size;
    UInt16  audioFormat;
    UInt16  numChannels;
    UInt32  sampleRate;
    UInt32  byteRate;
    UInt16  blockAlign;
    UInt16  bitsPerSample;
    //    UInt16  xtraParams;
    char    subchunk2ID[4];
    UInt32  subchunk2Size;      // and this field needs to be calculated
    //    UInt32  subchunk2Size2;      // and this field needs to be calculated
}WAVEHEADER;

#define NUM_BUFFERS 3

typedef struct
{
    AIRBRIDGEHEADER hdr;
    
    unsigned char	na;                      // was 8 bit checksum
    
    union
    {
        unsigned char	all8;                  // all 8 bits of the union
        
        struct
        {
            unsigned char	na      :2;             // not applicable to common
            unsigned char	video2  :2;         // 2 bits of 6 in 11th video ID value
            unsigned char	catID   :4;         // 4 bit category ID
        }utube;
        struct
        {
            unsigned char	group   :4;         // phone group number
            unsigned char	catID   :4;         // 4 bit category ID common to all
        }common;
        
    }u8;
    
    union
    {
        unsigned long long phone;                   // used to store a phone number
        
        struct
        {
            union
            {
                UInt32	parentID;                   // ParentID
                
                struct
                {
                    UInt32	video   :30;           // first 5 characters of video ID
                    UInt32	video2  :2;            // 2 bits of 6 in 11th video ID value
                }utube;
                
                struct
                {
                    UInt32	url     :30;           // first 5 x 6 bit characters of short/custom url
                    UInt32	spare   :2;            //
                }url;                              // both custom and short URLS
                
                struct
                {
                    UInt32	scode       :20;        // up to 6 digit short code
                    UInt32	msg         :12;        // first 2 characters of message
                }smpp;
                
            }u321;
            
            union
            {
                UInt32	childID;                    // ParentID
                
                struct
                {
                    UInt32	video   :30;           // next 5 characters of video ID
                    UInt32	video2  :2;            // 2 bits of 6 in 11th video ID value
                }utube;
                
                struct
                {
                    UInt32	url     :30;           // next 5 x 6 bit characters of short/custom url
                    UInt32	spare   :2;            //
                }url;                               // both custom and short URLS
                
                struct
                {
                    UInt32	msg      :30;        // next 5 characters of message for 7 characters total
                    UInt32	spare    :2;            //
                }smpp;
                
            }u322;
            
        }s64;
    }u64;
    
    // NOTE 80 bits above this point
    /*
     union
     {
     UInt16  unused[4]; // these bits are unused except to place the structure on a 32 bit boundary
     struct
     {
     unsigned char	shortCodes1      :6;             // not applicable to common
     unsigned char	shortCodes2      :6;             // not applicable to common
     unsigned char	shortCodes3      :6;             // not applicable to common
     unsigned char	shortCodes4      :6;             // not applicable to common
     unsigned char	shortCodes5      :6;             // not applicable to common
     unsigned char	shortCodes6      :6;             // not applicable to common
     unsigned char	shortCodes7      :6;             // not applicable to common
     unsigned char	shortCodes8      :6;             // not applicable to common
     unsigned char	shortCodes9      :6;             // not applicable to common
     unsigned char	shortCodes10     :6;             // not applicable to common
     unsigned char	spare     :4;             // not applicable to common
     }scodes64;
     
     }u64_2;
     */
    struct
    {
        unsigned char	shortCodes1      :6;             // not applicable to common
        unsigned char	shortCodes2      :6;             // not applicable to common
        unsigned char	shortCodes3      :6;             // not applicable to common
        unsigned char	shortCodes4      :6;             // not applicable to common
        unsigned char	shortCodes5      :6;             // not applicable to common
        unsigned char	shortCodes6      :6;             // not applicable to common
        unsigned char	shortCodes7      :6;             // not applicable to common
        unsigned char	shortCodes8      :6;             // not applicable to common
        unsigned char	shortCodes9      :6;             // not applicable to common
        unsigned char	shortCodes10     :6;             // not applicable to common
        unsigned char	spare     :4;             // not applicable to common
    }scodes64;
    
}BEACON_MESSAGE; // allow to grow up to 256 bit messages


// 4 bit Beacon Category ID
enum  {
	CAT_VENUE,	// Venue ID Message contains 30 bit ParentID, 30 bit ChildID, 8 bit checksum; used for checking in to a venue
	CAT_PHONE,  // 64 Bit phone number containing up to 20 digits, 4 bit parity
	CAT_UTUBE,  // 11 x 6 bit Video ID, 2 bit checksum
	CAT_SURL,   // 10 x 6 bit Short Google URL, 8 bit checksum
	CAT_SMPP,   // SMPP short code message, 20 bit up to 6 digit short code, 7 x 6 bit message, 6 bit checksum
    CAT_CURL,   // Custom URL invocation, 10 x 6 bit custom URL to invoke a native app, 8 bit checksum - requires code updates to add any parameters
    CAT_LOYAL,  // 30 bit ParentID, 30 bit ChildID, 8 bit checksum; used to punch a virtual loyalty
    CAT_SYNCH,  // Broadcast message to display synch advertising returned from web data
    CAT_APPSTORE, // invoke the app store at this ID
    CAT_MAP,    // Display Google map of the venue location
    CAT_THUMPB, // Indicates the beacon contains simply a 14 character ASCII name auto capitolized on each first character
    CAT_LOCATION, // Similar to a venue where the parent VID identifies the venue and child VID identifies
    CAT_SEQUENCE, // Used to get a timed control sequence typically using a low frequency command
    CAT_URL,      // Used to invoke a web page or app external to this app
    CAT_HOME = 15, // Allow personal use of the home beacon category as the last entry
};

// 4 bit Venue Type ID's stored in the .group field of the beacon message
enum  {
	VID_PERSONAL,	// Home Venues
	VID_ID,         // ID venues where a certificate is conveyed like a school or government ID certificate that must be produced in the future
	VID_FOOD,       // Restaurants
 	VID_RETAIL,     // retail stores
	VID_HOTEL,      // Hotels and/or Casinos
 	VID_MALL,       // Malls, airports, bus or train stations
    VID_SPORT,      // Sport Venues and stadiums
    VID_MED,        // All Medical related venues like hospitals, dentists and doctors offices
    VID_PROF,       // All professional or service related groups like Lawyers an accountants related venues
    VID_BROADCAST,  // All Broadcast Media, TV
    VID_CINEMA,     // Cinema movies and posters
    VID_MUSEUM,     // Museums and art exhibits
    VID_GOV,        // All government related venues
    VID_END = 15,
};

/////////////////////******************** USING THESE VALUES
#define LOG2N                   (15) //NOTE: to get 5 Hz separation you need at least log2n=14 or greater
//#define LOG2N                   (16) //NOTE: to get 5 Hz separation you need at least log2n=14 or greater
//#define LOG2NFM                 (12) //NOTE: to get 5 Hz separation you need at least log2n=14 or greater
#define FFT_SAMPLES             (1<<LOG2N) // this equals 65536 if LOG2N is 16
//#define FFT_SAMPLESFM           (1<<LOG2NFM) // this equals 65536 if LOG2N is 16
//#define NOVER2                  (FFT_SAMPLES/2)
//#define NOVER2FM                (FFT_SAMPLESFM/2)
//#ifdef TJ
//#define     SAMPLE_CYCLE    (1*(SAMPLE_RATE/(GAMEINC/2))) // NOTE: SAMPLE_CYCLE is how many cycles before all frequencies in signal repeat
//#else
#define     SAMPLE_CYCLE    (FFT_SAMPLES/2) // Same as N/2 NOTE: SAMPLE_CYCLE is how many cycles before all frequencies in signal repeat
//#endif

#define     BASEFREQINC         ((float)SAMPLE_RATE/FFT_SAMPLES)

#define MARKEROFFSET            (50)
#define BEACONBASEOFFSET        (int)(18000/(BASEFREQINC*1024))
#define BEACONBASEFMOFFSET      (int)(15000/(BASEFREQINC*1024))
#define BEACONBASEAMOFFSET      (int)(1500/(BASEFREQINC*1024))

//#define BEACONBASEOFFSET        (48) (18000/(BASEFREQINC*1024))
//#define BEACONBASEFMOFFSET      (40)
//#define BEACONBASEAMOFFSET      (3)

//#define     BEACONMULT          (8)
//#define     BEACONMULT          (FFT_SAMPLES/SAMPLE_CYCLE)
#define     BEACONMULT          (FFT_SAMPLES/16384)
//#define     CYCLESIZE           (SAMPLE_RATE/(SAMPLE_RATE/FFT_SAMPLES/8))
//#define     CYCLESIZE           (16384) // Stupid compiler will not let me nest defined constants

#define     BEACONCHANS         (10)
#define     BEACONBYTESPERCHAN  (2) // extra bit added per channel stores checksum

#define     BEACONDIVIDER     (0)     // range of beacon frquencies for two 36 bit numbers
#define     BEACONSKEW        (BEACONMULT*BEACONMULT)     // range of beacon frquencies for two 36 bit numbers
#define     BEACONFREQS        (20)     // range of beacon frquencies for two 36 bit numbers
#define     BEACONNUM          (9)              // Number of beacon fequencies
//#define     BEACONMSGSZ         (BEACONCHANS * (int)(BEACONBITSPERCHAN/8))     // size of beacon message in bytes
//#define     BEACONINCFM       ((float)10.0)            // frequency separation in Hz; must be even number
//#define     BEACONINCFM         ((float)BASEFREQINC*BEACONMULTFM)            // frequency separation in Hz; must be even
//#define     BEACONINC         ((float)BASEFREQINC*BEACONMULT*2)            // frequency separation in Hz; must be even
#define     BEACONINC           ((double)BASEFREQINC*BEACONMULT)            // frequency separation in Hz; must be even
#define     BEACONINCAM           ((double)BASEFREQINC*BEACONMULT*BEACONMULT)            // frequency separation in Hz; must be even
// NOTE: Any base multiple of 1024 (375Hz) will work with a BASEFREQINC of 0.36621 which comes from LOG2N=17

#define     BEACONBASE          ((double)BASEFREQINC*1024*BEACONBASEOFFSET)  // .366*1024*48=18 KHz

#define     BEACONBASEFM        ((double)BASEFREQINC*1024*BEACONBASEFMOFFSET)  // .366*1024*40=15 KHz
#define     BEACONBASEAM        ((double)BASEFREQINC*1024*BEACONBASEAMOFFSET)  // .366*1024*40=15 KHz
/////////////////////******************** USING THESE VALUES


#define WAVESIZE   2 // 4 for stereo and 2 for mono

/*
 {set of all frequencies} / freq increment/2) should always be an even whole number if
 you want all the frequencies to cross 0 at the exact same place for 2 pi of a common
 multiple of every frequency. That common multiple is sample rate / frequency separation
 (or increment) / 2. For example if frequency separtion (increment) is 20 and the sample
 rate is 48000 then all frequencies will have a 0 crossing at 48000/20/2 = 4800 samples.
 Likewise if the sample rate is 44100 then 44100/20/2 = 4410 samples is the 2 pi 0
 crossing. the pi crossing is half of each of those and the 90 degree or pi/2 crossing is
 half of those. This is significant because we can actually generate the complete set of
 sample values for any combination of frequencies with as few as the pi/2 number of samples
 (1200 samples and 1102.5 where one sample is shared on both sides of the peak sample at
 pi). So ex. 16800, 16820, 16840, 16860...18000 all cross 0 at sample 0 and at samples 4800
 with sample rate 48000 or sample 4410 with sample rate 44100. This also means we can
 sample a single 4410 sample, replicate it any number of times, and run it thru an FFT or
 Goertzel algorithm to get a more precise set of frequencies in a shorter period of time
 assuming we are looking for a static repeating beacon. Normally we would need a 200 or
 even 400 ms samples to get good frequency separation. But, knowing that our frequencies
 will cycle in these shorter periods, we can use this replication procedure to reduce that
 time to 4410/44100 = 100 ms and cut the time in half. And since we know the beacon will
 cycle, it doesn't matter where we start the sample and replicate it.
 */

#define     AUDIO_BYTES         (2)
#define     AUDIO_BITS          (AUDIO_BYTES*8)
#define     AUDIO_CHANNELS      (AUDIO_BYTES/2)


//#define     SAMPLE_CYCLE48    (48000/(BEACONINC/2))
//#define     SAMPLE_CYCLE    (SAMPLE_RATE/5)
//#define     SAMPLE_CYCLE48    (48000/5)
//#define     SAMPLE_CYCLE48    (48000/(BEACONINC/2)*(WAVESIZE/2))
#define     GAME_CYCLE48    (SAMPLE_RATE/(GAMEINC/2))

//#define ORBUFFER_SIZE   (((SAMPLE_CYCLE/AUDIO_BLOCK)+1)*AUDIO_BLOCK)

#define TWO2THE15TH             (32767.0) // I can attenuate this to keep from too much distortion
#define TWO2THE14TH             (16383.0) // I can attenuate this to keep from too much distortion
#define TWO2THE13TH             (8191.0) // I can attenuate this to keep from too much distortion
#define TWO2THE12TH             (4091.0) // I can attenuate this to keep from too much distortion

//#define     ATTENUATION         (2.9)
//#define     ATTENUATION         (1.0)

//#define THUMPB_READY_TONE       19000.0 // Peer indicator that it is ready to receive a Thumpb message
//#define CHECKIN_READY_TONE      19400.0 // Peer indicator that it is ready to check in to a server
//#define CHECKIN_TONE_THRESHOLD  100000
//#define THUMPB_TONE_THRESHOLD   100000

// define tone target fft array indices
#define		TTA				0
#define		TTB				1
#define		TTC				2
#define		TTD				3
#define		TTE				4
#define		TTF				5

// shapestereo side defines
#define LEFTSIDE            1
#define RIGHTSIDE           2
#define BOTHSIDES           3

//#define		N3				(1<<3)
//#define		N9				(1<<9)
//#define		N9OVER2			(N9/2)

typedef struct
{
	unsigned long		fft[PALETTE_SIZE];
	int                 audio;
	int                 peakFreq;	// index to the peak frequency
} TONESBUFFER;

#define MAX_CHARS           175
#define	AUDIO_BLOCK         1024
#define MAXBLOCKS           88
//#define MAXBLOCKS           150
// NFC receive states
#define	ALERTSTATE	0
#define	HEADERSTATE	1
#define	BODYSTATE	2

#define PM_TX_SIZE			(MAX_CHARS-6)
#define MAX_PSB_NUM_SIZE	8 // how many maximum bytes in a long long converted to base 5
#define MAX_SBBITS			22 // maximum number of bytes in a bit field record

#define MAX_DEVICE_TYPES 20

//#define	REDUNDANT		1	// indicates whether we send a second message or not
//#define	PULSEBASE	5		// each Pulse is based on the number of different pulse frequencies possible (0-4)
//#define SYMBOLBASE	125			// each symbol is base 125 (values between 0-124)
#define SYMBOLBASE	256			// each symbol is base 125 (values between 0-124)
//#define SYMBOLBASE	0x7f			// each symbol is base 128 (values between 0-127)
#define	CHKSUMMOD	SYMBOLBASE	// Checksum is across all possible symbol values so naturally they are equivalent
#define MSGEXPTM 86400 // 24*60*60 This assumes time() is on a second boundary

#define	PWDMOD 256

#define codeTimeEpoch	1321890300	// time in seconds since 1970 when i tested the time stamp code for the first time


// Message Type is always 0 - 124
// bit 5 (value 32) indicates server check in/out broadcast permission; 32 gives permission for the Server to broadcast check IN/OUT
// bit 6 (value 64) indicates if this is a check IN (1) or OUT (0)
// bitwise definitions are the first and the 5th and 6th bits


// default NFC substitution strings for ASCII values 1-31 in the message body of the check in/out messages (Post decryption)

#define	SUB_FB		1
#define	SUB_TW		2
#define	SUB_YP		3
#define	SUB_THX		4
#define	SUB_NET		5
#define	SUB_GOV		6
#define	SUB_HTTP	7
#define	SUB_HTTPS	8
#define	SUB_FINDME	9
#define	SUB_GRATS	10
#define	SUB_NOCP	11	// no coupon

// Server Check In/Out Acknowledgements...first returned parameter is always server location
// Service is either accepted or failed
// If service is awarded then look in second parameter for award definition; Award depends on the service requested
#define	ACKA		0	// Service Awarded...look in first parameter for server location and second location for any award info
#define ACKP		1	// Service Awarded with points ... look in third parameter for points

// Message Failure Definitions
#define	ACKFCC		122	// Service Failed due to a check sum failure
#define	ACKFH		123	// Service Failed due to a SHA1 Hash failure
#define	ACKD		124	// Service Recieved but Denied due to customer class of service or account

#define NOTIFY_BY_PUSH	0x08
#define NOTIFY_BY_TEXT	0x04
#define NOTIFY_BY_PHONE	0x02
#define NOTIFY_BY_EMAIL	0x01

#define ENABLE_GIFT     0x01
#define ENABLE_PAYMENTS	0x02
#define ENABLE_MENU		0x04
#define ENABLE_MAP		0x08

#define ALERTTONE	0 // Client and Server sends this along with the first header pulse in a response message
#define NFC8MS		12
#define NFC20MS		13
#define NFC100MS	14

// cryptography
#define ENCRYPT		0
#define DECRYPT		1

// the range of values we can send are 0 - 124
// normalized to a base of 32 this become 32 - 156
#define FIELD_DELIMITER	0 // No expansion. Used to delimit all fields including ascii string fields
#define	NUMEXPANSION	1 // expansion code to force the next delimited field to be expanded to a number
#define	CANEXPANSION	2 // expansion code to force the next delimited field to be expanded to a number
#define	CCEXPANSION		3 // expansion code to force the next delimited field to be expanded to a number

#define ASCSPACE	32	// definition for ASCII space ' ' which is the lower bound ASCII character we can transmit
#define ASCTILDE	126 // definition for ASCII'~' which is the upper bound character we can transmit
#define ASCDEL		127 // definition for ASCII DEL. This is the begining of the replacement characters we can transmit
#define	ASCREND		156 // This is the largest replacement value we can receive (after adding back the space)


#define CHECKIN_WAIT_COUNT 10 // wait 2 seconds for server response


// Messages are preceded by a message identifier followed by the message with the message size as the first byte
#define NO_BEACON_MSG     0 //
#define BEACON_MSG_TRUE   1 //
#define BEACON_MSG_DUP    2 // Duplicate Beacon Message
#define ACK_MSG           0x1A // 26
#define SERVER_BEACON_MSG 0x2B // 43
#define SERVER_RSP_MSG    SERVER_BEACON_MSG // 43
#define PHONE_BEACON_MSG  0x2C //
#define SHORT_URL_MSG     0x2D //
#define CLIENT_BEACON_MSG 0x3C //
#define THUMPB_BEACON_MSG 0x4D
#define PUNCH_BEACON_MSG  0x5E
#define REWARD_BEACON_MSG 0x5F // use this only in nVokeRewardsAPP
#define START_BEACON_MSG  0x6F

#define BITLY             (0x80c080c080c08080) // high order bits in higher
#define GOGGL             (0xc0c080c080c08080) // high order bits in higher
#define UTUBE             (0xc08080c080c08080) // high order bits in higher address space

#define	consumerAcctBase	50764	// base offset for all even numbered consumer parent ID accounts
#define	corpAcctBase		40259	// base offset for all odd numbered corporate parent ID accounts

#define	MAX_PRB_STRING	(ASCSPACE-1)
#define	MAX_PRB_BIT		8
#define	MAX_PRB_NUM		(ASCSPACE-MAX_PRB_BIT)
#define MAX_NUM_DIGITS	19 // 2^64 == 1.8 E+19 so 20 digits but only 19 from 0-9 so we use 19 as the limit
#define PERISHABLE      1
#define NONPERISHABLE   0

typedef struct
{
    unsigned char   bags        :1;		// server ability to take hotel bags
    unsigned char	payments    :1;		// payments are enabled on this server
    unsigned char	menu        :1;		// menu is enabled on this server
    unsigned char	map         :1;		// map is enabled on this server
    unsigned char   loyalty     :1;		// display loyalty card relative to this vendor
    unsigned char   custserv    :1;		// call for customer service
    unsigned char   table       :1;		// server ability to take table reservation
    unsigned char	perishable	:1;		// Time Perishable Message - only works if entire message is
}SERVICE_BITS;


// TODO we need to union these headers
// 16 bits require 7 pulses, then 3 more for number in party and 2 more for checksum
typedef struct
{
    union
    {
        unsigned char   bin;
        struct
        {
            unsigned char	spare       :3;		//
            unsigned char	luggage     :1;		// This is a luggage checkin
            unsigned char	occasion    :4;		// up to 16 occasions
            unsigned char	notify      :4;		// bitmap of callback preferences, phone, text, push, email
            unsigned char	withPhoto	:1;		// indicate if checkin is with photo
            unsigned char	seating		:2;		// inside, outside, in or out, bar
            unsigned char	perishable	:1;		// Time Perishable Message - only works if entire message is readable
        }ckin;
        struct
        {
            unsigned char	spare       :8;		//
            unsigned char	comment     :4;		// index to canned comment
            unsigned char	rating		:3;		// inside, outside, in or out, bar
            unsigned char	perishable	:1;		// Time Perishable Message - only works if entire message is readable
        }ckout;
        
        SERVICE_BITS srvr;
        
    }u;
    
    // These 8 bits are in every message
	unsigned char	spare       :8;		// Checkin or out spare
	unsigned char	checkin     :1;		// Checkin or out
	unsigned char	devtype		:2;		// Agnostic, Smart Server, Dumb Server, Client
	unsigned char	social		:1;		// is social networking allowed
	unsigned char	service		:4;		// service requested - basically the scroll position SP_ Value
    UInt8           rcvdMsgNum;         // primarily number in party but can mean other things
    UInt8           hdrChkSum;
} PULSEHDR;

//- (void) AudioProcessingDidReceiveMessage:(PULSEHDR)rxHdr :(time_t)rxTime :(long long)userID :(int)rcvdMsgNum :(NSString*[])prbString :(long long []) prbNumber :(int)err

/*
typedef struct
{
    long long                   prbNumber[MAX_PRB_NUM];
    unsigned long long          rcvdUserID;
    NSString                    *prbString[MAX_PRB_STRING];
    time_t                      rxTime;
    int                         err;
    int                         ret;                        // message type being returned (i.e. beacon, ack etc
    PULSEHDR                    rxHdr;
}PULSEPACKET;
*/
#define CHECKIN_DELAY   15 // use this in the service field to delay processing the more information popup
// this is the structure used to play the message
typedef struct
{
	unsigned char	msgSize;	// msgSize in symbols not including this header
	unsigned char	chkSum;		// encrypted checksum starting at uchksum
	unsigned char	uChkSum;	// unencrypted checksum over message body including msgType
	unsigned char	respSeed;   // client should use this seed when encrypting a response
    UInt32          timeStamp;  // every message has a time stamp in seconds since 1970
    unsigned long long          rcvdUserID;
    // Beacon message ends here
    PULSEHDR        txHdr;     // binary message header
	char            sendPB [PM_TX_SIZE];	// send Pulse Buffer
} PULSEMSG;

/*
 // Service Categories
 enum  {
 SP_HOME,		// Simple check in with or without picture
 SP_CHECKOUT,	// Check out service
 SP_ADMIN,       // ADMIN Function
 SP_COUPON,      // ADMIN Function
 SP_PMT,         // make a payment
 SP_LOYAL,       // Process a Loyalty transaction
 SP_MAP,			// show map if not checked in or show augmented reality if indoors and checked in
 SP_MENU,		// look at menu service..surf to restaurant menu
 SP_GIFT,        // Process a Gift Coupon transaction
 SP_CUSTSERV,    // Call for Customer Service
 SP_THUMPB,		// Share Contact Information
 SP_ABOUT,		// Reveal QR Button populated with QR link to this app
 CHECKIN_SVC_COUNT // this is always last
 };
 */
// Service Categories
enum  {
	SP_HOME,		// Slides presented by venue after checking in.
    SP_SLIDE2,		//
    SP_SLIDE3,		//
    SP_SLIDE4,		//
    SP_SLIDE5,		//
    SP_SLIDE6,		//
    SP_SLIDE7,		//
    SP_SLIDE8,		//
    SP_SLIDE9,		//
    SP_SLIDE10,		//
    SP_SLIDE11,		//
    SP_SLIDE12,		//
    SP_SLIDE13,		//
    SP_SLIDE14,		//
    SP_SLIDE15,		//
    SP_SLIDE16,		//
	SP_REWARDS,		// display virtual rewards
	CHECKIN_SVC_COUNT // this is always last
};

// shape audio edges
enum  {
	SA_LINEAR,
	SA_SINE,
	SA_SINEEDGE,
	SA_INVSINE,
	SA_NOEDGE,
};


// Transaction Codes
enum  {
	TC_BUSREG = 256, // Start transaction codes at 256, if they are below 256 then they are simply the button in the high order bits | with the service
	TC_REG,         // Customer Registration
	TC_ADMINCKIN,   // ADMIN Checkin
	TC_ADMINSEAT,   // ADMIN seat customer
	TC_ADMINCANCEL, // ADMIN cancel customer reservation
	TC_ADMINNOTIFY, // ADMIN Call back customer on wait list
	TC_ADMINRESERVE,// ADMIN move existng customer to wait list
	TC_CHKOUT0,     // check out with no stars
	TC_CHKOUT1,     // check out with 1 stars
	TC_CHKOUT2,     // check out with 2 stars
	TC_CHKOUT3,     // check out with 3 stars
	TC_CHKOUT4,     // check out with 4 stars
	TC_CHKOUT5,     // check out with 5 stars
	TC_THUMPBSHARE  // Share something with Thumpb
    
};

// processNFCStateHandler return codes
#define NFC_NO_ERROR        0
#define NFC_NO_MESSAGE      -1
#define NFC_HEADER_OK       -2
#define NFC_CHECKIN_TONE    -3
#define NFC_PERISHABLE_ERR  -4
#define NFC_COUNTDOWN_ERR   -5
#define NFC_MARKEROK        -6

// SP_PMT must stay below 29 to keep this field below 125
//#define SP_PMT				28 // special service type selected from the payment button

#define SCSB		32	// Secure Social Network Internet Broadcast Authorized
#define	SCI			64	// Secure Check In with optional text
#define ADMINCHECKIN 255 // indicates that an admin is trying to checkin to a mated server

#define CHECKOUT    0
#define CHECKIN     1
#define REWARDS     2 // push out rewords punch message
#define BCON        3 // push out beacon message

// this is a bit indicator in the transaction field which indicates if the checkout button was pushed for this particular service
#define CHECKOUT_BUTTON_CODE 0x40
typedef struct
{
	short base;
	short increment;
	unsigned long long active; // active frequencies for up to 64 frequencies starting at base
}SHAPEAUDIO;


typedef struct
{
	SHAPEAUDIO ch1; // First BEACONFREQS
	SHAPEAUDIO ch2; // Second BEACONFREQS; Theses may be inverted and interleaved
}SHAPEAUDIOCHANNELS;

#define SHA_DEF_SEED 1959 // default seed value for SHA algorithm

int encryptSHA1(int seed, char *beg, char *end, int eFlag, UInt32* secKeys, int range); // returns number of symbols processed
int rndwseed(int rand_seed);
void charcat (char *str, char c);
int stringCat(char *, char *);
int iToBaseX (long long num, char **a, int base, long long pwr);
FILE *cfopenAP (char *cfilename, char *mode);
void encryptServerMateKey (char *apwd, char *ptext, char *mateID);
void decryptServerMateKey (char *apwd, char *mateID);
//void shapeStereo (int side, int freqList[], SInt16 *dest, int sze, int edges, float power);
//void shapeStereo2 (int freqList[], SInt16 *dest, int cycle);
void shapeMono (int *beaconIndices, int base, SInt16 *dest, int cycle, float increment, float inverseInc, int freqs, int redundant);
void shapeMono2 (int *beaconIndices, double base, SInt16 *dest, int cycle, double increment, int freqs);

void storeBeaconWav (SInt16 *bm, int duration, int cycle, int base);
//void stopRecordingAudio (void);
//void startRecordingAudio (void);


typedef struct
{
	char verification[4];
	char l_postalCode[10];
	char value11;
	char value12;
	char value21;
	char value22;
	char value31;
	char value32;
	char value41;
	char value42;
	char spare;
	char msgKey;
}CCRECORD;

typedef union
{
	short count;
	struct
	{
		char rating;
		char cannedComment;
	}out;
	
}INorOUT;

#define NAMESIZE	26
#define EMAILSIZE	50
#define COMMENTSIZE	36
#define kPSBQRStringMaxLength 300

// Client States
typedef enum  {
	CLIENT_INIT_STATE,
	THUMPB_READY_STATE,
	THUMPB_PAUSE_STATE,
	CHECKIN_READY_STATE,
	CHECKIN_PAUSE_STATE,
} ClientStates;

// Server States
typedef enum  {
	SERVER_INIT_STATE,
	BROADCAST_BEACON_STATE,
	PHOTO_STATE,
	ADMIN_STATE,
} ServerStates;

typedef enum  {
	RL_INDOOR,			// Simple check in or out with broadcast permissions without picture
	RL_OUTDOOR,			// Check in or out with Photo only.... may have a digital overlay
	RL_FIRST_AVAILABLE,	// Register Client to Server...Must be done for once for every server
	RL_BAR				// Seating at the Bar
} ReservationLocation;

//self.occasionList = [NSArray arrayWithObjects:@"None", @"Birthday", @"Anniversary", @"Prom", @"Reunion", @"First Time Here", nil];

typedef enum  {
	RO_NONE,			//
	RO_BDAY,			//
	RO_ANIV,			//
	RO_PROM,			//
	RO_REUNION,			//
	RO_FIRST,			//
} ReservationOccasion;



#endif
