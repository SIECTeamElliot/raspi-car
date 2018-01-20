
#include "../include/Can.hpp" 
#include "../include/DDSCan.h"
#include "../include/communicationSTM.h"
#include <iostream>
#include <EventManager.hpp>
#include <AlertManager.hpp>


DDSCan dds;
EventManager ev("../../communication_file.txt", dds); 
AlertManager am("../../lecture.txt", 1000); 


int main() 
{/*
			dds.steeringPosFromLeft.write(88);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(3400000);
			dds.motorSpeed.write(127);
			sleep(2);

			dds.steeringPosFromLeft.write(138);
			sleep(2);
			dds.motorSpeed.write(190);
			usleep(3000000);
			dds.motorSpeed.write(127);
			sleep(2);

			dds.steeringPosFromLeft.write(88);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(4000000); //3.2
			dds.motorSpeed.write(127);
			sleep(2);			

			dds.steeringPosFromLeft.write(112);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(3200000);
			dds.motorSpeed.write(127);*/
	while(true) 
	{
		dds.motorSpeed.write(180);

 		if((dds.frontUS.center.read() < 40)  || (dds.frontUS.right.read() < 40) || (dds.frontUS.left.read() < 40))
		{
			dds.motorSpeed.write(127);
			dds.steeringPosFromLeft.write(112);
		}		
	}
}