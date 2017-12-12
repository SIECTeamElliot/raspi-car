#ifndef CAN_H
#define CAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <thread>
#include <iostream> 

#define DEBUG true

class Can 
{
private: 
	const char * ifname = "can0";
	int * canSckt; 
	bool enable;

	std::thread * listenThread; 
	bool listening; 

	int nbFilters = 1; 
	unsigned char * idFilters; // = { IDMSG1, IDMSG2 }

	int initFilters(); 
	int initSocket();

	void (*listenCallback)(int nbBytes, unsigned char * bytes); 
	void listenTask(); 

public: 	
	Can(); 
	Can(int nbFilters, unsigned char * idFilters); 
	virtual ~Can(); 
	
	int startListening(void (*callback)(int nbBytes, unsigned char * bytes) = nullptr);
	int stopListening(); 

	int sendFrame(struct can_frame *frame, int nbBytes, unsigned char * bytes); 
};


#endif