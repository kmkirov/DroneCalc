#pragma once
/// SQLite exec constants
#include <string>


static bool hasSolution = false;

static float expectedThrustFromOneMotorInKg = 0.51;//5.9;


/// propellers coef for filtering power
///void filterPropellersAccordingToThrustNeeded(float thrust, vector<CProps> & vec)
const float WEIGHTCONSTANTMIN = 3; //3.0; // 3.0
const float WEIGHTCONSTANTMAX = 10; //4;//2.2;

/// motor coef for filtering power
///vector<CMotorHK> filterMotorsByCapabilities(vector<CMotorHK> & vectorMotors, CProps & prop1, float  expectedThrustFromOneMotorInKg)
const float MINMOTORPOWERCOEF = 0.8;
const float MOTORPOWERCOEF = 2.0;

/// weight * 2 * 0.7 coeficient for measuring effective thrust
/// void calculateMotorEffectiveness(vector<CMotorHK> & vectorMotors, CProps & prop1, float effectiveCoef, float expectedThrustFromOneMotorInKg)
const float EFFECTIVETHRUST = 0.7;


///const float RPMCOEF = 1.2;
///const float MOTORPOWERVALUE = 1.3;
///const float wantedThrust = 0;
/// wantedThrust = 4 * expectedThrustFromOneMotorInKg
///const float droneWeight = 1;
///const  float wantedDroneWeihgtThrust = droneWeight * WEIGHTCONSTANTMIN;




/// SQL Query Table Nnames
const std::string PROPELLERSTABLENAME = "PROPELLERS";
const std::string MOTORSTABLENAME = "USEDMOTORS12";


/// sql exec statements
const std::string ENDSEMICOLLUMN = ";";
const std::string SQLSELECTSTAR = "Select * from ";

