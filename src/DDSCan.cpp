#include "../include/DDSCan.h"

#define ID_STEERING_WHEEL 0
#define ID_LEFT_MOTOR_SPEED 1
#define ID_RIGHT_MOTOR_SPEED 2

Can DDSCan::canBus; 

DDSCan::DDSCan() : 
	steeringWheel(&DDSCan::sendUpdate<ID_STEERING_WHEEL>), 
	leftMotorSpeed(&DDSCan::sendUpdate<ID_LEFT_MOTOR_SPEED>), 
	rightMotorSpeed(&DDSCan::sendUpdate<ID_RIGHT_MOTOR_SPEED>)
{}

DDSCan::~DDSCan() 
{}

template <uint8_t ID, class T = int32_t>
void DDSCan::sendUpdate(const T& val)
{
	struct can_frame frame; 
	frame.can_id = ID; 
	frame.can_dlc = 1; 
	frame.data[0] = val; 
	canBus.sendFrame(&frame); 
}