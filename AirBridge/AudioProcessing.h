//
//  AudioProcessing.h
//  PulseFilter
//
//  Created by Kerry Davis on 7/3/11.
//  Copyright 2010 mVeloce. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "PulseFilter.h"
//#import "AudioModel.h"

// Keys for dictionary with params, passed in AudioProcessingDidReceiveMessage
#define kWeb            @"webAddress"
#define kName911        @"Name911"
#define kText911        @"Text911"
#define kEmail911       @"Email911"

#define kMessage		@"message"
#define kparent_ID      @"parent_ID"
#define kchild_ID		@"child_ID"
#define kFirstName		@"firstName"
#define kLastName		@"lastName"
#define kEmail			@"email"
#define kPhoneNumber	@"phoneNumber"
//#define kSMSNumber		@"SMSNumber"
#define kAdditionalInfo	@"additionalInfo"
#define kOrganization	@"organization"
//#define kBand			@"band" // broadcast beacon channel band
#define kZIP			@"zip"
#define kRegTimestamp	@"regTimestamp"

#define kPassword		@"password"
#define kPasswordHint		@"passwordHint"
#define kSendBuffer		@"sendRawBuffer"
#define kPermitBroadcast @"permitBroadcast"
#define kUseComments	@"useComments"
#define kUseOverlays	@"useOverlays"
#define kUseSpeaker		@"useSpeaker"
#define kAudioCategory	@"audioCategory"
#define kDoubleTapForPaymentEnabled @"doubleTapForPaymentEnabled"
#define kCCWsKey		@"ccwsKey"
#define kCCWsString		@"ccwsString"
#define kNotifyFlags	@"notifyFlags"


#ifdef DEBUG
#define kUrbanApplicationKey			@"llz5tuatSjmGPtMlt6qhtA"
#define kUrbanApplicationMasterSecret	@"sPyEw6JtSbGn3SxHdjVG4g"
#else
#define kUrbanApplicationKey			@"CRbPCh6vQW6PreCje05Z0g"
#define kUrbanApplicationMasterSecret	@"u9zXzhzBT22uQdfJlmFbUQ"
#endif

#define kSlideshowDelay					@"slideshowDelay"
#define kPictureTakeDelay				@"takeDelay"
#define kPictureSelectDelay				@"selectDelay"
//#define ks_vpidHigh_ID					@"s_vpidHigh_ID"
#define ks_vpidLow_ID					@"s_vpidLow_ID" // stores phone numbers and shortened codes
#define ks_vpidInterval_ID				@"s_vpidInterval_ID"
#define ks_CDBand_ID                    @"s_CDBand_ID"
#define ks_FMBand_ID                    @"s_FMBand_ID"
#define ks_AMBand_ID                    @"s_AMBand_ID"

#define kCityPhoto							@"city_photo"
#define kStateUser							@"state_user"

#define kCorpName                       @"corpName"
#define kCorpURL                        @"corpURL"
#define kBusinessName					@"businessName"
#define kBusinessLocation				@"businessLocation"
#define kStreet							@"street"
#define kCity							@"city"
#define kState							@"state"
#define ksmsPhone						@"smsPhone"
#define kgpsLocation					@"gpsLocation"
#define kgpsLatitude					@"gpsLatitude"
#define kgpsLongitude					@"gpsLongitude"
#define kAdminEmail						@"adminEmail"
#define kBusinessPhone					@"businessPhone"
#define kEnabledServices				@"enabledServices"
#define kSlidesMaxCount					@"slidesMaxCount"
#define kBackgroundMusic				@"backgroundMusic"
#define kBackgroundMusicList			@"backgroundMusicList"
#define kPermitBroadcast				@"permitBroadcast"
#define kCSPhone						@"customerServicePhone"
#define kESPhone						@"emergencyServicePhone"
#define kSpeakerRoute					@"useSpeakerRoute"
#define kRecordOnly						@"recordOnly"

