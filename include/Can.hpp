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


class Can 
{
private: 
	const char * ifname = "can0";
	int * canSckt; 
	bool enable;

	std::thread * listenThread; 
	bool listening; 

	int nbFilters = 1; 
	unsigned int * idFilters;

	int initFilters(); 
	int initSocket();

	void (*listenCallback)(uint32_t id, int nbBytes, char * bytes) = nullptr;
	void listenTask(); 

public:
	Can(); 
	Can(const int nbFilters, const unsigned int * idFilters); 
	virtual ~Can(); 
	
	int startListening(void (*callback)(uint32_t id, int nbBytes, char * bytes) = nullptr);

	int stopListening(); 

	int sendFrame(struct can_frame * frame);
	int sendFrame(struct can_frame * frame, int nbBytes, char * bytes); 

	enum FrameDir_t { None = 0, Emission = 1, Reception = 2 };
};

void printFrame(Can::FrameDir_t dir, struct can_frame *frame); 


#endif