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
	ev.stopTeleop(); 

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
    delete lf; 
}

void parkingModeMain()
{

	while(true) 
	{
		dds.motorSpeed.write(180);

		if(dds.frontUS.left.read() < 40)
		{
			dds.motorSpeed.write(127);
			dds.steeringPosFromLeft.write(112);
			dds.print();
			sleep(1);
		}
		else if(dds.frontUS.right.read() < 40)
		{
			dds.motorSpeed.write(127);
			dds.steeringPosFromLeft.write(112);
			dds.print();
			sleep(1);
		}
		else if (dds.frontUS.center.read() < 40)
		{
			dds.motorSpeed.write(127);
			dds.steeringPosFromLeft.write(112);
			dds.print();
			sleep(1);		
		}

	}	
}

void waitingUserAnswerModeMain()
{}

void obstacleModeMain()
{
	dds.motorSpeed.write(127); 
}