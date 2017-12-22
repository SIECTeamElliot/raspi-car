#include "../include/DDSCan.h"

#define ID_STEERING_WHEEL 0
#define ID_LEFT_MOTOR_SPEED 1
#define ID_RIGHT_MOTOR_SPEED 2

Can DDSCan::canBus(Config::IDs::nbFilters, Config::IDs::filters); 

DDSCan::DDSCan() : 
	steeringWheel(&DDSCan::sendUpdate<Config::IDs::emission::steeringWheel>), 
	leftMotorSpeed(&DDSCan::sendUpdate<Config::IDs::emission::leftMotorSpeed>), 
	rightMotorSpeed(&DDSCan::sendUpdate<Config::IDs::emission::rightMotorSpeed>)
{
#if DEBUG
	std::cout << "Init. DDSCan" << std::endl;
#endif
	canBus.startListening(&canListenCallback); 
}

DDSCan::~DDSCan() 
{}

template <uint8_t ID, class T = int32_t>
void DDSCan::sendUpdate(const T& val)
{
#if DEBUG
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
#if DEBUG 
	std::cout << "[DDS] Received frame with id " << id << ", length " << nbBytes << std::endl; 
#endif 
	switch(id) 
	{
		case Config::IDs::reception::frontUS:
			assert(nbBytes == 3); 

			for(int i = 0; i < 3; i++)
			{
				assert(bytes[i] < Config::thresholds::frontUS::max); 
				assert(bytes[i] > Config::thresholds::frontUS::min);	
			}

			// steeringWheel.write(bytes[0]);

			break; 

		case Config::IDs::reception::rearUS:
			assert(nbBytes == 3); 

			for(int i = 0; i < 3; i++)
			{
				assert(bytes[i] < Config::thresholds::rearUS::max); 
				assert(bytes[i] > Config::thresholds::rearUS::min);	
			}

			// steeringWheel.write(bytes[0]);

			break; 

		case Config::IDs::reception::battery:
			assert(nbBytes == 1); 
			assert(bytes[0] < Config::thresholds::battery::max); 
			assert(bytes[0] > Config::thresholds::battery::min);

			dds.battery.update(bytes[0]);

			break; 

		case Config::IDs::reception::steeringWheel: 
			assert(nbBytes == 1); 
			assert(bytes[0] < Config::thresholds::steeringWheel::max); 
			assert(bytes[0] > Config::thresholds::steeringWheel::min);

			dds.steeringWheel.update(bytes[0]);

			break; 

		case Config::IDs::reception::leftMotorSpeed: 
			assert(nbBytes == 1); 
			assert(bytes[0] < Config::thresholds::leftMotorSpeed::max); 
			assert(bytes[0] > Config::thresholds::leftMotorSpeed::min);

			dds.leftMotorSpeed.update(bytes[0]);

			break; 

		case Config::IDs::reception::rightMotorSpeed: 
			assert(nbBytes == 1); 
			assert(bytes[0] < Config::thresholds::rightMotorSpeed::max); 
			assert(bytes[0] > Config::thresholds::rightMotorSpeed::min);

			dds.rightMotorSpeed.update(bytes[0]);

			break; 
	}
}