#define kSMTPRelay						@"smtpRelay"
#define kSMTPUsername					@"smtpUsername"
#define kSMTPPassword					@"smtpPassword"
#define kSMTPFrom                       @"smtpFrom"
#define kCustomURL                      @"customURL"

#define kAutoDialGroup                  @"autoDialGroup"
#define kAutoDial                       @"autoDial"
#define kVenueID                        @"venueID"
#define kDeptID                         @"deptID"
#define kSynch                          @"synch"

#define kServiceURL                     @"serviceURL" // short URL remote invocation
#define kUtube                          @"uTube"
#define kAppStore                       @"appStore"
#define kSmppCode                       @"smppCode"
#define kSmppText                       @"smppText"
#define kNativeApp                      @"nativeApp" // invoke native app on users phone
#define kSecurityCode                   @"securityCode"
#define kCatID                          @"catID"

#define kLoyal                          @"loyal"

#define kSettingsPwd					@"settingsPwd"
#define kAdminPwd						@"adminPwd"
#define kOverlayImage					@"overlayImage"
#define kBackgroundImage				@"backgroundImage"
#define kAdsImages						@"adsImages"
#define kAdsImagesUpdated				@"adsImagesUpdated"
#define kCouponImages					@"couponImages"
#define kCouponImagesUpdated			@"couponImagesUpdated"
#define kReservationUserName			@"name"
#define kReservationDate				@"date"
#define kReservationFirstDate			@"firstDate"
#define kReservationCount				@"count"
#define kReservationPhone				@"phone"
#define kReservationNotify				@"notify"
#define kReservationEmail				@"email"
#define kReservationLocation			@"location"
#define kReservationAlias				@"deviceAlias"
#define kReservationStatus				@"status"
#define kReservationChildID				@"childId"
#define kReservationCounter				@"counter"
#define kReservationCounterDate			@"counterDate"

#define BINV_ON 1 // turn bit inversion On or Off

//#define UInt8	unsigned char
//#define UInt16	unsigned short
//#define UInt32	unsigned int

#define kDoubleBumpTime 1.5


@protocol AudioProcessingDelegate <NSObject>

@optional

- (void)mailTheFile:(NSString*)aName;
- (void)AudioProcessingDidFailWithMessage:(NSString*)aMessage;
- (void)displayString:(NSString*)aText;
- (void) setPositionWithX:(NSInteger)aX Y:(NSInteger)aY Z:(NSInteger)aZ;
- (void) AudioProcessingDidReceiveMessage:(BEACON_MESSAGE)bconMessage;
- (void) waitForMessage;
- (void) hardwareOutputVolumeChanged:(Float32)volume;

@end

@class AudioModel;
@class AVAudioPlayer;

@interface AudioProcessing : NSObject <AudioModelDelegate>
{
	int xPos;
	int yPos;
	int zPos;
	
	NSString*		m_checkForSSIDName;
	UInt32*			m_lastBuffer;
	UInt32			m_lastCount;
	
	AVAudioPlayer	*m_appSoundPlayer;
	BOOL			m_useSpeaker;
	
//	UInt32 m_PWs[4];	// pulse message gross challenge
//	UInt32 m_CCWs[4];	// credit card challenge
}

typedef struct
{
    char subThoroughfare[20];
    char thoroughfare[50];
    char locality[50];
    char administrativeArea[50];
    char postalCode[50];
    char country[50];
    double latitude;
    double longitude;
} HOMELOCATON;

// alert view tag ids for checkin view operaitions
enum  {
	VERIFICATION_NUM = 101,
    NEW_CONTACT_NUM,
    DIAL_PHONE,
    DIAL_911,
    CTWM,                   // show Call, with optional [Text, Web, Map] selections
    CWM,                    // show Call, Web, Map
    CM,                     // show Call, Map
    CW,                     // show Call, Web
    CTM,                    // show Call, Text, Map
    MODEALERT,
    SELECTPHONE,
    SELECTTEXT,
};


