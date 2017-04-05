#pragma once
#include "sqlite3.h"
#include <iostream>
#include <vector>

///

struct CProps;
struct CMotorHK;



bool					propComparator(CProps a, CProps b);

bool					motorComparator(CMotorHK a, CMotorHK b);

void					sortMotors(std::vector<CMotorHK> & vec);

void					sortAndResizeVectorProps(std::vector<CProps> & vec);

void					filterPropellersAccordingToThrustNeeded(float thrust,
																std::vector<CProps> & vec);

std::vector<CMotorHK>		getFastCalculatedMotorsCapabilities(std::vector<CMotorHK> & vectorMotors,
															CProps & prop1,
															float  expectedThrustFromOneMotorInKg);

void					calculateMotorEffectiveness(std::vector<CMotorHK> & vectorMotors,
													CProps & prop1,
													float p,
													float expectedThrustFromOneMotorInKg);

std::vector<CMotorHK>	filterMotorsByCapabilities(std::vector<CMotorHK> & vectorMotors,
												   CProps & prop1, 
												   float  expectedThrustFromOneMotorInKg);

float					returnEffectivenessOfMotor(CMotorHK & motor);

void					calcEffectivePowerForMotors(std::vector<CMotorHK> & motors);

void					getPropsAppropriateforThrustSorted(std::vector<CProps>& vectorProps,
															float expectedThrustFromOneMotorInKg);

std::vector<CProps>			getPropsVectorFromSQLiteParsingDB(sqlite3 * db);

std::vector<CMotorHK>       getMotorVectorFromSQLiteParsingDB(sqlite3 * db);

void					goToPageWithDefaultBrowser(std::string url);

float					calculateSpeedOfMotorInMetersPerSecond(const CMotorHK & motor,
															   const CProps & prop);


static void		error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}