#pragma once
/// SQLite exec constants
#include <string>


static bool hasSolution = false;
static float expectedThrustFromOneMotorInKg = 0.51f;//5.9;


													/// propellers coef for filtering power
													///void filterPropellersAccordingToThrustNeeded(float thrust, vector<CProps> & vec)
const float WEIGHTCONSTANTMIN = 3.f; //3.0; // 3.0
const float WEIGHTCONSTANTMAX = 10.f; //4;//2.2;

									  /// motor coef for filtering power
									  ///vector<CMotorHK> filterMotorsByCapabilities(vector<CMotorHK> & vectorMotors, CProps & prop1, float  expectedThrustFromOneMotorInKg)
const float MINMOTORPOWERCOEF = 0.8f;
const float MOTORPOWERCOEF = 2.0f;

/// weight * 2 * 0.7 coeficient for measuring effective thrust
/// void calculateMotorEffectiveness(vector<CMotorHK> & vectorMotors, CProps & prop1, float effectiveCoef, float expectedThrustFromOneMotorInKg)
const float EFFECTIVETHRUST = 0.7f;


///const float RPMCOEF = 1.2;
///const float MOTORPOWERVALUE = 1.3;
///const float wantedThrust = 0;
/// wantedThrust = 4 * expectedThrustFromOneMotorInKg
///const float droneWeight = 1;
///const  float wantedDroneWeihgtThrust = droneWeight * WEIGHTCONSTANTMIN;




/// SQL Query Table Nnames
const std::string PROPELLERSTABLENAME = "PROPELLERS";
const std::string MOTORSTABLENAME = "USEDMOTORS12";
const std::string DBNAME = "test.db";


/// sql exec statements
const std::string ENDSEMICOLLUMN = ";";
const std::string SQLSELECTSTAR = "Select * from ";

