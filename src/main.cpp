
#include "../include/Can.hpp"
#include "../include/DDSCan.h"
#include "../include/communicationSTM.h"
#include "../include/lineFinder.h"
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
    LineFinder *lf = new LineFinder();
    thread t1 = lf->run();
    int i = 0;
    while (i < 1000) {
        tuple<double, double, double> result = lf->getLastResult();
        double command = lf->getLastCommand();
        cout << "offset: " << get<0>(result) << ", \tangle: " << get<1>(result) <<  ", \tcommand " << command<<endl;
        i++;
        //waitKey(100);
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << "stopping" << endl;
    lf->stop();
    t1.join();
    cout << "ending" << endl;
    
	while(true) 
	{

 		if(dds.frontUS.left.read() > 2000 || dds.frontUS.right.read() > 2000 || dds.frontUS.center.read() > 2000)
		{
			dds.motorSpeed.write(255);
			dds.steeringPosFromLeft.write(112);
			dds.print();
			sleep(1);
		}
		else 
		{
			dds.motorSpeed.write(127);
			dds.steeringPosFromLeft.write(112);
			dds.print();
			sleep(1);
		}
	}
	return 0; 
}
