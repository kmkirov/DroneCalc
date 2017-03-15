#include "AlgorithmDC.h"




bool propComparator(CProps a, CProps b)
{
	return a.mf_diameter < b.mf_diameter;
	//return a.mf_maxThrust < b.mf_maxThrust;
}

bool motorComparator(CMotorHK a, CMotorHK b)
{
	return a.mf_maxEffPersentage70 > b.mf_maxEffPersentage70;
}


void sortMotors(vector<CMotorHK> & vec)
{
	std::sort(vec.begin(), vec.end(), motorComparator);
}

///selects top 5 propellers
void sortAndResizeVectorProps(vector<CProps> & vec)
{
	std::sort(vec.begin(), vec.end(), propComparator);
	if (vec.size() > 5)
	{
		vec.resize(5);
	}
}

void filterPropellersAccordingToThrustNeeded(float thrust, vector<CProps> & vec)
{
	vector<CProps> newVect;
	///std::cout << thrust / 0.102 << std::endl;
	for (auto & elem : vec)
	{
		if (elem.mf_maxRPM < elem.mf_wantedThrustRPM)
		{
			continue;
		}
		if (!(elem.mf_maxThrust > WEIGHTCONSTANTMIN * thrust && elem.mf_maxThrust < WEIGHTCONSTANTMAX * thrust))
		{
			continue;
		}
		newVect.push_back(elem);
	}

	vec = newVect;
}

vector<CMotorHK> getFastCalculatedMotorsCapabilities(vector<CMotorHK> & vectorMotors, CProps & prop1, float  expectedThrustFromOneMotorInKg)
{
	std::vector<CMotorHK> vectorPossibleMotors;
	for (auto & elem : vectorMotors)
	{
		calcAdditionalParamsForProps(prop1, expectedThrustFromOneMotorInKg + elem.mf_weight);

		float voltageNeeded = prop1.mf_wantedThrustRPM / elem.mf_Kv; /// const needed ?!
		float neededCurrent = prop1.mf_powerNeededInWatts / voltageNeeded;

		elem.mf_neededCurrent = neededCurrent;
		elem.mf_neededPower = neededCurrent * voltageNeeded;
		elem.mf_neededVoltage = voltageNeeded;
		vectorPossibleMotors.push_back(elem);
	}
	return vectorPossibleMotors;
}

void fast(vector<CMotorHK> & vectorMotors, CProps & prop1, float p, float expectedThrustFromOneMotorInKg)
{
	for (auto & elem : vectorMotors)
	{
		calcAdditionalParamsForProps(prop1, expectedThrustFromOneMotorInKg * p + elem.mf_weight);
		float voltageNeeded = prop1.mf_wantedThrustRPM / elem.mf_Kv;
		float neededCurrent = prop1.mf_powerNeededInWatts / voltageNeeded;


		float powerIn = elem.mf_neededVoltage * elem.mf_neededCurrent;
		float powerOut = (neededCurrent - elem.mf_noLoadCurrent) * (voltageNeeded - neededCurrent * elem.mf_resistance);

		elem.mf_maxEffPersentage70 = powerOut / powerIn;
		elem.mf_effectiveCurrent70 = neededCurrent;
	}

}

vector<CMotorHK> filterMotorsByCapabilities(vector<CMotorHK> & vectorMotors, CProps & prop1, float  expectedThrustFromOneMotorInKg)
{
	std::vector<CMotorHK> vectorPossibleMotors;
	for (auto elem : vectorMotors)
	{
		/// adding weight to expecetr trhust with mass of the motor
		calcAdditionalParamsForProps(prop1, expectedThrustFromOneMotorInKg + elem.mf_weight);/// rmp for motor weight and payload
																							 /// check the prop again
		if (prop1.mf_maxRPM < prop1.mf_wantedThrustRPM)
		{
			continue;
		}

		/// check if potor haz the power to lift the thing
		if (!(elem.mf_maxPower > prop1.mf_powerNeededInWatts* MINMOTORPOWERCOEF &&  elem.mf_maxPower < prop1.mf_powerNeededInWatts * MOTORPOWERCOEF))
		{
			continue;
		}
		/// check voltage for the rpm needed
		//1. calculating how much voltage we need for rpm
		float voltageNeeded = prop1.mf_wantedThrustRPM / elem.mf_Kv; /// const needed ?!
		if (elem.mf_maxVoltage < voltageNeeded)
		{
			continue;
		}
		/// remove if max current is less than needed current
		float neededCurrent = prop1.mf_powerNeededInWatts / voltageNeeded;
		if (elem.mf_maxCurrent < neededCurrent)
		{
			continue;
		}
		elem.mf_maxRPM = elem.mf_Kv * elem.mf_maxVoltage;
		elem.mf_neededCurrent = neededCurrent;
		elem.mf_neededPower = neededCurrent * voltageNeeded;
		elem.mf_neededVoltage = voltageNeeded;
		vectorPossibleMotors.push_back(elem);
	}
	return vectorPossibleMotors;
}

