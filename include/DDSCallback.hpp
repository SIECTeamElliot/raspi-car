#ifndef DDS_CALLBACK_H
#define DDS_CALLBACK_H 

#include <DDSVar.hpp>
#include <iostream>

class DDSCallback
{
private: 
	DDSVar<RW, uint32_t > * var; 
	uint32_t  value_false, value_true; 

public: 
	DDSCallback(DDSVar<RW, uint32_t > * v, uint32_t  value_false, uint32_t  value_true) : 
		value_true(value_true), 
		value_false(value_false)
	{
		var = v; 
	}

	void operator()(bool trig_type) 
	{
		if(trig_type) 
		{
			var->write(value_true); 

#ifdef DEBUG
			std::cout << "Write value: " << value_true << std::endl; 
#endif 
		}
		else
		{
			var->write(value_false); 
#ifdef DEBUG
			std::cout << "Write value: " << value_false << std::endl; 
#endif
		}
	}

};

#endif