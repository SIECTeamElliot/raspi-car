#define DEBUG true

#include "../include/Can.h"
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

int main() 
{
	Can iface; 
	iface.startListening();
	Tests(iface);
	while(1);	

	return 0; 
}