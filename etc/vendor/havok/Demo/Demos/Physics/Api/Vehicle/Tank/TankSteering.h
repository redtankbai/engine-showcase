/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2008 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_TANK_STEERING_H
#define HK_TANK_STEERING_H

#include <Physics/Vehicle/Steering/Default/hkpVehicleDefaultSteering.h>

	/// Tank specific steering implementation. Rear wheels steer in opposite direction
	/// to front wheels.
class TankSteering: public hkpVehicleDefaultSteering
{
	public:

		/// Calculates information about the effects of steering on the vehicle.
		virtual void calcSteering(const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredInfoOutput, SteeringAnglesOutput& steeringOutput );
};

#endif // HK_TANK_STEERING_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20080925)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2008
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/