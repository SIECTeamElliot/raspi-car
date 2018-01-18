#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <vector>

#include <DDSCan.h>
#include <DDSCallback.hpp>

class Event
{
private: 
	bool value; 
	std::string eventName; 
	DDSCallback * callback; 

public: 
	Event(std::string eventName, DDSCallback * cb = nullptr) : 
		eventName(eventName)
	{
		callback = cb; 
	}

	~Event()
	{}

	void trig_on()
	{
		value = true;
		if(callback != nullptr)
		{
			(*callback)(value); 
		}
		std::cout << std::boolalpha; 
		std::cout << "ev: " << eventName << " - value: " << value << std::endl;
	}

	void trig_off()
	{
		value = false; 
		if(callback != nullptr)
		{
			(*callback)(value); 
		}
		std::cout << std::boolalpha; 
		std::cout << "ev: " << eventName << " - value: " << value << std::endl;
	}

	bool operator==(std::string& o) 
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
	std::vector<Event *> eventList; 
	std::thread * listenThread; 
	std::string filename;
	const std::string delimiter;
	const std::string keyword_on, keyword_off; 

	DDSCan & dds; 

	std::string readLastLine()
	{
		std::ifstream read(this->filename, std::ios_base::ate );//open file
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
		dds(dds)
	{
		listenThread = new std::thread(&EventManager::refreshEvents, this); 
		eventList.push_back(new Event("up", new DDSCallback(&dds.motorSpeed, 127, 254)));
		eventList.push_back(new Event("down", new DDSCallback(&dds.motorSpeed, 127, 0)));
		eventList.push_back(new Event("left", new DDSCallback(&dds.steeringPosFromLeft, 112, 138)));
		eventList.push_back(new Event("right", new DDSCallback(&dds.steeringPosFromLeft, 112, 88)));
		eventList.push_back(new Event("stop"));
		eventList.push_back(new Event("yesPark"));
		eventList.push_back(new Event("noPark"));
		eventList.push_back(new Event("autonomous"));
		eventList.push_back(new Event("manual"));
	}

	~EventManager()
	{
		delete listenThread; 
		for(auto it = eventList.begin(); it != eventList.end(); ++it) 
		{
			delete *it; 
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

	        	for( auto it = this->eventList.begin(); it != this->eventList.end(); ++it )
	        	{
	        		if(**it == tokens[0])
	        		{
	        			if(tokens[1] == keyword_on) 
	        			{
	        				(*it)->trig_on(); 
	        			}
	        			else if(tokens[1] == keyword_off)
	        			{
	        				(*it)->trig_off(); 
	        			}
	        			break; 
	        		}
	        	}
	        }
	        prev = tmp; 

	        usleep(5000);
	    }
	}

};

#endif