#pragma once
namespace DC 
{

	class CSQLiteBasicDetailsReader 
	{
	public:
		virtual void clearData() = 0;
		virtual void renewData() = 0;
		virtual std::vector<Part* > getVectorWithData(dataType & a) = 0;
	};
}