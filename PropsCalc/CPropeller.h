/////////////////////////////////////
///// Includes
//////////////////////
#include <string>

const float NO_VALUE = -1;

class CPropeller
{
public:
	CPropeller(float diam, float pitch, float weight, float propellerConst, float propellerFactor, float maxRPM, float numBlades ,std::string name)
		:mf_diameter(diam),
		 mf_pitch(pitch),		
	     mf_weight(),
		 mf_propConstant(propellerConst), // if exists
		 mf_propFactor(propellerFactor),   // if exists
		 mf_propMaxRPM(maxRPM),   /////???
		 mf_numberOfBlades(numBlades),
		 ms_propName(name)
	{}

	CPropeller(float diam, float pitch, float weight, float numBlades, std::string name)
		:mf_diameter(diam),
		mf_pitch(pitch),
		mf_weight(weight),
		mf_propConstant(NO_VALUE), // if exists
		mf_propFactor(NO_VALUE),   // if exists
		mf_propMaxRPM(NO_VALUE),   /////???
		mf_numberOfBlades(numBlades),
		ms_propName(name)


	{}

	float getPropellerDiameter()
	{
		return mf_diameter;
	}

	float getPropellerPitch()
	{
		return mf_pitch;
	}

	float getPropellerWeight()
	{
		return mf_weight;
	}

	float getPropellerConstant() 
	{
		return mf_propConstant;
	}

	float getPropellerFactor()
	{
		return mf_propFactor;
	}

	std::string getPropellerName() 
	{
		return ms_propName;
	}

	float getPropellerRPM() 
	{
		return mf_propMaxRPM;
	}

	float getMaxThrustInKg()
	{
		return mf_maxThrustInKg;
	}

private:
	float mf_diameter;
	float mf_pitch;
	float mf_weight;
	float mf_propConstant; // if exists
	float mf_propFactor;   // if exists
	float mf_propMaxRPM;   /////???
	float mf_numberOfBlades;
	float mf_maxThrustInKg;
	std::string ms_propName; //// contains the name
	
	//// pointer to lambda for matching rmp max limit formula
};