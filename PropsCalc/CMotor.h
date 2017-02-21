/////////////////////////////////////
///// Includes
//////////////////////
#include <string>

////////////////////////////
//// Constants
///////////////////////////

const float CONST_TORQUE_PARAM = 1355;


////////////////////////////////////////////
////////// CMotor - represents electric motor with all his real parts and characteristics
////////////////////
class CMotor 
{
public:
	CMotor( float diam, float resist, float kv,	float mpower, float weight, float mcurrent, float nlcurrent, float volts, std::string name)
	:ms_motorName(name),
	mf_diameter(diam),
	mf_resistance(resist),
	mf_Kv(kv),
	mf_maxPower(mpower),
	mf_weight(weight),
	mf_maxCurrent(mcurrent),
	mf_noLoadCurrent(nlcurrent),
	mf_maxVoltage(volts)
	{}
	
	float getMotorRPM(float volts) 
	{
		return volts * mf_Kv;
	}

	float getMotorRPMInSeconds(float volts)
	{
		return getMotorRPM(volts) /60.0f;
	}

	float getDiameter() 
	{
		return mf_diameter;
	}

	float getMotorDiameter()
	{
		return mf_diameter;
	}

	float getMotorResistance()
	{
		return mf_resistance;
	}

	float getMotorKv()
	{
		return mf_Kv;
	}

	float getMotorMaxPower()
	{
		return mf_maxPower;
	}

	float getMotorWeight()
	{
		return mf_weight;
	}

	float getMotorMaxCurrent()
	{
		return mf_maxCurrent;
	}
	float getMotorNoLoadCurrent()
	{
		return mf_noLoadCurrent;
	}
	float getMotorMaxVoltage()
	{
		return mf_maxVoltage;
	}
	//// Retursn Motor name from the 
	std::string getMotorName() 
	{
		return ms_motorName;
	}
	

private:
	
	//float mf_RPM;
	float mf_diameter;
	float mf_resistance;
	float mf_Kv;
	float mf_maxPower;
	float mf_weight;
	float mf_maxCurrent;
	float mf_noLoadCurrent; //Io
	float mf_maxVoltage; // optional
	std::string ms_motorName;

};