#ifndef IDS_H
#define IDS_H

#include <type_traits>
#include <limits>

namespace Config
{

	namespace IDs
	{
		namespace emission 
		{
			static const uint32_t motorSpeed = 0x003; 
			static const uint32_t steeringPosFromLeft = 0x001; 
		}

		namespace reception
		{
			static const uint32_t motorSpeed = 0x030; 
			static const uint32_t frontUS = 0x100; 
			static const uint32_t rearUS = 0x110; 
			static const uint32_t positionOther = 0x010; 
		}
		
		static const uint32_t nbFilters = 6; 
		static const uint32_t filters[nbFilters] = {
			reception::motorSpeed, 
			reception::frontUS,
			reception::rearUS, 
			reception::positionOther
		};	
	}

	namespace thresholds
	{
		template <
			class C,
			C MIN = std::numeric_limits<C>::min(),
			C MAX = std::numeric_limits<C>::max()
			>
		struct Threshold
		{
			static const C min = MIN; 
			static const C max = MAX; 
		};

		using steeringWheel = Threshold<uint32_t>; 
		using leftMotorSpeed = Threshold<uint32_t>; 
		using rightMotorSpeed = Threshold<uint32_t>; 
		using frontUS = Threshold<uint32_t>; 
		using rearUS = Threshold<uint32_t>; 
		using battery = Threshold<uint32_t>; 
	}



}

#endif