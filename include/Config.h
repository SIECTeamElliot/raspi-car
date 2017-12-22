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
			static const uint32_t steeringWheel = 0x001; 
			static const uint32_t leftMotorSpeed = 0x003; 
			static const uint32_t rightMotorSpeed = 0x003; 
			static const uint32_t frontUS = 4; 
			static const uint32_t rearUS = 5; 
			static const uint32_t battery = 6; 
		}

		namespace reception
		{
			static const uint32_t steeringWheel = 0x999; 
			static const uint32_t leftMotorSpeed = 0x998; 
			static const uint32_t rightMotorSpeed = 0x30; 
			static const uint32_t frontUS = 4; 
			static const uint32_t rearUS = 5; 
			static const uint32_t battery = 0x800; 
		}
		
		static const uint32_t nbFilters = 6; 
		static const uint32_t filters[nbFilters] = {
			reception::steeringWheel, 
			reception::leftMotorSpeed,
			reception::rightMotorSpeed, 
			reception::frontUS, 
			reception::rearUS, 
			reception::battery
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