#pragma once
/////////////////////////////////////
///// Includes
//////////////////////
//#ifndef MOTOR_H
//#define MOTOR_H
///
#include <string>
#include <iostream>
using namespace std;
////////////////////////////
//// Constants
///////////////////////////

const float CONST_TORQUE_PARAM = 1355;

////////////////////////////////////////////
////////// CMotor - represents electric motor with all his real parts and characteristics and some additional param for calculation his efficiency and working capabillities
////////////////////
struct CMotorHK
{
public:
	/////////////////
	///// Constructors
	////////////////
	CMotorHK();
	CMotorHK(std::string URL, float resist, float kv, float mpower, float weight, float mcurrent, float nlcurrent, float volts, float noLoadVolts, std::string name);
	
	//float mf_RPM;
	/////////////////
	///// Member variables
	////////////////
	float mf_resistance;    /// miliOmhs
	float mf_Kv;            /// measured in thousands
	float mf_maxPower;      ///measured in WATTs
	float mf_weight;        ///measured in kg
	float mf_maxCurrent;    ///measured in Amps
	float mf_noLoadCurrent; ///Io
	float mf_maxVoltage;    /// optional
	float mf_noLoadVolts;   ///measured in Volts
	float mf_maxRPM;        ///measured in Thousands
	
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

	///////
	std::string ms_motorName;
	std::string ms_URL;
	/////////////////
	/////friend function 
	////////////////
	friend std::ostream& operator<<(std::ostream& os, const CMotorHK& motor);
};
////////////////////////////////////////////////////////////////////////
/// function operator<< prints all member variables of CMotorHK class
/// params os - output stream by referece like cout
/// params motor - motor by reference
/// return - output stream in order to get "bind" streams
////
std::ostream& operator<<(std::ostream& os, const CMotorHK& motor);
//#endif 