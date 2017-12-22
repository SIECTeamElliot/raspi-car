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

	DDSVar<RW> steeringWheel;
	DDSVar<RW> leftMotorSpeed; 
	DDSVar<RW> rightMotorSpeed; 

	DDSVar<RO> frontUS[3]; 
	DDSVar<RO> rearUS[3]; 
	DDSVar<RO> battery; 
}; 

static DDSCan dds; 

#endif 