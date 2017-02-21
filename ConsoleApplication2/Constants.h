#pragma once
/// SQLite exec constants
#include <string>
#include <vector>
#include "Props.h"
#include "Motor.h"
#include "PropellersSQLiteToMapParsing.h"

using namespace std;
const std::string PROPELLERSTABLENAME = "PROPELLERS";
const std::string MOTORSTABLENAME = "USEDMOTORS12";
const std::string ENDSEMICOLLUMN = ";";

/// sql exec statements
const std::string SQLSELECTSTAR = "Select * from ";


std::vector<CMotorHK>  parseSQLiteToVectorOfMotors(char ** sqliteResult, int rows, int cols);
std::vector<CMotorHK>  correctingMotorData(std::vector<CMotorHK> & motors);

std::vector<CProps>  parseSQLiteToVectorOfProps(char ** sqliteResult, int rows, int cols);
float                getMaxThrustForPropellerInKg(const float & RPM, const float & diameter, const float & pitch);
void                 setAdditionalParamsToVectorProps(vector<CProps>& vec, float wantedThrust);
float                thrustCalc(const float & motorRPM, const float & propellerDiameter, const float & propellerPitch);
float                reversingThrustEquasion(float thrust, float propellerDiameter, float propellerPitch);


///// garbage code


/////// testing funcs 1
//float a[] = { 0, 0, 0, 0, 0, 52.5927, 75.7336, 103.082, 134.637, 170.4, 210.371, 254.549 };
//for (int p = 5000; p < 20000; p += 1000)
//	cout << p << "   " << reversingThrustEquasion(a[p / 1000], 20, 10, p) << "    " << thrustCalc(p, 20, 10) << endl;