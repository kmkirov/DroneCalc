#include "Motor.h"

#include <vector>
#include <cstdlib>



///Parsing sqlite db result into vector of CProps
std::vector<CMotorHK>  parseSQLiteToVectorOfMotors(char ** sqliteResult, int rows, int cols)
{
	std::vector<CMotorHK> resultVectorMotors;
	//resultVectorMotors.resize(rows*cols);
	//first line contains names of the table
	for (int rowCtr = 1; rowCtr < rows; ++rowCtr)
	{
		///missing id and name columns from table
		int cellPositionName = (rowCtr * cols) + 1;
		int cellPositionUnitWeight = (rowCtr * cols) + 2;
		int cellPositionKv = (rowCtr * cols) + 3;
		int cellPositionPower = (rowCtr * cols) + 4;
		int cellPositionResist = (rowCtr * cols) + 5;
		int cellPositionNoLoadCurr = (rowCtr * cols) + 6;
		int cellPositionNoLoadVolt = (rowCtr * cols) + 7;
		int cellPositionMaxCurr = (rowCtr * cols) + 8;
		int cellPositionMaxVolt = (rowCtr * cols) + 9;
		int cellPositionURL = (rowCtr * cols) + 10;
		//CMotor(std::string URL, float resist, float kv, float mpower, float weight, float mcurrent, float nlcurrent, float volts, std::string name)

		CMotorHK motor = CMotorHK(std::string(sqliteResult[cellPositionURL]),
			atof(sqliteResult[cellPositionResist]),
			atof(sqliteResult[cellPositionKv]),
			atof(sqliteResult[cellPositionPower]),
			atof(sqliteResult[cellPositionUnitWeight]),
			atof(sqliteResult[cellPositionMaxCurr]),
			atof(sqliteResult[cellPositionNoLoadCurr]),
			atof(sqliteResult[cellPositionMaxVolt]),
			atof(sqliteResult[cellPositionNoLoadVolt]),
			std::string(sqliteResult[cellPositionName]));

		resultVectorMotors.push_back(motor);
	}

	return resultVectorMotors;

}


std::vector<CMotorHK> correctingMotorData(std::vector<CMotorHK> & motors)
{
	std::vector<CMotorHK> newVector;///++optimization resize
	for(auto& elem : motors)
	{
		if (0 == elem.mf_maxCurrent && 0 == elem.mf_maxPower ||
			0 == elem.mf_maxCurrent && 0 == elem.mf_maxVoltage ||
			0 == elem.mf_maxVoltage && 0 == elem.mf_maxPower
			|| 50 > elem.mf_Kv || 1 > elem.mf_weight)
		{
			continue; /// check if not possible to handle data from db
		}
		//// setting possible data
		if (0 == elem.mf_maxCurrent)
		{
			elem.mf_maxCurrent = elem.mf_maxPower / elem.mf_maxVoltage;
		}

		if (1 > elem.mf_maxPower)
		{
			elem.mf_maxPower = elem.mf_maxCurrent * elem.mf_maxVoltage;
		}

		if (0 == elem.mf_maxVoltage)
		{
			elem.mf_maxVoltage = elem.mf_maxPower / elem.mf_maxCurrent;
		}

		/// Setting fiction noload -- needed from db
		if (elem.mf_noLoadCurrent < 0.0001)
		{
			elem.mf_noLoadCurrent = elem.mf_maxCurrent / (20 * elem.mf_Kv / 1000);
			if ( elem.mf_noLoadCurrent < 0.0001 )
			{
				elem.mf_noLoadCurrent = 0.3; /// :)
			}
			else if (elem.mf_noLoadCurrent > 4) 
			{
				elem.mf_noLoadCurrent = 4;
			}
		}
		/// partial correction of the values
		/// correcting corf
		float powerCoefForChange = elem.mf_maxPower / (elem.mf_maxCurrent * elem.mf_maxVoltage);
		/// correcting too small vbltage
		if (elem.mf_maxCurrent > 13.9 && powerCoefForChange > 1.25)
		{
			elem.mf_maxVoltage = elem.mf_maxPower / elem.mf_maxCurrent;
		}

		/// correcting too small current
		else if (powerCoefForChange > 1.25 && elem.mf_maxVoltage > 20.0)
		{
			elem.mf_maxCurrent = elem.mf_maxPower / elem.mf_maxVoltage;
		}


		if (elem.mf_resistance > 0.9)
		{
			elem.mf_resistance = elem.mf_resistance / 999.0;
		}
		else if (elem.mf_resistance < 0.0001)
		{
			elem.mf_resistance = 0.2;
		}

		if (elem.mf_noLoadVolts < 0.001) 
		{
			if (elem.mf_maxVoltage > 11)
			{
				elem.mf_noLoadVolts = 10;
			}
			else
			{
				elem.mf_noLoadVolts = elem.mf_maxVoltage*0.1;
			}

		}
		/// correction of weight
		elem.mf_weight = elem.mf_weight / 1000.0;
		/// adding to the new vector
		newVector.push_back(elem);
		///else if( powerCoefForChange > 1.25 || powerCoefForChange < 0.7)
	}
	return newVector;
}