#pragma once

#include <string>
#include "IBasicDetailsReader.h"

namespace DC 
{
	class CPart 
	{
	public:
		virtual DC::dataType   getType() = 0;
		virtual std::string    getURL() = 0;
		virtual void		   getAllDetails(std::string & details) = 0;
	};
}