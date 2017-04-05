#include "Motor.h"
#include <vector>
#include <cstdlib>

CMotorHK::CMotorHK(std::string URL, float resist, float kv, float mpower, float weight, float mcurrent, float nlcurrent, float volts,  float noLoadVolts, std::string name)
	:ms_motorName	(name),
	 ms_URL			(URL),
	 mf_resistance	(resist),
	 mf_Kv			(kv),
	 mf_maxPower	(mpower),
	 mf_weight		(weight),
	 mf_maxCurrent	(mcurrent),
	 mf_noLoadCurrent(nlcurrent),
	 mf_maxVoltage	(volts),
	 mf_noLoadVolts(noLoadVolts)
{}

CMotorHK::CMotorHK() {}

std::ostream& operator<<(std::ostream& os, const CMotorHK& motor)
{
	os  << " Resistance: "			<< motor.mf_resistance
		<< " KV coef: "				<< motor.mf_Kv
		<< " Max Power: "			<< motor.mf_maxPower
		<< " Motor Weight: "		<< motor.mf_weight
		<< " Max Current: "			<< motor.mf_maxCurrent
		<< " No Load Current: "		<< motor.mf_noLoadCurrent //Io
		<< " Max Voltage: "			<< motor.mf_maxVoltage
		<< " NAME: "				<< motor.ms_motorName
		<< " URL: "					<< motor.ms_URL
		<< " No Load Voltage:"		<< motor.mf_noLoadVolts
		
		<< " Max RPM possible:"		<< motor.mf_maxRPM
		<< " Needed Power for 100% of constants multiplied by load: "	<< motor.mf_neededPower
		<< " Needed Voltage for 100% of constants multiplied by load: " << motor.mf_neededVoltage
		<< " Needed Current for 100% of constants multiplied by load: " << motor.mf_neededCurrent
		
		<< " Needed Current for 100% of constants multiplied by load: " << motor.mf_neededCurrent
		<< " Efficiency at 100% of constants multiplied by load: "		<< motor.mf_maxEffPersentage100
		<< " Best Possible Efficiency of Motor: "						<< motor.mf_bestMotorEffectiveness
		<< " Best Currnet Efficiency of Motor: "						<< motor.mf_bestCurrentEffectiveness

		<< " Efficiency at 70% of constants multiplied by load: "		<< motor.mf_maxEffPersentage70
		<< " Most efficient current at 70% of constants multiplied by load: " << motor.mf_effectiveCurrent70

		<< std::endl;

	os << std::endl;

	 
	return os;
}