#include "ReadingFromDB.h"
#include <iostream>

///////////
/// Execute querery to  sqlite3 database 
/// params  db- pointer to sqlite 3 database
/// exec - query which will be executed
/// rows - variable for storin rows of the result
/// cols - variable for storin columns of the result
/// result - array of characters for storing the result
////////
void readSQLiteDBAndReturnResults(sqlite3* db, std::string& exec, int& rows, int& cols, char*** results)
{
	char *error;
	int rc = sqlite3_get_table(db, exec.c_str(), results, &rows, &cols, &error);
	if (rc)
	{
		std::cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_free(error);
		///exit ?
	}
}
///////////
/// Open sqlite3database with name dbName to the given pointer db.
/// params  db- pointer to database
/// dbName - name of the database
////////
void openSQLiteDb(sqlite3* & db, std::string dbName)
{
	int rc;
	char *error;

	// Open Database
	std::cout << "Opening " << dbName << std::endl;


	rc = sqlite3_open(dbName.c_str(), &db);
	if (rc)
	{
		std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl << std::endl;
		sqlite3_close(db);
		return;// exit
	}
	else
	{
		std::cout << "Openning " << dbName << std::endl << std::endl;
	}
}

///////////
/// Closing sqlite3database by given pointer to it.
/// params - pointer to database
////////
void closeSQLiteDb(sqlite3 * db)
{
	// Close Database
	std::cout << "Closing MyDb.db ..." << std::endl;
	sqlite3_close(db);
	std::cout << "Closed MyDb.db" << std::endl << std::endl;

	// Wait For User To Close Program
	std::cout << "Please press any key to exit the program ..." << std::endl;
	//cin.get();
}