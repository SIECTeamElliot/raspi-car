
#include "../include/Can.hpp" 
#include "../include/DDSCan.h"
#include "../include/communicationSTM.h"
#include <iostream>

// void print(int nbBytes, unsigned char * bytes) 
// {
// 	for(int i = 0; i < nbBytes; i++) 
// 	{
// 		std::cout << bytes[i]; 
// 	}
// 	std::cout << std::endl;
// }

DDSCan dds;

char toSpeed(float val) 
{
	char conv; 
	if(val >= 0) 
	{
		conv = (char) 128 * val; 
	}
	else 
	{
		conv = (char) (255 + (val * 128));
	}

	return conv;
}

int main() 
{

//	Can iface; 
//	iface.startListening();
//	while(1){
//		Tests(iface);
//	};



	while(true) 
	{
		dds.motorSpeed.write(127);
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(190);
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(255);
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(50);
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(0);
		dds.print(); 
		sleep(1); 


	}
	return 0; 
}