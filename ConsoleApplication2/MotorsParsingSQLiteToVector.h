#pragma once

#include <vector>

struct CMotorHK;


	///Parsing sqlite db result into vector of CProps
	std::vector<CMotorHK>  parseSQLiteToVectorOfMotors(char ** sqliteResult, int rows, int cols);

	std::vector<CMotorHK>  correctingMotorData(std::vector<CMotorHK> & motors);
