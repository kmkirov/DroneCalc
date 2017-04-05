#pragma once

#include <string>

namespace DC 
{
	class CPart 
	{
	public:
		virtual DC::dataType   getType() = 0;
		virtual std::string    getURL() = 0;
		virtual void           getAllDetails() = 0;
	};
}