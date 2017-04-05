#pragma once
#include <vector>
#include <string>

#include "CPart.h"

#include "sqlite3.h"
#include "IBasicDetailsReader.h"

namespace DC 
{

	class CSQLiteBasicDetailsReader : public IBasicDetailsReader
	{
		std::string    ms_databaseName;
		sqlite3 *      msl_database;

	public:
		CSQLiteBasicDetailsReader();
		CSQLiteBasicDetailsReader(const std::string & databaseName);

		~CSQLiteBasicDetailsReader();

		readerType getReaderType();

		void openDatabase();
		void closeDatabase();

		void readSQLiteDBAndReturnResults(std::string& exec, int& rows, int& cols, char*** results);

		std::vector<Part* > parseSQLiteToVectorOfMotors(char ** sqliteResult, int rows, int cols);

		///virtual void clearData();
		///virtual void renewData();
		virtual std::vector<Part* > getVectorWithData(dataType  a);


	};
}