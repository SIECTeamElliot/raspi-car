#ifndef IDS_H
#define IDS_H

#include <type_traits>
#include <limits>

namespace Config
{

	namespace IDs
	{
		static const uint32_t steeringWheel = 1; 
		static const uint32_t leftMotorSpeed = 2; 
		static const uint32_t rightMotorSpeed = 3; 
		static const uint32_t frontUS = 4; 
		static const uint32_t rearUS = 5; 
		static const uint32_t battery = 6; 


		static const uint32_t nbFilters = 6; 
		static const uint32_t filters[nbFilters] = {
			steeringWheel, 
			leftMotorSpeed,
			rightMotorSpeed, 
			frontUS, 
			rearUS, 
			battery
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