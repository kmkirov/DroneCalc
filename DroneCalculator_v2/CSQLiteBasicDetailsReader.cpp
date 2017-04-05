#include "CSQLiteBasicDetailsReader.h"
#include "Const.h"
#include "CMotorDetails.h"
#include <iostream>

namespace DC {
	readerType DC::CSQLiteBasicDetailsReader::getReaderType() 
	{
		return readerType::DB;
	}
	
	DC::CSQLiteBasicDetailsReader::CSQLiteBasicDetailsReader()
	{

	}

	DC::CSQLiteBasicDetailsReader::CSQLiteBasicDetailsReader(const std::string& databeseName)
		:ms_databaseName(databeseName),
		 msl_database(nullptr)
	{
		
	}

	DC::CSQLiteBasicDetailsReader::~CSQLiteBasicDetailsReader()
	{
		closeDatabase();
	}
	



	void  DC::CSQLiteBasicDetailsReader::openDatabase()
	{
		int rc;
		char * error;

		// Open Database
		std::cout << "Opening " << ms_databaseName << std::endl;


		rc = sqlite3_open(ms_databaseName.c_str(), &msl_database);
		if (rc)
		{
			std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(msl_database) << std::endl << std::endl;
			sqlite3_close(msl_database);
			return;// exit
		}
		else
		{
			std::cout << "Openning " << ms_databaseName << std::endl << std::endl;
		}
	}

	/// Closing sqlite3database by given pointer to it.
	/// params - pointer to database
	////////
	void DC::CSQLiteBasicDetailsReader::closeDatabase() 
	{
		// Close Database
		std::cout << "Closing MyDb.db ..." << std::endl;
		sqlite3_close(msl_database);
		std::cout << "Closed MyDb.db" << std::endl << std::endl;

		// Wait For User To Close Program
		std::cout << "Please press any key to exit the program ..." << std::endl;
		
	}
	/// abstract
	//void DC::CSQLiteBasicDetailsReader::clearData() {}
	//void DC::CSQLiteBasicDetailsReader::renewData() {}


	std::vector<Part* > DC::CSQLiteBasicDetailsReader::parseSQLiteToVectorOfMotors(char ** sqliteResult, int rows, int cols)
	{
		std::vector<Part*> resultVectorMotors;
		//resultVectorMotors.resize(rows*cols);
		//first line contains names of the table
		for (int rowCtr = 1; rowCtr < rows; ++rowCtr)
		{
			///missing id and name columns from table
			int cellPositionName = (rowCtr * cols) + 1;
			int cellPositionUnitWeight = (rowCtr * cols) + 2;
			int cellPositionKv = (rowCtr * cols) + 3;
			int cellPositionPower = (rowCtr * cols) + 4;
			int cellPositionResist = (rowCtr * cols) + 5;
			int cellPositionNoLoadCurr = (rowCtr * cols) + 6;
			int cellPositionNoLoadVolt = (rowCtr * cols) + 7;
			int cellPositionMaxCurr = (rowCtr * cols) + 8;
			int cellPositionMaxVolt = (rowCtr * cols) + 9;
			int cellPositionURL = (rowCtr * cols) + 10;
			//CMotor(std::string URL, float resist, float kv, float mpower, float weight, float mcurrent, float nlcurrent, float volts, std::string name)

			CMotorDetails * motor = new CMotorDetails(std::string(sqliteResult[cellPositionURL]),
				atof(sqliteResult[cellPositionResist]),
				atof(sqliteResult[cellPositionKv]),
				atof(sqliteResult[cellPositionPower]),
				atof(sqliteResult[cellPositionUnitWeight]),
				atof(sqliteResult[cellPositionMaxCurr]),
				atof(sqliteResult[cellPositionNoLoadCurr]),
				atof(sqliteResult[cellPositionMaxVolt]),
				atof(sqliteResult[cellPositionNoLoadVolt]),
				std::string(sqliteResult[cellPositionName]));

			resultVectorMotors.push_back((Part*)motor);
		}

		return resultVectorMotors;
	}

	std::vector<Part* >  DC::CSQLiteBasicDetailsReader::getVectorWithData(dataType a)
	{
		if (!msl_database) 
		{
			openDatabase();
		}

		int rows = 0, cols = 0;
		char ** results = nullptr;

		switch (a) 
		{
		case dataType::MOTORS:
			readSQLiteDBAndReturnResults((SQLSELECTSTAR + MOTORSTABLENAME + ENDSEMICOLLUMN), rows, cols, &results);
			break;

		case dataType::PROPELLERS:
			readSQLiteDBAndReturnResults((SQLSELECTSTAR + PROPELLERSTABLENAME + ENDSEMICOLLUMN), rows, cols, &results);
			break;
		default:
			std::cout << "Default datatype given.";
		}
		std::vector<Part*> res = parseSQLiteToVectorOfMotors(results, rows, cols);
		return res;
	}

	///////////
	/// Execute querery to  sqlite3 database 
	/// params  db- pointer to sqlite 3 database
	/// exec - query which will be executed
	/// rows - variable for storin rows of the result
	/// cols - variable for storin columns of the result
	/// result - array of characters for storing the result
	////////
	void DC::CSQLiteBasicDetailsReader::readSQLiteDBAndReturnResults(std::string& exec, int& rows, int& cols, char*** results)
	{
		char *error;
		int rc = sqlite3_get_table(msl_database, exec.c_str(), results, &rows, &cols, &error);
		if (rc)
		{
			std::cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(msl_database) << std::endl << std::endl;
			sqlite3_free(error);
			///exit ?
		}
	}
}