// Servers are odd and clients are even
// this is important because a server can never send to a server
// nor a client to a client
// EXCEPT in special cases like a peer to peer payment transfer
// or a add device where a device agnostic type is used
typedef enum
{
	D_AGNOSTIC,	// Device is agnostic for this peer to peer message
	C_CLIENT,	// Client
	S_DUMB,		// Dumb	Server of any origin
	S_SMART,	// Smart Server
	SC_TBL_END,
}en_device_types;

typedef enum
{
	PRB_ERROR,	// first byte in the record is a 0 then there is an error or placeholder for a null string
	PRB_STRING,	// Pulse Receive Buffer String
	PRB_NUMBER,	// Pulse Receive Buffer Number
	PRB_BIT,	// Pulse eceive Buffer BIT Field
	PRB_FIELD_TYPE_END
}en_next_rec;

// 31 string IDentifiers are available...WARNING DO NOT USE NEWLINE AS THIS IS A VALID STRING CHAR
typedef enum
{
	FIRST_NAME,
	LAST_NAME,
	EMAIL,
	COMMENT_STR,
	S_PARENT_LOCATION,
	S_PARENT_NAME,
	POSTAL_CODE,
	STREET,
	CITY,
	STATE,
    NEWLINE,        // WARNING DO NOT USE NEWLINE AS THIS IS A VALID STRING CHAR
	AD_HOC_TEXT,
	WEB_LINK,
	PIC_KEY,
	CONTACT_KEY,
	END_STRINGIDS
} stringNames;

// 24 different number IDs are available
typedef enum
{
	C_PHONE,
	S_PHONE,
	COMMENT,
	CC_NUMBER,
	SMS_PHONE,		// SMS number for business or second line for client
	END_NUMIDS
} numNames;

// 8 different bit field ID's are avaialable
typedef enum
{
	FLAGS
} bitNames;

//#define PHOTO_INDICATOR 12

// create a send buffer with message type to add a device
// service = relative to the client app service bar or an ack from the server
// social = social network broadcast enabled or not
// perishable = indicates if a time stamp is relevant to how long we accept this message
// dType = device types index; odd are server and even are clients
//long long initPSB(char service, char social, char checkin, char perishable, char dType);

// string is always simply null terminated
//int addPSBString(char *str, char ident);  // add user strings to send buffer

// a number is always terminated with a 1 - 8 which indicates the number of bytes
//int addPSBNumber(long long num, char ident);	// add and compress number into send buffer

// a bit field is always 4 x 6 bits
//int addPSBBit(char *bf, char ident);	// add and compress number into send buffer

long long atollwcheck (const char *);

void setPulseMonState (int state);

void setPulseSleep (int state);

//long long getNextPRBNum (void);
//char *getNextPRBString (void);
//int getNextPRBBit (void);
//int processFFT(float *sample, float base, float inc, unsigned long long *fftv, int log2N);
int processFFT(float base, float inc, unsigned long long *fftv);


//void parsePRB (void);
//int getNextPRBRecord (char *);

void procSleep (float);
//int getBeacon2 (); // combin(freqs,num)

//*************************************************************************************
@end
@interface AudioProcessing () {
    AVAudioPlayer               *audioFailTone;     //Plays a fail tone once
    AVAudioPlayer               *audioSuccessTone;  //Plays a success tone once
    AVAudioPlayer               *audioWinningTone;
    AVAudioPlayer               *audioPlayer2;
    AVAudioPlayer               *audioPlayer3;
    AVAudioPlayer               *dingTone;
//    AVAudioPlayer               *pfSuccessTone;
//    AVAudioPlayer               *pfFailTone;
//    SystemSoundID               dingTone;
//    SystemSoundID               pfSuccessTone;
//    SystemSoundID               pfFailTone;
}

