#include "Motor.h"
#include <vector>
#include <cstdlib>

CMotorHK::CMotorHK(std::string URL, float resist, float kv, float mpower, float weight, float mcurrent, float nlcurrent, float volts,  float noLoadVolts, std::string name)
	:ms_motorName(name),
	ms_URL(URL),
	mf_resistance(resist),
	mf_Kv(kv),
	mf_maxPower(mpower),
	mf_weight(weight),
	mf_maxCurrent(mcurrent),
	mf_noLoadCurrent(nlcurrent),
	mf_maxVoltage(volts),
	mf_noLoadVolts(noLoadVolts)
{}



ostream& operator<<(ostream& os, const CMotorHK& motor)
{
	os << " RES " << motor.mf_resistance
		<< " KV " << motor.mf_Kv
		<< " POWER " << motor.mf_maxPower
		<< " WEIGHT " << motor.mf_weight
		<< " MAXCUR " << motor.mf_maxCurrent
		<< " NOLOADCUR " << motor.mf_noLoadCurrent //Io
		<< " MAXVOLT " << motor.mf_maxVoltage
		<< " NAME " << motor.ms_motorName
		<< " URL " << motor.ms_URL
		<< " NOVOLTAGE" << motor.mf_noLoadVolts
		<< std::endl;
	return os;
}