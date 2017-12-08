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

#define DEBUG true
class Can 
{
private: 
	const char * ifname = "can0";
	int * canSckt; 
	bool enable;

	std::thread * listenThread; 
	bool listening; 

	static constexpr int nbFilters = 1; 
	unsigned char idFilters[nbFilters]; // = { IDMSG1, IDMSG2 }

	int initFilters(); 
	int initSocket();

	void (*listenCallback)(int nbBytes, unsigned char * bytes); 
	void listenTask(); 

public: 	
	Can(); 
	virtual ~Can(); 
	
	int startListening(void (*callback)(int nbBytes, unsigned char * bytes) = nullptr);
	int stopListening(); 

	int sendFrame(struct can_frame *frame, char data); 
};


#endif