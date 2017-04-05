#pragma once
/////////////////////////////////////
///// Includes
//////////////////////
#include <string>
#include <iostream>

///////////////////////////////////////////////////////////////

////////////////////////////
//// Constants
///////////////////////////

/////////////////////////////////////////////////////////////////////
/// Class CProps represends a proppeler with his physical attributes like diameter and pitch measured in inches
/////////////////////
struct CProps 
{
public:
	/////////////////
	///// Constructors
	////////////////
	CProps() {}
	CProps(float diam, float pitch, std::string name);
	
	
	////////////////////////////
	// Member variables, please make sure that they are properly aligned by 4 bytes
	////////////////////
	float mf_powerNeededInWatts; /// watts
	float mf_diameter; /// inches
	float mf_pitch; /// inches
	float mf_maxRPM; /// max possible rpm in thousands
	float mf_maxThrust;/// max possible thrust in kg
	float mf_wantedThrustRPM; /// needed rpm in thousands for wanted kg

	std::string ms_name; /// combination of diamxpitch

	//////////////////
	//Friend functions
	///////////////
	friend std::ostream& operator<<(std::ostream& os, const CProps& prop);
};

////////////////////////////////////////////////////////////////////////
/// function operator<< prints all member variables of CProp class
/// params os - output stream by referece like cout
/// params prop - propeller by reference
/// return - output stream in order to get "bind" streams
////
////
std::ostream& operator<<(std::ostream& os, const CProps& prop);