
#include "../include/Can.hpp" 
#include "../include/DDSCan.h"
#include "../include/communicationSTM.h"
#include <iostream>
#include <EventManager.hpp>
#include <AlertManager.hpp>

// void print(int nbBytes, unsigned char * bytes) 
// {
// 	for(int i = 0; i < nbBytes; i++) 
// 	{
// 		std::cout << bytes[i]; 
// 	}
// 	std::cout << std::endl;
// }

DDSCan dds;
EventManager ev("../../communication_file.txt", dds); 
AlertManager am("../../lecture.txt", 1000); 


int main() 
{
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
			usleep(3000000);
			dds.motorSpeed.write(127);
			sleep(2);			

			dds.steeringPosFromLeft.write(112);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(3200000);
			dds.motorSpeed.write(127);
/*	while(true) 
	{

 		if(dds.frontUS.left.read() < 20 || dds.frontUS.right.read() < 20 || dds.frontUS.center.read() < 20)
		{
			dds.motorSpeed.write(127);
			dds.steeringPosFromLeft.write(112);
			dds.print();
			sleep(1);
		}

		else if
		{
			//add manoeuvre
			dds.steeringPosFromLeft.write(88);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(3400000);

			dds.steeringPosFromLeft.write(138);
			sleep(2);
			dds.motorSpeed.write(190);
			usleep(3000000);

			dds.steeringPosFromLeft.write(88);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(3000000);

			dds.steeringPosFromLeft.write(112);
			sleep(2);
			dds.motorSpeed.write(70);
			usleep(3200000);
			dds.motorSpeed.write(0);
	
		}

	}*/
}