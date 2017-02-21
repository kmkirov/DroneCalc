
#include "Props.h"
#include <vector>
#include <cstdlib>
//////////////////////////////////////////
//////////////// Implementation
//////////////////////////

/////////////////
///// Constructors
////////////////

CProps::CProps(float diam, float pitch, std::string name)
	:mf_diameter(diam),
	mf_pitch(pitch),
	ms_name(name)
{
}
///////////////////////////////
///////////// functions
//////////////////////////////
ostream& operator<<(ostream& os, const CProps& prop)
{
	os << prop.ms_name << " diam " << prop.mf_diameter 
		<< " pitch " << prop.mf_pitch 
		<< " maxRPM " << prop.mf_maxRPM 
		<< " maxThrust " << prop.mf_maxThrust
		<< " wantedRPMThrujs " << prop.mf_wantedThrustRPM 
		<< " powerNeedWats "<< prop.mf_powerNeededInWatts 
		<< std::endl;
	return os;
}
