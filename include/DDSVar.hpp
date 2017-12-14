#ifndef DDSVAR_H
#define DDSVAR_H

#include <mutex>
#include <thread>
#include <memory>

class DDSCan; 

template <class T = uint8_t> 
class DDSVar 
{
private: 
	std::shared_ptr<T> value; 
	std::mutex mx; 
	friend class DDSCan; 

	void (*onWrite)(const T&) = nullptr;

public: 
	DDSVar(void (*onwrite)(const T&)) : 
			value( new T ), 
			onWrite(onWrite)
	{}

	inline T read(void) const
	{
		T val; 
		mx.lock(); 
		val = value;
		mx.unlock(); 
		return val;  
	}

	inline void write(const T& val)
	{
		mx.lock(); 
		onWrite(T);
		value = val; 
		mx.unlock();
	}

	inline T operator=(const T& val) 
	{
		write(val); 
		return read();
	}
};

#endif
