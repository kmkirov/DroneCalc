#pragma once

#include <vector>

struct CProps;
///Parsing sqlite db result into vector of CProps
std::vector<CProps>  parseSQLiteToVectorOfProps(char ** sqliteResult, int rows, int cols);

/// calculation of max RPM for a prop based on its diameter name and pitch
float getMaxRPMForPropeller(float diameter, float pitch, std::string name);



float thrustCalc(const float & motorRPM, const float & propellerDiameter, const float & propellerPitch);


float getMaxThrustForPropellerInKg(const float & RPM, const float & diameter, const float & pitch);


float reversingThrustEquasion(float thrust, float propellerDiameter, float propellerPitch);


float calcPowerForPropeller(float propellerDiameter,
							float propellerPitch,
							float motorRPM,
							float propCoefFiction = 1.31);



void calcAdditionalParamsForProps(CProps & prop, float wantedThrust);



void setAdditionalParamsToVectorProps(std::vector<CProps>& vec, float wantedThrust);
