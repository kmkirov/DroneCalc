#pragma once

#include "CMotorDetails.h"


namespace DC 
{
	struct CMotorDetailsDecorator 
	{
		CMotorDetails * motor;
		//// members for the solution

		float mf_neededPower;   /// power at 100 % same as effective100
		float mf_neededVoltage; /// volts at 100 % same as effective100
		float mf_neededCurrent; /// current at 100 % same as effective100

		float mf_maxEffPersentage100;      /// efficency persentage att 100 load

		float mf_bestMotorEffectiveness;   /// global best effectiveness
		float mf_bestCurrentEffectiveness; /// best global effectivens

										   /// additional calculation for 70 of load
		float mf_maxEffPersentage70;       /// efeeftivens at 70% load
		float mf_effectiveCurrent70;       /// effectiveness at 70% load
	};
}