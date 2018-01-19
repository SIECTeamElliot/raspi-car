
#include "../include/Can.hpp"
#include "../include/DDSCan.h"
#include "../include/communicationSTM.h"
#include "../include/lineFinder.h"
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <EventManager.hpp>
#include <AlertManager.hpp>


using namespace std;

DDSCan dds;
EventManager ev("../../communication_file.txt", dds); 
AlertManager am("../../lecture.txt", 1000); 

static volatile int keepRunning = 1;

void intHandler(int dummy){
    keepRunning = 0;
}

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

    signal(SIGINT, intHandler);
    cout << "begin" << endl;
    LineFinder *lf = new LineFinder();
    thread t1 = lf->run();
    
    cout << "motor start" << endl;
    dds.motorSpeed.write(166);

	for (int i = 0; i < 200; i++)
	{
        tuple<double, double, double> result = lf->getLastResult();
        double command = lf->getLastCommand();
        cout << "offset: " << get<0>(result) << ", \tangle: " << get<1>(result) << ", \tR: " << get<2>(result) <<  ", \tcommand " << command<<endl;

        if (command < -0.5)
		{
			//dds.steeringPosFromLeft.write(138);
			dds.steeringPosFromLeft.write(128);
			dds.print();
		}
		else if (command > 0.5) 
		{
			dds.steeringPosFromLeft.write(98);
			//dds.steeringPosFromLeft.write(88);
			dds.print();
		}
		else 
		{
			dds.steeringPosFromLeft.write(112);
			dds.print();
		}
        if (keepRunning == 0)
            break;

        this_thread::sleep_for(chrono::milliseconds(100));
        
	}
    cout << "stopping" << endl;
    dds.motorSpeed.write(127);
    lf->stop();
    t1.join();
    cout << "ending" << endl;

//	Can iface; 
//	iface.startListening();
//	while(1){
//		Tests(iface);
//	};	

#ifdef ROLL
	while(true) 
#else 

#ifdef PARK
	while( dds.parkFinished.read() == 0 )
	{
		dds.parkOrder.write(1)	; 
		dds.print(); 
		sleep(1);
	}
#else 
	int state = 0; 
	while(true)
	{
		if(state == 0)
		{
			am.alert(AlertManager::obstacle);
			am.alert(AlertManager::obstacle);
			am.alert(AlertManager::obstacle);
			am.alert(AlertManager::obstacle);
			am.alert(AlertManager::obstacle);
			state++; 
		} 
		else if (state == 1) 
		{
			am.alert(AlertManager::erreur); 
			state++; 
		} 
		else if (state == 2)
		{
			am.alert(AlertManager::place_parking); 
			state = 0; 
		} 
		dds.print();
		sleep(1);
	}
#endif

#endif
	return 0; 
}
