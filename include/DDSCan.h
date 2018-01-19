#ifndef DDSCAN_H
#define DDSCAN_H

#include "Can.hpp"
#include "DDSVar.hpp"
#include "Config.h"
#include <cassert>

void canListenCallback(uint32_t id, int nbBytes, char * bytes);

class DDSCan
{
private: 
	static Can canBus; 
	friend void canListenCallback(uint32_t id, int nbBytes, char * bytes);

	template <uint8_t ID, class T = int32_t>
	static void sendUpdate(const T& val);


public:
	DDSCan(); 
	virtual ~DDSCan(); 

	void print();

	// Recep ID 0x30
	DDSVar<RO> rightMotorSpeed;
	DDSVar<RO> leftMotorSpeed; 

	// Emiss ID 0x50
	DDSVar<RW> parkOrder; 


	// Emiss ID 0x03
	DDSVar<RW> motorSpeed;

	struct US_struct 
	{
		US_struct() : 
			left(), 
			center(), 
			right()
		{} 
		
		DDSVar<RO> left; 
		DDSVar<RO> center; 
		DDSVar<RO> right; 
	};

	// ID 0x100
	US_struct frontUS; 

	// ID 0x110
	US_struct rearUS; 

	// ID 0x010
	DDSVar<RO> wheelSensorLeft; 
	DDSVar<RO> wheelSensorRight;
	DDSVar<RW> steeringPosFromLeft; // Emiss ID 0x01
 	DDSVar<RO> battery; 
	DDSVar<RO> parkFinished; 
 	
}; 



extern DDSCan dds; 

#endif 