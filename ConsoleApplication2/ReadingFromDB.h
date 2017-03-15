#pragma once

#include "sqlite3.h"

#include <string>

///////////
/// Execute querery to  sqlite3 database 
/// params  db- pointer to sqlite 3 database
/// exec - query which will be executed
/// rows - variable for storin rows of the result
/// cols - variable for storin columns of the result
/// result - array of characters for storing the result
////////
void readSQLiteDBAndReturnResults(sqlite3* db, std::string& exec, int& rows, int& cols, char*** results);
//{	
//	char *error;
//	int rc = sqlite3_get_table(db, exec.c_str(), results, &rows, &cols, &error);
//	if (rc)
//	{
//		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
//		sqlite3_free(error);
//		///exit ?
//	}
//}
///////////
/// Open sqlite3database with name dbName to the given pointer db.
/// params  db- pointer to database
/// dbName - name of the database
////////
void openSQLiteDb(sqlite3* & db, std::string dbName);
//{
//	int rc;
//	char *error;
//
//	// Open Database
//	cout << "Opening " << dbName << endl;
//
//	
//	rc = sqlite3_open(dbName.c_str(), &db);
//	if (rc)
//	{
//		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
//		sqlite3_close(db);
//		return;// exit
//	}
//	else
//	{
//		cout << "Openning " << dbName << endl << endl;
//	}
//}

///////////
/// Closing sqlite3database by given pointer to it.
/// params - pointer to database
////////
void closeSQLiteDb(sqlite3 * db);
//{
//	// Close Database
//	cout << "Closing MyDb.db ..." << endl;
//	sqlite3_close(db);
//	cout << "Closed MyDb.db" << endl << endl;
//
//	// Wait For User To Close Program
//	cout << "Please press any key to exit the program ..." << endl;
//	//cin.get();
//}
