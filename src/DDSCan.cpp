#include "../include/DDSCan.h"

#define ID_STEERING_WHEEL 0
#define ID_LEFT_MOTOR_SPEED 1
#define ID_RIGHT_MOTOR_SPEED 2

Can DDSCan::canBus(Config::IDs::nbFilters, Config::IDs::filters); 

DDSCan::DDSCan() : 
	motorSpeed(&DDSCan::sendUpdate<Config::IDs::emission::motorSpeed>), 
	steeringPosFromLeft(&DDSCan::sendUpdate<Config::IDs::emission::steeringPosFromLeft>)
{
#ifdef DEBUG
	std::cout << "Init. DDSCan" << std::endl;
#endif
	canBus.startListening(&canListenCallback); 
}

DDSCan::~DDSCan() 
{}

template <uint8_t ID, class T>
void DDSCan::sendUpdate(const T& val)
{
#ifdef DEBUG
	std::cout << "[DDS] Sending update to id ID with value : " << val << std::endl;
#endif
	struct can_frame frame; 
	frame.can_id = ID; 
	frame.can_dlc = 1; 
	frame.data[0] = val; 
	canBus.sendFrame(&frame); 
}

void canListenCallback(uint32_t id, int nbBytes, char * bytes)
{
#ifdef DEBUG 
	std::cout << "[DDS] Received frame with id " << id << ", length " << nbBytes << std::endl; 
#endif 
	switch(id) 
	{
		case Config::IDs::reception::frontUS:
			// assert(nbBytes == 6); 

			// for(int i = 0; i < 3; i++)
			// {
			// 	assert(bytes[i] < Config::thresholds::frontUS::max); 
			// 	assert(bytes[i] > Config::thresholds::frontUS::min);	
			// }

			dds.frontUS.left.update((bytes[0] << 8) + bytes[1]); 
			dds.frontUS.center.update((bytes[2] << 8) + bytes[3]); 
			dds.frontUS.right.update((bytes[4] << 8) + bytes[5]); 

			break; 

		case Config::IDs::reception::rearUS:
			// assert(nbBytes == 3); 

			// for(int i = 0; i < 3; i++)
			// {
			// 	assert(bytes[i] < Config::thresholds::rearUS::max); 
			// 	assert(bytes[i] > Config::thresholds::rearUS::min);	
			// }

			dds.rearUS.left.update((bytes[0] << 8) + bytes[1]); 
			dds.rearUS.center.update((bytes[2] << 8) + bytes[3]); 
			dds.rearUS.right.update((bytes[4] << 8) + bytes[5]); 

			break; 

		case Config::IDs::reception::motorSpeed:
			// assert(nbBytes == 1); 
			// assert(bytes[0] < Config::thresholds::battery::max); 
			// assert(bytes[0] > Config::thresholds::battery::min);

			dds.rightMotorSpeed.update((bytes[0] << 8 ) + bytes[1]);
			dds.leftMotorSpeed.update((bytes[2] << 8 ) + bytes[3]);
			dds.motorSpeed.update(((bytes[0] << 8 ) + bytes[1] + (bytes[2] << 8 ) + bytes[3]) / 2);

			break; 

		case Config::IDs::reception::positionOther: 
			// assert(nbBytes == 1); 
			// assert(bytes[0] < Config::thresholds::steeringWheel::max); 
			// assert(bytes[0] > Config::thresholds::steeringWheel::min);

			dds.wheelSensorLeft.update((bytes[0] << 8 ) + bytes[1]);
			dds.wheelSensorRight.update((bytes[2] << 8 ) + bytes[3]);
			dds.steeringPosFromLeft.update((bytes[4] << 8 ) + bytes[5]);
			dds.battery.update((bytes[6] << 8 ) + bytes[7]);

			break; 
	}
}