#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

#include <DDSCan.h>
#include <DDSCallback.hpp>
#include <Config.h>

class EventManager; 

class Event
{
private:
	friend class EventManager; 

	bool value; 
	std::string eventName; 
	
	DDSCallback * ddscallback; 
	void (*callback)(bool); 


	bool inhibited; 

	void inhibit() 
	{
		inhibited = true; 
	}

	void uninhibit() 
	{
		inhibited = false; 
	}

public: 
	Event(std::string eventName, DDSCallback * cb = nullptr) : 
		eventName(eventName), 
		callback(nullptr)
	{
		ddscallback = cb; 
	}

	~Event()
	{}

	void addCallback(void (*cb)(bool))
	{
		callback = cb; 
	}

	void trig_on()
	{
		value = true;
		if(ddscallback != nullptr && !inhibited)
		{
			(*ddscallback)(value); 
		}
		else if(callback != nullptr && !inhibited)
		{
			(*callback)(value); 
		}
#ifdef DEBUG
		std::cout << std::boolalpha; 
		std::cout << "ev: " << eventName << " - value: " << value << std::endl;
#endif 
	}

	void trig_off()
	{
		value = false; 
		if(ddscallback != nullptr && !inhibited)
		{
			(*ddscallback)(value); 
		}
		else if(callback != nullptr && !inhibited)
		{
			(*callback)(value); 
		}
#ifdef DEBUG
		std::cout << std::boolalpha; 
		std::cout << "ev: " << eventName << " - value: " << value << std::endl;
#endif
	}

	bool operator==(std::string& o) 
	{
		return eventName == o; 
	}

	bool operator==(const char o[]) 
	{
		return eventName == o;
	}
};

void print( std::vector <std::string> & v )
{
  for (size_t n = 0; n < v.size(); n++)
    std::cout << "\"" << v[ n ] << "\"\n";
  std::cout << std::endl;
}

class EventManager
{
private: 
	boost::unordered_map<std::string, Event *> eventStrMap;
	std::thread * listenThread; 
	std::string filename;
	const std::string delimiter;
	const std::string keyword_on, keyword_off; 

	bool stopped;

	DDSCan & dds; 

	std::string readLastLine()
	{
		std::ifstream read(this->filename, std::ios_base::trunc | std::ios_base::ate );//open file
	    int length = 0; 

	    char c = '\0';

	    std::string result(""); 

	    if( read )
	    {
	        length = read.tellg();//Get file size

	        // loop backward over the file

	        for(int i = length-2; i > 0; i-- )
	        {
	            read.seekg(i);
	            c = read.get();
	            if( c == '\r' || c == '\n' )//new line?
	                break;
	        }

	        std::getline(read, result);//read last line
        }
        return result; 
	} 


public: 
	EventManager(std::string filename, DDSCan & dds) : 
		filename(filename), 
		delimiter(" "), 
		keyword_on("on"), 
		keyword_off("off"), 
		stopped(false),
		dds(dds)
	{
		listenThread = new std::thread(&EventManager::refreshEvents, this); 

		eventStrMap.emplace("up", new Event("up",
			new DDSCallback(
				&dds.motorSpeed, 
				Config::event_values::motor_speed::neutral, 
				Config::event_values::motor_speed::forwardMax
				)
			)); 

		eventStrMap.emplace("down", new Event("down", 
			new DDSCallback(
				&dds.motorSpeed, 
				Config::event_values::motor_speed::neutral, 
				Config::event_values::motor_speed::backwardMax
				)
			));

		eventStrMap.emplace("left", new Event("left", 
			new DDSCallback(
				&dds.steeringPosFromLeft, 
				Config::event_values::steering_pos::neutral, 
				Config::event_values::steering_pos::left
				)
			));

		eventStrMap.emplace("right", new Event("right", 
			new DDSCallback(
				&dds.steeringPosFromLeft, 
				Config::event_values::steering_pos::neutral,
				Config::event_values::steering_pos::right
				)
			));

		eventStrMap.emplace("stop", new Event("stop"));
		eventStrMap.emplace("yesPark", new Event("yesPark"));
		eventStrMap.emplace("noPark", new Event("noPark"));
		eventStrMap.emplace("autonomous", new Event("autonomous"));
		eventStrMap.emplace("manual", new Event("manual"));

	}

	~EventManager()
	{
		delete listenThread; 
		for(auto it = eventStrMap.begin(); it != eventStrMap.end(); ++it) 
		{
			delete it->second; 
		}
	}

	void eventAddCallback(std::string eventName, void (*callback)(bool))
	{
		auto it = eventStrMap.find(eventName);
    	if( it != eventStrMap.end())
    	{
    		it->second->addCallback(callback);
    	}
	}

	void refreshEvents()
	{
		std::string prev(""); 
	    std::string tmp("");
	    while (true)
	    {
	        std::string tmp = this->readLastLine(); 

	        if(tmp != prev) 
	        {
	        	std::vector<std::string> tokens; 
	        	boost::split(tokens, tmp, boost::is_any_of(" ")); 

	        	// std::cout << tokens.size(); 
	        	// print(tokens);
	        	auto it = eventStrMap.find(tokens[0]);
	        	if( it != eventStrMap.end())
	        	{
	        		if(tokens[1] == keyword_on) 
        			{
        				it->second->trig_on(); 
        			}
        			else if(tokens[1] == keyword_off)
        			{
        				it->second->trig_off(); 
        			}
	        	} 
	        }
	        prev = tmp; 

	        usleep(5000);
	    }
	}

	void stopTeleop() 
	{
    	eventStrMap["up"]->inhibit(); 
    	eventStrMap["down"]->inhibit(); 
    	eventStrMap["left"]->inhibit(); 
    	eventStrMap["right"]->inhibit(); 
	}

	void startTeleop() 
	{
		eventStrMap["up"]->uninhibit(); 
    	eventStrMap["down"]->uninhibit(); 
    	eventStrMap["left"]->uninhibit(); 
    	eventStrMap["right"]->uninhibit(); 
	}

};

#endif