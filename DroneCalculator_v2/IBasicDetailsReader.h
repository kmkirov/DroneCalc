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

	enum readerType
	{
		DB = 1
	};

	class IBasicDetailsReader
	{
	public:
	
		virtual readerType getReaderType() = 0; 
		virtual ~IBasicDetailsReader() {}
	};
}