float returnEffectivenessOfMotor(CMotorHK & motor)
{

	float powerIn = motor.mf_neededVoltage * motor.mf_neededCurrent;
	float powerOut = (motor.mf_neededCurrent - motor.mf_noLoadCurrent) * (motor.mf_neededVoltage - motor.mf_neededCurrent * motor.mf_resistance);

	return powerOut / powerIn;
}

void calcEffectivePowerForMotors(vector<CMotorHK> & motors)
{
	for (auto& elem : motors)
	{
		elem.mf_bestCurrentEffectiveness = sqrt(elem.mf_maxCurrent*elem.mf_noLoadCurrent);
		elem.mf_bestMotorEffectiveness = pow(((elem.mf_bestCurrentEffectiveness - elem.mf_noLoadCurrent) / elem.mf_bestCurrentEffectiveness), 2.0);

		elem.mf_maxEffPersentage100 = returnEffectivenessOfMotor(elem);


		cout << " eff current " << elem.mf_bestCurrentEffectiveness << "maxEffectivePersentage " << elem.mf_bestMotorEffectiveness << " effPower " << elem.mf_maxEffPersentage100;
	}

}

void getPropsAppropriateforThrustSorted(vector<CProps>& vectorProps, float expectedThrustFromOneMotorInKg)
{
	/// working with vector and adding additional info
	setAdditionalParamsToVectorProps(vectorProps, expectedThrustFromOneMotorInKg);/// need changes here ! ++optimization
																				  /// remove all unused propellers ima oshte rabota tuk !
	filterPropellersAccordingToThrustNeeded(expectedThrustFromOneMotorInKg, vectorProps);
	/// sort according to maxt thrust and select top 5 propellers
	sortAndResizeVectorProps(vectorProps);

	for (auto& elem : vectorProps)
	{
		std::cout << elem;
	}

}

vector<CProps> getPropsVectorFromSQLiteParsingDB(sqlite3 * db)
{
	std::string sqlExPropellers = SQLSELECTSTAR + PROPELLERSTABLENAME + ENDSEMICOLLUMN;
	/// results from db
	char **results = NULL;
	int rows, columns;
	readSQLiteDBAndReturnResults(db, sqlExPropellers, rows, columns, &results);
	auto vectorProps = parseSQLiteToVectorOfProps(results, rows, columns);
	sqlite3_free_table(results);
	results = NULL;
	return vectorProps;
}


vector<CMotorHK> getMotorVectorFromSQLiteParsingDB(sqlite3 * db)
{
	std::string sqlExMotor = SQLSELECTSTAR + MOTORSTABLENAME + ENDSEMICOLLUMN;
	/// results from db
	char **results = NULL;
	int rows, columns;
	readSQLiteDBAndReturnResults(db, sqlExMotor, rows, columns, &results);
	std::vector<CMotorHK> vectorMotors = parseSQLiteToVectorOfMotors(results, rows, columns);
	sqlite3_free_table(results);
	results = NULL;
	return vectorMotors;
}


//static void error_callback(int error, const char* description)
//{
//	fprintf(stderr, "Error %d: %s\n", error, description);
//}


void goToPageWithDefaultBrowser(std::string url)
{
	HWND hwnd = GetDesktopWindow();
	ShellExecute(hwnd, L"open", std::wstring(url.begin(), url.end()).c_str(), NULL, NULL, NULL);
}

float calculateSpeedOfMotorInMetersPerSecond(const CMotorHK & motor, const CProps & prop)
{/// http://www.mh-aerotools.de/airfoils/pylonprops_1.htm
	return 3.14159265359 * (motor.mf_Kv * motor.mf_neededVoltage / 60.0) * prop.mf_diameter * 0.0254;
}