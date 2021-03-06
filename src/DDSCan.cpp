#include "../include/DDSCan.h"


Can DDSCan::canBus(Config::IDs::nbFilters, Config::IDs::filters); 


DDSCan::DDSCan() : 
	rightMotorSpeed(), 
	leftMotorSpeed(), 
	parkOrder(&DDSCan::sendUpdate<Config::IDs::emission::parkOrder>),
	motorSpeed(&DDSCan::sendUpdate<Config::IDs::emission::motorSpeed>), 
	frontUS(), 
	rearUS(), 
	wheelSensorLeft(), 
	wheelSensorRight(), 
	steeringPosFromLeft(&DDSCan::sendUpdate<Config::IDs::emission::steeringPosFromLeft>), 
	battery(), 
	parkFinished()
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

			dds.frontUS.left.update((bytes[1] << 8) + bytes[0]); 
			dds.frontUS.center.update((bytes[3] << 8) + bytes[2]); 
			dds.frontUS.right.update((bytes[5] << 8) + bytes[4]); 

			break; 

		case Config::IDs::reception::rearUS:
			// assert(nbBytes == 3); 

			// for(int i = 0; i < 3; i++)
			// {
			// 	assert(bytes[i] < Config::thresholds::rearUS::max); 
			// 	assert(bytes[i] > Config::thresholds::rearUS::min);	
			// }

			dds.rearUS.left.update((bytes[1] << 8) + bytes[0]); 
			dds.rearUS.center.update((bytes[3] << 8) + bytes[2]); 
			dds.rearUS.right.update((bytes[5] << 8) + bytes[4]); 

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

			dds.wheelSensorLeft.update(bytes[0]);
			dds.wheelSensorRight.update(bytes[1]);
			dds.steeringPosFromLeft.update(bytes[2]);
			dds.battery.update(bytes[3]);
			dds.parkFinished.update(bytes[4]);

			break; 
	}
}

void DDSCan::print()
{
	std::cout << "---------- DDS ------------" << std::endl;
	std::cout << "rightMotorSpeed : " << rightMotorSpeed.read() << std::endl;
	std::cout << "leftMotorSpeed : " << leftMotorSpeed.read() << std::endl;
	std::cout << "motorSpeed : " << motorSpeed.read() << std::endl;
	
	std::cout << std::hex; 

	std::cout << "frontUS.left : " << frontUS.left.read() << std::endl;
	std::cout << "frontUS.center : " << frontUS.center.read() << std::endl;
	std::cout << "frontUS.right : " << frontUS.right.read() << std::endl;
	std::cout << "rearUS.left : " << rearUS.left.read() << std::endl;
	std::cout << "rearUS.center : " << rearUS.center.read() << std::endl;
	std::cout << "rearUS.right : " << rearUS.right.read() << std::endl;

	std::cout << std::dec; 
	
	std::cout << "wheelSensorLeft : " << wheelSensorLeft.read() << std::endl;
	std::cout << "wheelSensorRight : " << wheelSensorRight.read() << std::endl;
	std::cout << "steeringPosFromLeft : " << steeringPosFromLeft.read() << std::endl;
	std::cout << "battery : " << battery.read() << std::endl;
	std::cout << std::boolalpha; 
	std::cout << "parkOrder : " << parkOrder.read() << std::endl;
	std::cout << "---------------------------" << std::endl;
}