#ifndef DDSVAR_H
#define DDSVAR_H

#include <mutex>
#include <thread>
#include <memory>
#include <type_traits>

class DDSCan; 

enum VarDir_t { RO = 0, RW = 1 };

template <VarDir_t DIR = RW, class T = int32_t> 
class DDSVar 
{
private: 
	std::shared_ptr<T> value; 
	std::mutex mx; 
	friend class DDSCan; 

	void (*onWrite)(const T&);

public: 

	DDSVar(void (*onwrite)(const T&) = nullptr) :
			value( new T ), 
			onWrite(onWrite)
	{}

	inline T read(void)
	{
		T val; 
		mx.lock(); 
		val = value;
		mx.unlock(); 
		return val;  
	}

	template <VarDir_t D = DIR>
	inline
	typename std::enable_if<D == RW, void>::type
	write(const T& val)
	{
		mx.lock(); 
		value = val; 
		onWrite(val);
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
