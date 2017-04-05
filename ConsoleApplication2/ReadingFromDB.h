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
///////////
/// Open sqlite3database with name dbName to the given pointer db.
/// params  db- pointer to database
/// dbName - name of the database
////////
void openSQLiteDb(sqlite3* & db, std::string dbName);
///////////
/// Closing sqlite3database by given pointer to it.
/// params - pointer to database
////////
void closeSQLiteDb(sqlite3 * db);

