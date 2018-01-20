
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

void manualModeMain() 
{
	ev.startTeleop();
} 

static volatile int keepRunning = 1;

void intHandler(int dummy){
    keepRunning = 0;
}

void autonomousModeMain() 
{
    signal(SIGINT, intHandler);
    LineFinder *lf = new LineFinder();
    thread t1 = lf->run();

	for(int i = 0; i < 200; ++i)
	{
		dds.motorSpeed.write(166);

        tuple<double, double, double> result = lf->getLastResult();
        double command = lf->getLastCommand();
        // cout << "offset: " << get<0>(result) << ", \tangle: " << get<1>(result) << ", \tR: " << get<2>(result) <<  ", \tcommand " << command<<endl;

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
        command = command * (-25.) + 113.;
        if (command > 138) command = 138;
        if (command < 88) command = 88;
		dds.steeringPosFromLeft.write(command);
        
        if (keepRunning == 0)
            break;

        this_thread::sleep_for(chrono::milliseconds(100));
	}
    dds.motorSpeed.write(127);
    lf->stop();
    t1.join();
    delete lf;
}

void parkingModeMain()
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
	usleep(4000000); //3.2
	dds.motorSpeed.write(127);
	sleep(2);			
	dds.steeringPosFromLeft.write(112);
	sleep(2);
	dds.motorSpeed.write(70);
	usleep(3200000);
	dds.motorSpeed.write(127);
}

void obstacleModeMain()
{
	dds.motorSpeed.write(127); 
}

bool checkUS()
{
	return (dds.frontUS.left.read() < 50) 
		|| (dds.frontUS.center.read() < 50) 
		|| (dds.frontUS.center.read() < 50); 
}

enum State_t 
{
	Stop = 0, 
	RoulerManuel = 1, 
	RoulerAutonome = 2, 
	Manoeuvre = 3
}; 


int main() 
{
	State_t etatCourant = Stop; 
	bool signalStopModeAuto = false; 

	int count = 0; 

	while(true)
	{
		// Transitions 
		switch(etatCourant) 
		{
			case Stop: 
				if(!checkUS())
				{
					etatCourant = RoulerManuel; 
				}
				break;

			case RoulerManuel: 
				if(checkUS())
				{
					etatCourant = Stop; 
				}
				else if(ev.checkEvent("autonomous"))
				{
					etatCourant = RoulerAutonome; 
				}
				else if(ev.checkEvent("yesPark"))
				{
					etatCourant = Manoeuvre; 
				}
				break;

			case RoulerAutonome: 
				if(checkUS())
				{
					etatCourant = Stop; 
				}
				else if(ev.checkEvent("manual"))
				{
					etatCourant = RoulerManuel; 
				}
				else if(ev.checkEvent("yesPark"))
				{
					etatCourant = Manoeuvre; 
				}
				break;

			case Manoeuvre: 
				if(checkUS())
				{
					etatCourant = Stop; 
				}
				else
				{
					etatCourant = RoulerManuel; 
				}
				break;
		}

		// Execution des états
		switch(etatCourant) 
		{
			case Stop: 
				ev.stopTeleop(); 
				dds.motorSpeed.write(127); 
				dds.steeringPosFromLeft.write(112); 
				am.alert(AlertManager::obstacle);
				break;

			case RoulerManuel: 
				ev.startTeleop(); 
				break;

			case RoulerAutonome: 
				ev.stopTeleop(); 
				autonomousModeMain(); 
				break;

			case Manoeuvre: 
				ev.stopTeleop(); 
				parkingModeMain(); 
				break;
		}

		count++; 
		if(count > 100000) 
		{
			count = 0;
			std::cout << "Etat courant : " << etatCourant << std::endl;
			dds.print();
		}
	}

	return 0;
}
