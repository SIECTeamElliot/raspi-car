#ifndef ALERT_MANAGER_HPP
#define ALERT_MANAGER_HPP 

#include <string>
#include <iostream>
#include <fstream>
#include <boost/unordered_map.hpp>
#include <chrono> 

class AlertManager
{
public: 
	enum AlertType_t 
	{
		obstacle = 0, 
		erreur = 1, 
		place_parking = 2 
	}; 

private: 
	std::string _filename; 
	size_t _timeout_ms; 
	std::chrono::high_resolution_clock::time_point _lastClearDate; 
	boost::unordered_map<AlertType_t, std::string> _mapAlertText; 

public: 
	AlertManager(std::string filename, size_t timeout_ms) : 
		_filename(filename), 
		_timeout_ms(timeout_ms), 
		_mapAlertText()
	{
		std::ofstream file(_filename, std::ofstream::out | std::ofstream::trunc); 
		_lastClearDate = std::chrono::high_resolution_clock::now(); 
		
		_mapAlertText.emplace(obstacle, "Un obstacle se dresse sur le chemin."); 
		_mapAlertText.emplace(erreur, "Une erreur a été détectée"); 
		_mapAlertText.emplace(place_parking, "Une place libre a été trouvée");
	}

	void alert(AlertType_t alert)
	{
		auto duration = std::chrono::high_resolution_clock::now() - _lastClearDate; 	
		std::ofstream file; 

		file.open(_filename, std::ofstream::out | std::ofstream::trunc);
		
		// if(((size_t) std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()) > _timeout_ms)
		// {
		// 	file.open(_filename, std::ofstream::out | std::ofstream::trunc);
		// 	_lastClearDate = std::chrono::high_resolution_clock::now(); 
		// }
		// else 
		// {
		// 	file.open(_filename, std::ofstream::out | std::ofstream::app); 
		// }

		if (file.is_open())
		{
			file << _mapAlertText[alert] << std::endl;
			file.close(); 
		}
	}
};


#endif