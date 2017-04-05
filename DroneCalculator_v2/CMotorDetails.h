#pragma once
/////////////////////////////////////
///// Includes
//////////////////////

#include <string>
#include <iostream>

//////////////////////////

#include "CPart.h"

////////////////////////////
//// Constants
///////////////////////////
namespace DC
{
	const float CONST_TORQUE_PARAM = 1355;
	///////////////
	/// CMotorDetails  represents electric motor with all his real parts and characteristics 
	////////////////
	class CMotorDetails : public CPart
	{
	public:
		/////////////////
		///// Constructors
		////////////////
		CMotorDetails();
		CMotorDetails(std::string URL, float resist, float kv, float mpower, float weight, float mcurrent, float nlcurrent, float volts, float noLoadVolts, std::string name);
		
		//////////////////////
		/// Parent abstract functions from CPart
		//////////////////////
		virtual DC::dataType   getType();
		virtual std::string    getURL();
		virtual void           getAllDetails(std::string & details);

	private:
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
		std::string ms_motorName;
		std::string ms_URL;
		/////////////////
		/////Friend function 
		////////////////
		friend std::ostream& operator<<(std::ostream& os, const CMotorDetails& motor);
	};
	////////////////////////////////////////////////////////////////////////
	/// function operator<< prints all member variables of CMotorHK class
	/// params os - output stream by referece like cout
	/// params motor - motor by reference
	/// return - output stream in order to get "bind" streams
	////
	std::ostream& operator<<(std::ostream& os, const CMotorDetails& motor);
}