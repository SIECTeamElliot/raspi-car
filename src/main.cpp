#define DEBUG true

#include "../include/Can.h"
#include "../include/communicationSTM.h"

int main() 
{
	Can iface; 
	Tests(iface);
	return 0; 
}