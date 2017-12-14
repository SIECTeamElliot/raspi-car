#ifndef DDSCAN_H
#define DDSCAN_H

#include "DDSVar.hpp"
#include "Can.h"

class DDSCan
{
private: 
	void canListenCallback(int nbBytes, unsigned char * bytes); 

public:
	DDSCan(); 
	virtual ~DDSCan(); 

	DDSVar frontUS[3]; 
	DDSVar rearUS[3]; 
	DDSVar steeringWheel;
	DDSVar leftMotorSpeed; 
	DDSVar rightMotorSpeed; 
	DDSVar battery; 
}; 

#endif 