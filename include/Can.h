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


class Can 
{
private: 
	const char * ifname = "can0";
	int * socket; 
	bool enable; 

	static const int nbFilters = 0; 
	static const char idFilters[nbFilters]; // = { IDMSG1, IDMSG2 }

	int initFilters(); 
	int initSocket();

	void (*listenCallback)(int nbBytes, int * data); 
	void listenTask(); 

public: 	
	Can(); 
	virtual ~Can(); 
	
	int startListening(void (*callback)(int nbBytes, int * data));
	int stopListening(); 
};


#endif