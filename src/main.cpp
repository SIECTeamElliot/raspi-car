
#include "../include/Can.hpp"
#include "../include/DDSCan.h"
#include "../include/communicationSTM.h"
#include "../include/lineFinder.h"
#include <iostream>
#include <stdio.h>

using namespace std;

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

    cout << "begin" << endl;
    LineFinder *lf = new LineFinder();
    thread t1 = lf->run();
    
    cout << "motor start" << endl;
//    dds.motorSpeed.write(200);

	for (int i = 0; i < 200; i++)
	{
        tuple<double, double, double> result = lf->getLastResult();
        double command = lf->getLastCommand();
        cout << "offset: " << get<0>(result) << ", \tangle: " << get<1>(result) << ", \tR: " << get<2>(result) <<  ", \tcommand " << command<<endl;

        if (command < -0.5)
		{
			dds.steeringPosFromLeft.write(138);
			dds.print();
		}
		else if (command > 0.5) 
		{
			dds.steeringPosFromLeft.write(88);
			dds.print();
		}
		else 
		{
			dds.steeringPosFromLeft.write(112);
			dds.print();
		}
        this_thread::sleep_for(chrono::milliseconds(100));
        
	}
    cout << "stopping" << endl;
    lf->stop();
    t1.join();
    cout << "ending" << endl;
	return 0; 
}