@property (nonatomic, retain) AVAudioPlayer *audioPlayer2;
@property (nonatomic, retain) AVAudioPlayer *audioFailTone;
@property (nonatomic, retain) AVAudioPlayer *audioSuccessTone;
@property (nonatomic, retain) AVAudioPlayer *audioWinningTone;
//@property (nonatomic, retain) AVAudioPlayer *dingTone;


@property (nonatomic, assign) AudioModel *audioModel;
@property (nonatomic, assign) NSObject<AudioProcessingDelegate>* delegate;
@property (nonatomic, copy) NSString *checkForSSIDName;

@property int xPos;
@property int yPos;
@property int zPos;

//@property (readonly) UInt32* PWs;
//@property (readonly) UInt32* CCWs;

@property BOOL useSpeaker;

//+ (void) processHexString:(NSString*)hexString outputBuffer:(UInt32*)buffer;
//+ (void) processHumanString:(NSString*)aString outputBuffer:(UInt8*)buffer;
//#if defined (NVOKER) || defined (NVOSERVER)
- (void) createBeaconWav:(char *)serviceURL :(int) catID;
- (void) stopGraph;
//#endif

//- (UInt32 *) makeAudio:(unsigned char *)msg count:(UInt32 *)count :(int)ifServer :(int)msgSize;

- (void) playBuffer:(unsigned char *)msg count:(int)count;

+ (void) nvokeurl:url storeName:store;

- (id)initWithCategory:(int)aCategory;
+ (void) setSpeakerRoute: (BOOL)speakerRoute;
//- (void) initSysAudioPlayer;
- (void) showLowVolumeAlert;
- (void) showMuteError;

- (void) startGraph;
- (void) gameBeaconPlay;
- (void) gameBeaconPause;
- (void) gameBeaconStop;

- (void) initTone;
//- (void) playTone:(float)toneDuration :(uint)freq;
+ (void) playSystemTone:(int)tone;
//- (void) dingPlayer;
//- (void) pfSuccessPlayer;
//- (void) pfFailPlayer;
+ (NSString*) stripPhoneFormat: (NSString*)ph;
//- (void) setupAudioSession;

//- (void) processCheckin;
//- (int) processNFC;
//- (int) processLocation;
//- (int) processNFCStateHandler;
+ (void) processNFCStateHandler2;

//- (NSString *)genQRfromMsg;
//- (int) congestion;
//- (void) processCheckinWithTone:(BOOL)aTone;
//- (void) processCheckinReplay;
//- (void) processSample;
//- (void) processReplay;
//- (void) processData;

//- (BOOL) isSSIDMatch;
//- (BOOL) isSSIDMatch:(NSString*)aSSID;

#define PROCESSMICDELAY 0.2
#define PROCESSNFCDELAY 0.4
#define PROCESSGAMEDELAY 0.4
#define PROCESSSLIDEDELAY 15.0

//- (BOOL) playAudio:(unsigned char *)aChars :(BOOL)audible :(int)msgSize;
- (BOOL) playWAV:(NSInteger)loops;
//- (BOOL) replayAudio;
//- (void)sendPSB :(unsigned long long)uid :(int)msgNum :(BOOL)audible :(BOOL)speakerRoute;

//- (void) buildPSBMsg: (unsigned long long) userID :(int)msgNum;

- (void) restartModel;


typedef struct
{
    AudioStreamBasicDescription  dataFormat;
    AudioQueueRef                queue;
    AudioQueueBufferRef          buffers[NUM_BUFFERS];
    AudioFileID                  audioFile;
    SInt64                       currentPacket;
    bool                         recording;
} RecordState;

typedef struct
{
    AudioStreamBasicDescription  dataFormat;
    AudioQueueRef                queue;
    AudioQueueBufferRef          buffers[NUM_BUFFERS];
    AudioFileID                  audioFile;
    SInt64                       currentPacket;
    bool                         playing;
} PlayState;


extern NSString *NULLSTRING;



@end
