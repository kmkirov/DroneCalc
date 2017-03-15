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
///////////// Functions
//////////////////////////////
ostream& operator<<(ostream& os, const CProps& prop)
{
	os  << prop.ms_name 
		<< " Diameter: "			<< prop.mf_diameter 
		<< " Pitch: "				<< prop.mf_pitch 
		<< " MaxRPM: "				<< prop.mf_maxRPM 
		<< " MaxThrust: "			<< prop.mf_maxThrust
		<< " WantedRPMThrujs: "		<< prop.mf_wantedThrustRPM 
		<< " PowerNeedInWats: "		<< prop.mf_powerNeededInWatts 
		<< std::endl;
	return os;
}
