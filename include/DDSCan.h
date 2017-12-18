#ifndef DDSCAN_H
#define DDSCAN_H

#include "Can.h"
#include "DDSVar.hpp"

class DDSCan
{
private: 
	void canListenCallback(int nbBytes, unsigned char * bytes);

	static Can canBus; 

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

#endif 