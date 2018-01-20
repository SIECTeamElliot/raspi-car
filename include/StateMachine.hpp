#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <DDSCan.h>
#include <EventManager.hpp>
#include <AlertManager.hpp>
#include <MainFunctions.h>

#include <boost/unordered_map.hpp>
#include <vector>



enum EnumState_t
{
	ManualMode = 0, 
	AutonomousMode = 1,
	ParkingMode = 2, 
	WaitingUserAnswerMode = 3, 
	ObstacleMode = 4
};

class State
{
private: 
	void (*stateExecFunc)(); 

public: 
	State(void (*func)()) : 
		stateExecFunc(func)
	{}

	void operator()() 
	{
		(*stateExecFunc)(); 
	}
};


class Transition 
{
private: 
	EnumState_t _inputState;
	EnumState_t _outputState;
	bool (*_eval)(); 
	int _priority; 

public: 
	Transition(
		EnumState_t inputState, 
		EnumState_t outputState, 
		int priority, 
		bool (*evalFunc)()) : 
		_inputState(inputState),
		_outputState(outputState),
		_eval(evalFunc),
		_priority(priority) 
	{}

	EnumState_t getInputState() 
	{
		return _inputState; 
	}

	EnumState_t getOutputState() 
	{
		return _outputState; 
	}

	int getPriority()
	{
		return _priority; 
	}

	bool operator()()
	{
		return (*_eval)();
	}
}; 


class StateMachine
{
public: 
	DDSCan * dds;
	EventManager * ev; 
	AlertManager * am; 

private:
	EnumState_t currentState; 
	boost::unordered_map<EnumState_t, State *> stateMap; 
	std::vector<Transition *> transitionsVect; 

	void checkTransitions()
	{
		int priorityMax = 0; 
		Transition * bestTransition; 

		for(auto it = transitionsVect.begin(); it != transitionsVect.end(); ++it) 
		{
			if((**it)())
			{
				if((*it)->getInputState() == currentState && (*it)->getPriority() >= priorityMax )  
				{
					bestTransition = (*it); 
				}
			}
		}

		currentState = bestTransition->getOutputState(); 
	}

	void executeStateOnce() 
	{
		(*stateMap[currentState])(); 
	}

public: 
	StateMachine(DDSCan * dds, EventManager * ev, AlertManager * am, EnumState_t initState) : 
		dds(dds), 
		ev(ev), 
		am(am), 
		currentState(initState)
	{
		stateMap.emplace(ManualMode, new State(&manualModeMain)); 
		stateMap.emplace(AutonomousMode, new State(&autonomousModeMain)); 
		stateMap.emplace(ParkingMode, new State(&parkingModeMain)); 
		stateMap.emplace(WaitingUserAnswerMode, new State(&waitingUserAnswerModeMain)); 
		stateMap.emplace(ObstacleMode, new State(&obstacleModeMain)); 

	}

	virtual ~StateMachine() 
	{
		for(auto it = stateMap.begin(); it != stateMap.end(); ++it) 
		{
			delete it->second; 
		}
	}

	void operator()()
	{
		checkTransitions(); 
		executeStateOnce(); 
	}	
};



#endif