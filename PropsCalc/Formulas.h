#pragma once
//////////////////////////////////////////////
//// Includes
/////////////////////////////////
#include <math.h>  
#include <iostream>
//////////////////////////////////////
///// Constants
///////////////////////
const float PI = 3.14159265359; 
const float RHO = 1.225; /// air density
const float KvKtConstant = 1355;///
const float G = 9.8;///

//// thrust 30 str ot uchebnika 
/// thrust = 550 * horsepower/ speed(ft/sec)
/// thrust = 375 * hp/speed(mile per hour
float thrustFromHorsePowerInFTPerSecond(float hoursePower, float speed) 
{
	return 550 * hoursePower * speed;
}

float thrustFromHorsePowerInMph(float hoursePower, float speed)
{
	return 375 * hoursePower * speed;
}

float kiloWattsToHorsePowerConverter(float powerInKiloWatts) 
{
	return (powerInKiloWatts / 1000 )*1.34;
}


float getTorque(float KtConstant, float amps) 
{
	return KtConstant * amps;
}
////////////////////////////////////////////
///// formula 2
float practivalPowerCalculation(float propelerConst, float motorRPM, float powerFactor)
{
	return propelerConst * pow(motorRPM, powerFactor);
}

float massOfThrust(float propellerDiameter, float calculatedPracticalPower) 
{
	return pow(((PI / 2) * pow(propellerDiameter, 2.0) * RHO * pow(calculatedPracticalPower, 2.0)), 0.333) / G;
}




 
float calcPowerElectricity( float propellerDiameter,
							float propellerPitch,
							float motorRPM, 
							float propCoefFiction = 1.31 )
{
	return propCoefFiction * pow(propellerDiameter, 4.0) * propellerPitch * pow(motorRPM, 3.0);
}


////////////////////////////////
///////////

float calculateStaticThrustEquation(float propellerDiameter, float bladesNumber, float motorRPM, float horsepower, float propellerPitch)
{
	return 6000 * (18, 7 - 9, 5 * propellerPitch / propellerDiameter) *bladesNumber * horsepower / (motorRPM * propellerDiameter);
}

//float calculateCT(float thrustCalculatedBySpecialFormula, float numberOfBlades, float propellerDiameter) 
//{
//	return thrustCalculatedBySpecialFormula / (RHO * pow(numberOfBlades, 2.0) * pow(propellerDiameter, 4.0));
//}
//
//float calculateCP(float PCalculatedBySpecialFormula, float numberOfBlades, float propellerDiameter)
//{
//	return PCalculatedBySpecialFormula / (RHO* pow(numberOfBlades, 3.0) * pow(propellerDiameter, 5.0));
//}

float thrustEq2(float powerOfSystem, float effProp, float effMotor, float propellerDiameter) 
{
		return pow(pow(powerOfSystem * effProp * effMotor * propellerDiameter, 2.0) * PI * RHO / 2, 0.333);
}

float calcCoefForPropeler(float propellerDiameter, float propellerPitch)
{
	return 0.1;
	if (0.33 > propellerPitch / propellerDiameter < 0.5)
	{
		//std::cout << (0.075 + propellerPitch / propellerDiameter * 0.025) << std::endl;
		return (0.075 + propellerPitch / propellerDiameter * 0.025);
	}
	else if (propellerPitch / propellerDiameter >= 0.5)
		return 0.1;
	else
	//return propellerPitch / propellerDiameter;
	//return 0.1; //ops
		return 0.075;
}


//bg sait
float thrustEq(float coef, float numberOfBlades, float propDiameter) 
{
	return coef * RHO * pow(numberOfBlades, 2.0) * pow(propDiameter, 4.0);
}

//best real formula
float thrust(float motorRPM, float propellerDiameter, float propellerPitch)
{
	return 4.392399 * (1.0 / pow(10.0, 8.0)) * motorRPM * pow(propellerDiameter, 3.5) / sqrt(propellerPitch)* (4.2333 * (1.0 / pow(10.0, 4.0)) * motorRPM * propellerPitch);
}


float calculateVelocity(float RPM, float propellerDiameter) 
{
	return PI * propellerDiameter * RPM / 60.0;
}

/// dont use it
float calculateVelocityFromPitch(float propellerPitch, float RPM) 
{
	return propellerPitch * RPM / 60.0;
}

float calculateIStallCurrent(float Vin, float Rm) 
{
	return Vin / Rm;
}

float calculateMotorRPM(float Kv, float Vin, float Im, float Rm) 
{
	return  Kv * (Vin - Im * Rm);
}

/// returns thrust
float formulaA1Thrust(float propellerDiameter,	float propellerPitch, float motorRPM)
{
	return  calcPowerElectricity(propellerDiameter, propellerPitch, motorRPM, 1.31);
} 


float inchToMeter(float inches) 
{
	return inches * 0.0254;
}

float inchToFoot(float inches)
{
	return inches * 0.083;
}