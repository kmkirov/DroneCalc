#include "CSQLiteBasicDetailsReader.h"
#include "IBasicDetailsReader.h"
#include "Const.h"
#include "CMotorDetails.h"

#include <iostream>

int main() 
{
	DC::CSQLiteBasicDetailsReader a(DBNAME);
	
	for (auto item : a.getVectorWithData(DC::dataType::MOTORS))
		std::cout << *(DC::CMotorDetails*)item;
	///DC::CMotorDetailsDecorator a;
	return 0;
}