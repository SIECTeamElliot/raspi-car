#ifndef DDSVAR_H
#define DDSVAR_H

#include <mutex>
#include <thread>
#include <memory>
#include <type_traits>

class DDSCan; 

enum VarDir_t { RO = 0, RW = 1 };

template <VarDir_t DIR = RW, class T = uint32_t> 
class DDSVar 
{
private: 
	std::shared_ptr<T> value; 
	std::mutex mx; 

	void (*onWrite)(const T&);
	
	friend class DDSCan; 

public:
	DDSVar() : 
		value( new T ), 
		mx(), 
		onWrite(nullptr)
	{}


	DDSVar(void (*p_onwrite)(const T&)) :
			value( new T ), 
			onWrite(p_onwrite)
	{}

	inline T read(void)
	{
		T val; 
		mx.lock(); 
		val = (*value);
		mx.unlock(); 
		return val;  
	}

	template <VarDir_t D = DIR>
	inline
	typename std::enable_if<D == RW, void>::type
	write(const T& val)
	{
		mx.lock(); 
		(*value) = val; 
		if(onWrite != nullptr)
		{
			onWrite(val);
		} 
		mx.unlock();
	}

	void update(const T& val) 
	{
		mx.lock();
#if DEBUG
		std::cout << "[DDSVar] Update value - old : " << *value << " - new : " << val << std::endl;
#endif		
		(*value) = val; 
		mx.unlock(); 
	}

	template <VarDir_t D = DIR>
	inline
	typename std::enable_if<D == RW, T>::type	
	operator=(const T& val) 
	{
		write(val); 
		return read();
	}
};

#endif
