//
//  PulseFilterAPI.h
//  PulseFilterLib
//
//  Created by Kerry Davis on 7/23/13.
//
//

/*
 //  Example Use case to recieve a message
 //
 // allocate a venue ID or pass a contant
 UInt16 vid = 12345;
 
 // allocate a static or malloc dynamic buffers if you want to handle mulltiple messages simultaneously in a queue
 AIR_BRIDGE_MESSAGE newMessage;

 // Optionally allocate a separate buffor for processing messages
 AIR_BRIDGE_MESSAGE thisMessage;

 // Create a C call back handler to handle processing of any received messages
 // a pointer to the received message will be passed to the call back handler
 void cProcessAudioMessage(AIR_BRIDGE_MESSAGE *msg) // call back to here from AirBridge platform NOTE: AirBridge will auto pause itself before this call back, so you must continueAirBridge on your side
 {
    // This step may be unnecessary unless you want to handle multiple messages simultaneously
    // in which case you could malloc multiple messages to process and queue them
    memcpy(&thisMessage, msg, sizeof (AIR_BRIDGE_MESSAGE));

    // *msg is ignored because it should always be newMessage
    [thisClass AudioProcessingDidReceiveMessage:newMessage];
 
    // AirBridge is automatically paused when a new message is received so you must continue when you are ready to do so
    // NOTE: if processing will take a long time then delay the continue until processing is done
    continueAirBridge (void);
 }

 // initialize AirBridge with a new message buffer and provide a call back message handler and assigned venue ID between 1-65535
 // 
 // where newMessage is a pointer to the message buffer to fill NOTE: upon call back you must copy this buffer out immediately because it will be reused on the next call back
 // cProcessAudioMessage is the address of the call back function to handle processing of the recieved message
 // vid is the venue or application ID assigned to you by us
 airBridgeInit (&newMessage, &cProcessAudioMessage, vid);
*/

/*
 //  Example Use case to broadcast a message
 //
 // allocate a send buffer
 AIR_BRIDGE_MESSAGE msg; 
 
 // place your unique venueID into the buffer
 msg.hdr.venueID = 22;   
 
 // fill the buffer with anything you like up to 144 bits (18 bytes or 9 words)
 UInt16 val = 65535;     
 for (int x = 1; x < 9; ++x)
 {
    msg.msgbody[x] = val;
    val--;
 }
 
 // Broadcast the message with (send = 1) or without (send = 0) an additional sound effect
 sendAirBridge (&msg, 1); // NOTE: SendAirBridge will automatically pause and continue internally when sending a message
*/

#ifndef PulseFilterLib_PulseFilterAPI_h
#define PulseFilterLib_PulseFilterAPI_h

// 80 bit message but 12 bytes in the structure. 2 bytes are simply spare at the end of the structure
typedef struct
{
    UInt16  venueID; // RESERVED: This value will be overwritten by the sendAirBridge() API command
    
}AIRBRIDGEHEADER;

typedef struct
{
    AIRBRIDGEHEADER hdr;        // 16 bit header containing Venue (aka Application Developer or Broadcaster ID)
    UInt16          msgbody[9]; // 144 bit message body to be used in any way by Consumer to Consumer App
}AIR_BRIDGE_MESSAGE;

void airBridgeInit (AIR_BRIDGE_MESSAGE *msg, void (callback(AIR_BRIDGE_MESSAGE *)));
void continueAirBridge (void);
void pauseAirBridge (void);
void sendAirBridge (AIR_BRIDGE_MESSAGE *msg, int soundEffect);

// soundEffect defines - 0 indicates stealth mode and 1 indicates the default sound
#define SESTEALTH 0 // send airbridge pulse silently
#define SEDEFAULT 1 // play default audio when sending airbridge pulse

// system tones that can be played by the user via the playSysTone interface in the library
#define SYSFAILTONE    0
#define SYSSUCCESSTONE 1
#define SYSDINGTONE     2

#define PROCESSMICDELAY 0.2
#define PROCESSNFCDELAY 0.4

void playSysTone (int tone);

int getAirBridgeStatus (void);

// AirBridge Status Defines
#define AIRBRIDGERUNNING  -1
#define AIRBRIDGEPAUSED 0

char *airBridgeShortenURL (char *longURL);

#endif
