#pragma once

#include <vector>

namespace DC
{

	class Part;

	enum dataType
	{
		ALL = -1,
		NONE = 0,
		MOTORS = 1,
		PROPELLERS = 2,
		BATTERIES = 4,
		ESC = 8,
		BODY = 16,
	};
	
	class IBasicDetailsReader
	{
	public:
		virtual void clearData() = 0;
		virtual void renewData() = 0;
		virtual std::vector<Part* > getVectorWithData(dataType & a) = 0;

	};
}