#pragma once

#include "Props.h"
#include <vector>
#include <cstdlib>

///Parsing sqlite db result into vector of CProps
std::vector<CProps>  parseSQLiteToVectorOfProps(char ** sqliteResult, int rows, int cols)
{
	std::vector<CProps> resultVectorProps;
	//resultVectorProps.resize(rows*cols);
	/// first line contains names of the table
	for (int rowCtr = 1; rowCtr < rows; ++rowCtr)
	{
		/// missing id and name columns from table
		int cellPositionDiam = (rowCtr * cols) + 2;  /// diameter pos
		int cellPositionPitch = (rowCtr * cols) + 3; ///pitch pos

		CProps prop = CProps(atof(sqliteResult[cellPositionDiam]), atof(sqliteResult[cellPositionPitch]), std::string("Propeller " + std::string(sqliteResult[cellPositionDiam]) + 'x' + std::string(sqliteResult[cellPositionPitch])));
		resultVectorProps.push_back(prop);
	}

	return resultVectorProps;
}

/// calculation of max RPM for a prop based on its diameter name and pitch
float getMaxRPMForPropeller(float diameter, float pitch, std::string name)
{
	/// for now we are using only diameter int he formula and it is base on APC calcs
	if (diameter > 32 || diameter < 2)
		return -1; ///error diameter is expected to be in range [2 .. 32]
	if (diameter <= 5) /// smallest props 5inch also
		return 22000;
	else if (diameter < 9 && diameter > 5) /// from 6 inch to 9
		return (105000.f / diameter);
	else if (diameter >= 9 && diameter <= 13)
		return (65000.f / diameter);
	else if (diameter > 13)
		return  (190000.f / diameter);

	return -1;
}


float thrustCalc(const float & motorRPM, const float & propellerDiameter, const float & propellerPitch)
{
	return 4.392399 * (1.0 / pow(10.0, 8.0)) * motorRPM * pow(propellerDiameter, 3.5) / sqrt(propellerPitch)* (4.2333 * (1.0 / pow(10.0, 4.0)) * motorRPM * propellerPitch);
}

float getMaxThrustForPropellerInKg(const float & RPM, const float & diameter, const float & pitch)
{
	return thrustCalc(RPM, diameter, pitch) * 0.102;
}

float reversingThrustEquasion(float thrust, float propellerDiameter, float propellerPitch)
{
	//float a = 4.392399 * pow(propellerDiameter, 3.5) * 4.2333 * propellerPitch * pow(motorRPM, 2.0); *pow(rpm,2.0) :))
	float b = pow(10.0, 8.0) * sqrt(propellerPitch) *  pow(10.0, 4.0);
	//return  a / b;
	return sqrt((thrust / 0.102 * b) / (4.392399 * pow(propellerDiameter, 3.5) * 4.2333 * propellerPitch));
}

float calcPowerForPropeller(float propellerDiameter,
	float propellerPitch,
	float motorRPM,
	float propCoefFiction = 1.31)
{
	return propCoefFiction * pow(propellerDiameter * 0.083, 4.0) * propellerPitch * 0.083 * pow(motorRPM / 1000, 3.0);
}


void calcAdditionalParamsForProps(CProps & prop, float wantedThrust) 
{
	prop.mf_maxRPM = getMaxRPMForPropeller(prop.mf_diameter, prop.mf_pitch, prop.ms_name);
	prop.mf_maxThrust = getMaxThrustForPropellerInKg(prop.mf_maxRPM, prop.mf_diameter, prop.mf_pitch);
	prop.mf_wantedThrustRPM = reversingThrustEquasion(wantedThrust, prop.mf_diameter, prop.mf_pitch);///
	prop.mf_powerNeededInWatts = calcPowerForPropeller(prop.mf_diameter, prop.mf_pitch, prop.mf_wantedThrustRPM);///
}


void setAdditionalParamsToVectorProps(vector<CProps>& vec, float wantedThrust)
{
	for (CProps & prop : vec)
	{
		calcAdditionalParamsForProps(prop, wantedThrust);
	}
}