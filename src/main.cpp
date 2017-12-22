
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

int main() 
{

//	Can iface; 
//	iface.startListening();
//	while(1){
//		Tests(iface);
//	};

	while(true) 
	{
		dds.motorSpeed.write(0);
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(static_cast<char>(0.2));
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(static_cast<char>(0.8));
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(static_cast<char>(-0.2));
		dds.print(); 
		sleep(1); 

		dds.motorSpeed.write(static_cast<char>(-0.8));
		dds.print(); 
		sleep(1); 


	}
	return 0; 
}