#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

class State
{
private:
	void (*_stateFunc)(); 

public: 
	State(void (*stateFunc)()) :
		_stateFunc(stateFunc)
	{}

	void operator()()
	{
		_stateFunc(); 
	}
}

class StateMachine
{
	enum Mode
	{
		ManualMode, 
		AutonomousMode,
		ParkingMode, 
		WaitingUserAnswerMode, 
		ObstacleMode
	}
	
	void manualModeMain() 
	{} 

	void autonomousModeMain() 
	{}

	void parkingModeMain()
	{}

	void waitingUserAnswerModeMain()
	{}

	void obstacleModeMain()
	{}
}

#endif