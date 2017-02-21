//// Test environment for diplom work
//////////////////////////
///////////////////////////////////////////
//////// INCLUDES
//////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "CMotor.h"
#include "CPropeller.h"
#include "Formulas.h"
using namespace std;

#define NO_VALUE -1;

//////////////////
//////// Propellers
//////// 1. 32 inch diam / 10 inch pitch / Shaft Size: 10mm/ 200gr weight / 2 blade
//////// https://hobbyking.com/en_us/turnigy-3d-gas-propeller-32x10-1pc.html nai-golqm diametar

CPropeller prom1(32.0, 10.0, 200.0, 2.0, "turnigy-3d-gas-propeller-32x10");

/////////////////////////////////////////////////////////////////////////////////////////////////
//////// 2. 9 inch diam / 5 inch pitch / 19 grams / 2 blade
//////// https://hobbyking.com/en_us/master-airscrew-propeller-9x5-1pc-1.html
CPropeller prom2(9, 5, 19, 2, "master-airscrew-propeller-9x5");
//////////////////////////////////////////////////////////////////////////////////////////////////
//////// 3. 2.5 inch diam / 1 inch pitch / 21 gram / 2 blade
///////  https://hobbyking.com/en_us/gws-style-propeller-2-5x1-black-ccw-6pcs.html
CPropeller prom3(2.5, 1, 21, 2, "gws - style - propeller - 2 - 5x1");
//////////////////////////////////////////////////////////////////////////////////////////////////
////////// 4. 4 inch diam / 4.5 inch pitch / 19 grams /3 blades
////////// https://hobbyking.com/en_us/gemfan-4045-grp-nylon-bullnose-3-blade-propeller-cw-ccw-green.html
CPropeller prop4(4, 4.5, 19, 3, "gemfan-4045-grp-nylon-bullnose-3-blade-propeller");
///////////////////////////////////////////////////////////////////////////////////////////////////
////////  5.14 inch diam / 4.7 inch size / 76 grams / 2 blade
///////   https://hobbyking.com/en_us/gws-style-slowfly-propeller-14x4-7-grey-ccw-2pcs.html
CPropeller prop5(5.14, 4.7, 76, 2, "gws-style-slowfly-propeller-14x4-7");
//////////////////////////////////////////////////////////////////////
///////// 6. 15 inch diam / 5.5 inch pitch / 55 grams /2 blades
///////// https://hobbyking.com/en_us/15-5-5-carbon-fiber-propeller-for-multirotor-one-pair.html
CPropeller prop6(15, 5.5, 55, 2, "15-5-5-carbon-fiber-propeller-for-multirotor");
///////////////////////////////////////////////////////////////////////////////////////////////
///////// 7. 12 inch diam / 4.5 inch pitch / 67 grams / 2 blades
/////////  https://hobbyking.com/en_us/gws-style-slowfly-propeller-12x4-5-black-cw-4pcs.html
CPropeller prop7(12, 4.5, 67, 2, "gws - style - slowfly - propeller - 12x4 - 5");
////////////////////////////////////////////////////////////////////////////////////////////////
///////// 8. 24 inch diam / 15 inch pitch / 211 grams / 2 blades
////////  https://hobbyking.com/en_us/turnigy-cherry-wood-propeller-24x15-1pc.html
CPropeller prop8(24, 15, 211, 2, "/turnigy-cherry-wood-propeller-24x15");
///////////////////////////////////////////////////////////////////////////////////////////////
///// biggest multirotor is https://hobbyking.com/en_us/quanum-carbon-fiber-propeller-6x4-5-cw-ccw-2pcs.html 6 diam/ 4.5 pitch/ 2 blades/ 18 grams
///// smallest multirotor https://hobbyking.com/en_us/6-pack-of-rotorx-props.html 3 diam / 2 pitch / 2 blade / 10 grams
CPropeller prop9(6, 4.5, 18, 2, "quanum-carbon-fiber-propeller-6x4-5");
CPropeller prop10(3, 2, 10, 2, "6-pack-of-rotorx");
///// Special propellers with coef
////////////////////////////////
/////// http://www.apcprop.com/Articles.asp?ID=255 restrictions for rpm
//////
//////////////////////////////////////////////////////////
/////
/////
/////////////////////////////////////////
//http://www.apcprop.com/Articles.asp?ID=255 apc rpm limists
//https://www.aircraft-world.com/Datasheet/en/hp/emeter/hp-propconstants.htm source
//APC SLOWFLY Series
//Prop Size 	PROP CONSTANTS 	POWER FACTOR
CPropeller prop11(7, 4, -1, 0.028, 3.30, 650000.0 / 7.0, 2, "7 * 4  0.028 3.30");
//7 * 4 	             0.028       	3.30  /// 9.
CPropeller prop12(9, 6, -1, 0.119, 3.55, 65000.0 / 9.0, 2, "9 * 6  0.119  3.55 ");
//9 * 6 	             0.119 	        3.55  /// 10.
CPropeller prop13(12, 6, -1, 0.629, 3.30, 65000.0 / 12.0, 2, "12 * 6  0.629 3.30 ");
//12 * 6             	 0.629 	        3.30  /// 11.
//
//Slow Flyer(SF) Propellers
//Maximum RPM = 65, 000 / prop diameter(inches)
//
int main() 
{
	std::cout.width(10);
	cout << std::setprecision(3) <<std::fixed << "Diam" << std::setw(10) << "Pitch" << std::setw(10) <<"RPM"<< std::setw(10) << "A1" << std::setw(10) << "A2" << std::setw(10) << "A3" << std::setw(10) << "A4" << std::setw(10) << "A5" << std::setw(10) << "A6" << endl;
	float diam = 2;//prop12.getPropellerDiameter();
	float pitch = 2; // prop12.getPropellerPitch();
	///cout << diam  << std::setw(10) << pitch;
	for (int RPM = 5000; RPM < 22000; RPM += 1000)
	{ /// A1
		cout << std::setw(10) << diam <<  std::setw(10) << pitch << std::setw(10)<< RPM << std::setw(10) << kiloWattsToHorsePowerConverter( formulaA1Thrust(inchToFoot(diam), inchToFoot(pitch), RPM/1000))*0.3 * 25;
		/// A2
		float power = practivalPowerCalculation(prop12.getPropellerConstant(), RPM/1000, prop12.getPropellerFactor());
		cout << std::setw(10) << massOfThrust(prop12.getPropellerDiameter()*0.0254, power);

		///formula A3
		float power2 = kiloWattsToHorsePowerConverter(formulaA1Thrust(inchToFoot(diam), inchToFoot(pitch), RPM / 1000));
		cout <<  std::setw(10) << calculateStaticThrustEquation(inchToFoot(diam), 2, RPM, power2, inchToFoot(pitch))*0.453592;

		////formula A4 pounds * 0.45 to kg
		cout << std::setw(10) << thrustEq2(power2, 0.8, 0.8, diam)*0.453592; //?? nz

		//formula A5	
		cout << std::setw(10) << 	thrustEq(calcCoefForPropeler(inchToMeter(diam), inchToMeter(pitch)) , (RPM*1.f)/60.0, inchToMeter(diam))*0.102 ; //kg
		
		/// formula A6 nai vqrnata
		/// N*0.102 = kg /// N = 
		//cout << std::setw(10) << thrust( RPM, 9, 6)*0.102 << endl  ; //kg
		cout << std::setw(10) << thrust(RPM, diam, pitch)*0.102 << endl; //kg
 	}	
	return 0;
}

//////////////////////////////////////////////////////
///////////////////////////////////////////////////////

////////////////////////////////////
//// Motors
/////
//CMotor(-1, -1, 810, 360, 170, 35, 2.0, 18, "HobbyKing Donkey ST3511-810kv ");
///////////////////////////////
////// Definition of five motors
////////////////////////////////////////


///// 1. HobbyKing Donkey ST3511-810kv Brushless Power System Combo
/////    https://hobbyking.com/en_us/hobbyking-donkey-st3511-810kv-brushless-power-system-combo.html
/////    Specs:
//RPM / v: 810kv
//Dimensions : 42 x 29.5mm
//	Shaft : 5.0mm
//	Voltage : 6v~18v(2~4s lipo)
//	Weight : 170g
//	No - load current : 2.0A
//	Max Current : 35A
//	Max Watts : 360W
//	Mounting Holes : 52mm
//	ESC : 30A with XT60
//
//	Prop Data :
//12x6 - 11.1v - 25A - 1450g Thrust
////////////////////////////////////////////////////
//CMotor(-1, 0.028, 190, 2450, 697, 65, -1, 37.00, "Turnigy Aerodrive SK3 - 6364 - 190kv");
////// 2. Turnigy Aerodrive SK3 - 6364-190kv Brushless Outrunner Motor
////// https://hobbyking.com/en_us/turnigy-aerodrive-sk3-6364-190kv-brushless-outrunner-motor.html
//Specs.
//Turns: 18T
//	Voltage : 10S Lipoly
//	RPM / V : 190kv
//	Internal resistance : 0.028 Ohm
//	Max Loading : 65A
//	Max Power : 2450W
//	Shaft Dia : 8.0mm
//	Bolt holes : 32mm
//	Bolt thread : M4
//	Weight : 697g
//	Motor Plug : 4mm Bullet Connector
//Max Voltage(V) : 37.00
/////////////////////////////////////////////////////////////////////////////
//	CMotor(-1, 0.123, 2300, 175, 25, 14, 0.7, 18, "Scorpion M-2204-2300KV");
//// 3. Scorpion M-2204-2300KV Brushless Outrunner Motor Pair (CW & CCW) 
//https://hobbyking.com/en_us/scorpion-m-2204-2300kv-brushless-outrunner-motor-pair-cw-ccw.html
//Stator Diameter : 22 mm(0.87 in)
//Stator Thickness : 4.5mm(0.177 in)
//No.of Stator Arms : 12
//Magnet Poles : 14
//Motor Wind : 14 + 15 Turn Delta
//Motor Wire : 3 - Strand 0.21 mm
//Motor KV : 2300 RPM / Volt
//No - Load Current(Io / 10V) : 0.7 Amps
//Motor Resistance(Rm) : 0.123 Ohms
//Max Continuous Current : 14 Amps
//Max Continuous Power : 175 Watts
//Weight : 25 Grams(0.88 oz)
//	Outside Diameter : 27.9 mm(1.09 in)
//	Shaft Diameter : 2.98 mm(0.12 in)
//	Body Length : 16.5 mm(0.65 in)
//	Output Shaft Length : 12 mm(0.47 in)
//	Max LiPoly Cell : 3~4s
//	Motor Timing : 5 deg
//	Drive Frequency : 8 kHz
//
//	Included :
//1 x M - 2204 - 2300KV motor CW
//1 x M - 2204 - 2300KV motor CCW
//2 x Bullet nuts
//4 x M3 screws
//8 x M2.5 screws
//
//Thrust Data
//
//Prop Throttle  V         Amps  RPM       Thrust(G)
//6 x 4   50 % 11.1     4.3     10648    158
//6 x 4   60 % 11.1     5.7     11979    204
//6 x 4   70 % 11.1     7.9     13397    256
//6 x 4   80 % 11.1     10.7   14802    320
//6 x 4   90 % 11.1     14      16090    382
//6 x 4   100 % 11.1     14      16098    384
//
//6 x 4   50 % 14.8     5.7     12908    231
//6 x 4   60 % 14.8     7.9     14340    296
//6 x 4   70 % 14.8     11.1   15959    374
//6 x 4   80 % 14.8     14.7   17173    445
//6 x 4   90 % 14.8     18.7   18104    494
//6 x 4   100 % 14.8     18.7   18171    496

///////////////////////////////////
//	CMotor(-1, 0.125, 2300, 126.5, 24, 11.5, 0.6, -1, "Multistar Elite 2204 - 2300KV Multi");
//4.Multistar Elite 2204 - 2300KV Multi - Rotor Motor 3 - 4S(CCW Prop Adapter)
//https://hobbyking.com/en_us/multistar-elite-2204-2300kv-multi-rotor-motor-ccw-prop-adapter.html
//Specs:
//KV(RPM / V) : 2300KV
//Lipo cells : 3~4s
//Max current : 126.5w
//Max Amps : 11.5A
//No Load Current : 0.6A / 10V
//Internal Resistance : 0.125 ohm
//Number of Poles : 12 / 14
//Dimensions(Dia.xL) : 22×4 mm
//Motor Shaft : 3mm
//prop shaft : 5mm CCW prop adapter
//Weight : 24g
//	bolt hole spacing : 16 * 19 M3
//	Lamination thickness : .2mm
//	Magnets : N45SH
//	Balancing spec : .005g
//	Wire : 180deg oxygen free
//	Connector : 2mm bullet
//
//	Prop Data :
//5x3
//
//12.6V(3S) : 50 %= 224g 3.7A, 100 %= 371g 7.5A
//(Hover amps @ 125g thrust = 1.7A(x 4 = 500g = 6.8A)
//	8.4V(2S) : 50 %= 120g 2.2A, 100 %= 200g 4.3A
//	(Hover amps @ 125g thrust = 2.2A(x 4 = 500g = 8.8A)
//
//		5x3x3(3 blade)
//
//		12.6V(3S) : 50 %= 232g 4.7A, 100 %= 392g 9.9A
//		(Hover amps @ 125g thrust = 2.0A(x 4 = 500g = 8A)
//			8.4V(2S) : 50 %= 134g 2.7A         100 %= 221g 6.7A
//			(Hover amps @ 125g thrust = 2.7A(x 4 = 500g = 10.8A)
//
//				6x4
//
//				12.6V(3S) : 50 %= 385g 7.5A, 100 %= 591g 9.9A
//				(Hover amps @ 125g thrust = 1.4A(x 4 = 500g = 5.6A)
//					8.4V(2S) : 50 %= 230g 4.8A, 100 %= 367g 9.7A
//					(Hover amps @ 125g thrust = 2.1A(x 4 = 500g = 8.4A)
////////////////////////////////////////
//	CMotor(-1, -1, 105, 2600, 420, 117, -1, 6s, "Turnigy 9014 105kv ");
//5.Turnigy 9014 105kv Brushless Multi - Rotor Motor(BLDC)
//https://hobbyking.com/en_us/turnigy-9014-105kv-brushless-multi-rotor-motor-bldc.html
//Specs:
//Kv: 105rpm / v
//	Can size : 90mm
//	Motor Mount Holes : M3 x 16mm / 19mm / 25mm / 33mm
//	Rated Watts : 2600w
//	Max Current : 117A
//	Cell Count : 6S Lipoly
//	Motor Wire Length : 390mm
//	Weight : 420g
//
//	Note : Mount Screws Included
//
//////////////////////////////////////////////
//	CMotor(-1, -1, 1000, 4600, 380, 110, -1, 40, "Dr Mad Thrust 1000kv 4600watt");
//6. Dr Mad Thrust 1000kv 4600watt 90mm EDF Inrunner 8 - 10s version(40mm)
//https://hobbyking.com/en_us/dr-mad-thrust-1000kv-4600watt-90mm-edf-inrunner-8-10s-version-40mm.html
//Specs:
//RPM / V : 1000kv
//Voltage : 8 - 10s
//	Max current : 110A
//	Max Power : 4600 watts
//	Suggested Rpm Operating Range.
//	High Blade Count : 32000rpm
//	Low Blade Count : 37000rpm
//	Poles : 4
//	Diameter : 40mm
//	Front Mounting Hole Distance : 25mm
//	Shaft Diameter : 5mm
//	Shaft Length : 12mm
//	Front mount Thread Size : M3
//	Plug type : Bullet - Connector 4mm
//	Weight : 380g
////////////////////////////////////////////////////////////////////////

//float speed(float rpm, float D) 
//{
/////http://www.mh-aerotools.de/airfoils/pylonprops_1.htm
//	return  3.1416 * (rpm / 60.f) * D;
//}
////////////////////////////////////////////


//// basic-http-client.cpp
//#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>
//#include <iostream>
//#include <sstream>
//
//using namespace web::http;
//using namespace web::http::client;
//
//// Creates an HTTP request and prints the length of the response stream.
//pplx::task<void> HTTPStreamingAsync()
//{
//	http_client client(L"http://www.fourthcoffee.com");
//	//http_client client(L"https://hobbyking.com/en_us/motor.html?kv=386-12000&");
//	// Make the request and asynchronously process the response. 
//	return client.request(methods::GET).then([](http_response response)
//	{
//		// Print the status code.
//		std::wostringstream ss;
//		ss << L"Server returned returned status code " << response.status_code() << L'.' << std::endl;
//		std::wcout << ss.str();
//
//		// TODO: Perform actions here reading from the response stream.
//		auto bodyStream = response.body().is_open();
//		std::wcout << L"zdr" << bodyStream << std::endl;
//		// In this example, we print the length of the response to the console.
//		ss.str(std::wstring());
//		ss << L"Content length is " << response.headers().content_length() << L" bytes." << std::endl;
//		std::wcout << ss.str();
//	});
//
//	/* Sample output:
//	Server returned returned status code 200.
//	Content length is 63803 bytes.
//	*/
//}
//
//// Builds an HTTP request that uses custom header values.
//pplx::task<void> HTTPRequestCustomHeadersAsync()
//{
//	//http_client client(L"http://www.fourthcoffee.com");
//	http_client client(L"https://hobbyking.com/en_us/motor.html?kv=386-11663&p=1");
//	// Manually build up an HTTP request with header and request URI.
//	http_request request(methods::GET);
//	//request.headers().add(L"kv", L"386-12000");
//	//request.headers().add(L"MyHeaderField", L"MyHeaderValue");
//	//request.set_request_uri(L"requestpath");
//	return client.request(request).then([](http_response response)
//	{
//		// Print the status code.
//		std::wostringstream ss;
//		ss << L"Server returned returned status code ????" << response.status_code() << L"." << std::endl;
//		std::wcout << ss.str();
//
//		auto bodyStream = response.body().is_open();
//		std::wcout << L"zdr" << bodyStream << std::endl;
//	});
//
//	/* Sample output:
//	Server returned returned status code 200.
//	*/
//}
//
//// Upload a file to an HTTP server.
//pplx::task<void> UploadFileToHttpServerAsync()
//{
//	using concurrency::streams::file_stream;
//	using concurrency::streams::basic_istream;
//
//	// To run this example, you must have a file named myfile.txt in the current folder. 
//	// Alternatively, you can use the following code to create a stream from a text string. 
//	// std::string s("abcdefg");
//	// auto ss = concurrency::streams::stringstream::open_istream(s); 
//
//	// Open stream to file. 
//	return file_stream<unsigned char>::open_istream(L"myfile.txt").then([](pplx::task<basic_istream<unsigned char>> previousTask)
//	{
//		try
//		{
//			auto fileStream = previousTask.get();
//
//			// Make HTTP request with the file stream as the body.
//			http_client client(L"http://www.fourthcoffee.com");
//			return client.request(methods::PUT, L"myfile", fileStream).then([fileStream](pplx::task<http_response> previousTask)
//			{
//				fileStream.close();
//
//				std::wostringstream ss;
//				try
//				{
//					auto response = previousTask.get();
//					ss << L"Server returned returned status code " << response.status_code() << L"." << std::endl;
//				}
//				catch (const http_exception& e)
//				{
//					ss << e.what() << std::endl;
//				}
//				std::wcout << ss.str();
//			});
//		}
//		catch (const std::system_error& e)
//		{
//			std::wostringstream ss;
//			ss << e.what() << std::endl;
//			std::wcout << ss.str();
//
//			// Return an empty task. 
//			return pplx::task_from_result();
//		}
//	});
//
//	/* Sample output:
//	The request must be resent
//	*/
//}
//
//int wmain()
//{
//	// This example uses the task::wait method to ensure that async operations complete before the app exits.  
//	// In most apps, you typically don�t wait for async operations to complete.
//
//	std::wcout << L"Calling HTTPStreamingAsync..." << std::endl;
//	HTTPStreamingAsync().wait();
//
//	std::wcout << L"Calling HTTPRequestCustomHeadersAsync..." << std::endl;
//	HTTPRequestCustomHeadersAsync().wait();
//
//	//std::wcout << L"Calling UploadFileToHttpServerAsync..." << std::endl;
//	//UploadFileToHttpServerAsync().wait();
//}

//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//#include <iostream>
//
//using namespace rapidjson;
//
//int main() {
//	// 1. Parse a JSON string into DOM.
//	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
//	Document d;
//	d.Parse(json);
//
//	// 2. Modify it by DOM.
//	Value& s = d["stars"];
//	s.SetInt(s.GetInt() + 1);
//
//	// 3. Stringify the DOM
//	StringBuffer buffer;
//	Writer<StringBuffer> writer(buffer);
//	d.Accept(writer);
//
//	// Output {"project":"rapidjson","stars":11}
//	std::cout << buffer.GetString() << std::endl;
//	return 0;
//}

//
//#include <ios>
//#include <iostream>
//#include "sqlite3.h"
//
//using namespace std;
//
//int main()
//{
//	int rc;
//	char *error;
//
//	// Open Database
//	cout << "Opening MyDb.db ..." << endl;
//	sqlite3 *db;
//	rc = sqlite3_open("MyDb.db", &db);
//	if (rc)
//	{
//		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
//		sqlite3_close(db);
//		return 1;
//	}
//	else
//	{
//		cout << "Opened MyDb.db." << endl << endl;
//	}
//
//	// Execute SQL
//	cout << "Creating MyTable ..." << endl;
//	const char *sqlCreateTable = "CREATE TABLE MyTable (id INTEGER PRIMARY KEY, value STRING);";
//	rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
//	if (rc)
//	{
//		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
//		sqlite3_free(error);
//	}
//	else
//	{
//		cout << "Created MyTable." << endl << endl;
//	}
//
//	// Execute SQL
//	cout << "Inserting a value into MyTable ..." << endl;
//	const char *sqlInsert = "INSERT INTO MyTable VALUES(NULL, 'A Value');";
//	rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
//	if (rc)
//	{
//		cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
//		sqlite3_free(error);
//	}
//	else
//	{
//		cout << "Inserted a value into MyTable." << endl << endl;
//	}
//
//	// Display MyTable
//	cout << "Retrieving values in MyTable ..." << endl;
//	const char *sqlSelect = "SELECT * FROM MyTable;";
//	char **results = NULL;
//	int rows, columns;
//	sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
//	if (rc)
//	{
//		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
//		sqlite3_free(error);
//	}
//	else
//	{
//		// Display Table
//		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
//		{
//			for (int colCtr = 0; colCtr < columns; ++colCtr)
//			{
//				// Determine Cell Position
//				int cellPosition = (rowCtr * columns) + colCtr;
//
//				// Display Cell Value
//				cout.width(12);
//				cout.setf(ios::left);
//				cout << results[cellPosition] << " ";
//			}
//
//			// End Line
//			cout << endl;
//
//			// Display Separator For Header
//			if (0 == rowCtr)
//			{
//				for (int colCtr = 0; colCtr < columns; ++colCtr)
//				{
//					cout.width(12);
//					cout.setf(ios::left);
//					cout << "~~~~~~~~~~~~ ";
//				}
//				cout << endl;
//			}
//		}
//	}
//	sqlite3_free_table(results);
//
//	// Close Database
//	cout << "Closing MyDb.db ..." << endl;
//	sqlite3_close(db);
//	cout << "Closed MyDb.db" << endl << endl;
//
//	// Wait For User To Close Program
//	cout << "Please press any key to exit the program ..." << endl;
//	cin.get();
//
//	return 0;
//}



//#include <stdio.h>
//#include <stdint.h>
//#include "timer.h"
//
//#if __linux__ != 0
//// linux is LP64
//#define PRINT_U64		"%lu"
//#define LITERAL_U64(x)	x##UL
//#elif _WIN64 != 0
//// windows is LLP64
//#define PRINT_U64		"%llu"
//#define LITERAL_U64(x)	x##ULL
//#elif __APPLE__ != 0
//// osx is LP64
//#define PRINT_U64		"%lu"
//#define LITERAL_U64(x)	x##UL
//#else
//#error unsupported target platform
//#endif
//
//// target ISA support
//#define TARGET_ISA_AMD64	1
//#define TARGET_ISA_ARM64	2
//
//#if __x86_64__ != 0 || _M_AMD64 != 0
//#if _M_AMD64 != 0
//#include <intrin.h> // emmintrin.h is also present but it's incomplete under msvc
//#else
//#include <emmintrin.h>
//#endif
//#define TARGET_ISA	TARGET_ISA_AMD64
//
//#elif __ARM_ARCH == 8 || _M_ARM64 != 0
//#include <arm_neon.h>
//#define TARGET_ISA	TARGET_ISA_ARM64
//
//#else
//#error unsupported target ISA
//
//#endif
//
//// compiler support
//#if _WIN64 != 0
//#define ALIGN_DECL(alignment, decl) \
//	__declspec (align(alignment)) decl
//
//#else
//#define ALIGN_DECL(alignment, decl) \
//	decl __attribute__ ((aligned(alignment)))
//
//#endif
//
//#define TOP_ALIGN	32
//
//ALIGN_DECL(TOP_ALIGN, const volatile uint64_t fib[]) = { 1, 1, 2, 3 };
//
////
//// you can add your declarations here, given:
//// 1) they do not exceed 32 bytes in total (paddings for alignment non-withstanding)
//// 2) all declarations (even const) are volatile
////
//
//// fill this array with the remaining members of the fibonacci seqeunce (started by fib[] above) up to the 93rd member
//ALIGN_DECL(TOP_ALIGN, uint64_t res[93 - sizeof(fib) / sizeof(fib[0])]);
//
//int main(int, char**) {
//	const uint64_t t0 = timer_nsec();
//
//	const size_t rep = size_t(1e7);
//	for (size_t i = 0; i < rep; ++i) {
//		// computations follow (your code goes here)
//		uint64_t t_1 = fib[sizeof(fib) / sizeof(fib[0]) - 2];
//		uint64_t t_0 = fib[sizeof(fib) / sizeof(fib[0]) - 1];
//
//		const size_t trip = 93 - sizeof(fib) / sizeof(fib[0]);
//		for (size_t j = 0; j < trip; ++j) {
//			const uint64_t t = t_1 + t_0;
//			t_1 = t_0;
//			t_0 = t;
//			res[j] = t;
//		}
//	}
//
//	const uint64_t dt = timer_nsec() - t0;
//	const size_t res_last_i = sizeof(res) / sizeof(res[0]) - 1;
//
//	for (size_t i = 2; i <= res_last_i; ++i) {
//		if (res[i - 2] + res[i - 1] != res[i]) {
//			fprintf(stderr, "error at " PRINT_U64 " (" PRINT_U64 ", " PRINT_U64 ", " PRINT_U64 ")\n", i, res[i], res[i - 1], res[i - 2]);
//			return -1;
//		}
//	}
//	if (res[res_last_i] != LITERAL_U64(12200160415121876738)) {
//		fprintf(stderr, "error (" PRINT_U64 ")\n", res[res_last_i]);
//		return -1;
//	}
//
//	fprintf(stderr, PRINT_U64 ", %f\n", res[res_last_i], 1e-9 * dt);
//	return 0;
//}





//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <iterator>
//#include <set>
//#include <string>
//
//using namespace std;
//
//template<typename T>
//void printVector(const T& t) {
//	std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
//}
//
//int main()
//{
//	vector<int> a = { 1,3,4,5,6 };
//	printVector(a);
//}



















///////////////////////////////////////////////////////////////////////////////
///// Natural selection task http://acm.timus.ru/problem.aspx?space=388&num=2
///////////////////////////////////////////////////////////////////////////////
//
//int minElem = 100000;
//int mas[2] = { -1, -1 };
//
//bool hasBetterSeparation(int AandBVal, int AnotBVal, int BnotAVal, int notABVal) 
//{
//	vector<int> tmp = { AandBVal, AnotBVal, BnotAVal, notABVal };
//	int tmpVal = *max_element(tmp.begin(), tmp.end());
//	if (tmpVal < minElem)
//	{
//		minElem = tmpVal;
//		return true;
//	}
//	return false;
//}
//
//template <class T >
//void printVector(const T& container) 
//{
//	for (auto elem : container)
//	{
//		cout << elem << ' ';
//	}
//	cout << endl;
//}
//
//
//template <class T>
//void printSetElements(const T& vectorWithSets, const vector<int>& vecResult, int id1, int id2, string info) 
//{
//	cout << info << id1 << id2 << endl;
//
//	//cout << "Set on index: " << id1 << endl;
//	//printVector(vectorWithSets[id1]);
//	
//	//cout << "Set on index: " << id2 << endl;
//	//printVector(vectorWithSets[id2]);
//	
//	cout << "Resulting vector's size: " << vecResult.size() << endl;
//	printVector(vecResult);
//}
//// A & B
//size_t initializeVectorWithIntersectionOfTwoSetsAndReturnSize(int id1, int id2, vector<set<int> > & vectorWithSets, vector<int>& vectorResult)
//{
//	auto iterUnionOrTwoCourses = std::set_intersection(vectorWithSets[id1].begin(),
//		vectorWithSets[id1].end(),
//		vectorWithSets[id2].begin(),
//		vectorWithSets[id2].end(),
//		inserter(vectorResult, vectorResult.begin()));
//
//	//printSetElements(vectorWithSets, vectorResult, id1, id2, "intersection of two sets");
//
//	return vectorResult.size();
//}
//
//
///// A || B
//size_t initializeVectorWithUnionOfTwoSetsAndReturnSize(int id1, int id2, vector<set<int> > & vectorWithSets, vector<int>& vectorResult) 
//{
//	auto iterUnionOrTwoCourses = std::set_union(vectorWithSets[id1].begin(),
//		vectorWithSets[id1].end(),
//		vectorWithSets[id2].begin(),
//		vectorWithSets[id2].end(),
//		inserter(vectorResult, vectorResult.begin()));
//	
//	//printSetElements(vectorWithSets, vectorResult, id1, id2, "union of two sets");
//
//	return vectorResult.size();
//}
//
//
//size_t initializeVectorWithdifferenceOfTwoSetsAndReturnSize(int id1, int id2, vector<set<int> > & vectorWithSets, vector<int>& vectorResult)
//{
//	auto iterUnionOrTwoCourses = std::set_difference(vectorWithSets[id1].begin(),
//		vectorWithSets[id1].end(),
//		vectorWithSets[id2].begin(),
//		vectorWithSets[id2].end(),
//		inserter(vectorResult, vectorResult.begin()));
//
//	//printSetElements(vectorWithSets, vectorResult, id1, id2, "difference of two sets");
//
//	return vectorResult.size();
//}
//
//
//
//
//int main()
//{
//	int degProgrNInt = 0, courcesMInt = 0;
//	cin >> degProgrNInt >> courcesMInt;
//	///cout << "n number of degree programs" << degProgrNInt <<
//	///	"m number of cources" << courcesMInt << endl;
//	
//	vector<vector<char> > allPrograms;
//	vector<char> oneProgram;
//	oneProgram.reserve(courcesMInt);
//
//	char p;
//
//	if (degProgrNInt < 3 || courcesMInt > 100)
//		return -1; /// dummy error check
//	
//	for (int programs = 0 ; programs < degProgrNInt; ++programs)
//	{
//		for(int coursesCount = 0 ; coursesCount < courcesMInt ; ++coursesCount)
//		{
//			cin >> p;
//			oneProgram.push_back(p);
//		}
//		allPrograms.push_back(oneProgram);
//		oneProgram.resize(0);
//		//oneProgram.resize(courcesMInt);
//	}
//
//	/// Vector of set which has all programs which has the course
//	///
//	vector<set<int> > programsBelongingToSpecificCourseVectorSet;
//	set<int> tmpSet;
//	for (int singleCourse = 0 ; singleCourse < courcesMInt ; ++singleCourse)	
//	{
//		for (int degProgram = 0; degProgram < degProgrNInt; ++degProgram)
//		{
//			//cout << allPrograms[degProgram][singleCourse];
//			if ('1' == allPrograms[degProgram][singleCourse])
//			{
//				tmpSet.insert(degProgram); /// forgetting + 1 for real world index
//			}
//		}
//		programsBelongingToSpecificCourseVectorSet.push_back(tmpSet);
//		tmpSet.clear();
//	}
//
//	int n = { 0 };
//	vector<int> allProgs(degProgrNInt);
//	std::generate(allProgs.begin(), allProgs.end(), [&n] { return n++; });
//	vector<int> intersectOfTwoCourses;
//	intersectOfTwoCourses.reserve(courcesMInt);
//	
//	vector<int> unionOfTwoCourses;
//	unionOfTwoCourses.reserve(courcesMInt);
//	
//	vector<int> AnotBOfTwoCourses;
//	AnotBOfTwoCourses.reserve(courcesMInt);
//	
//	vector<int> BnotAOfTwoCourses;
//	BnotAOfTwoCourses.reserve(courcesMInt);
//	
//	vector<int> notBAOfTwoCourses;
//	notBAOfTwoCourses.reserve(courcesMInt);
//	int AandB = 100;
//	int AnotB = 100;
//	int BnotA = 100;
//	int allnotBandA = -1;
//	for (int course1 = 0 ; course1 < courcesMInt - 1 ; ++course1)
//	{
//		for (int course2 = course1 + 1 ; course2 < courcesMInt; ++course2)
//		{
//			//A&B
//			AandB = initializeVectorWithIntersectionOfTwoSetsAndReturnSize(course1, course2, programsBelongingToSpecificCourseVectorSet, intersectOfTwoCourses);
//			initializeVectorWithUnionOfTwoSetsAndReturnSize(course1, course2, programsBelongingToSpecificCourseVectorSet, unionOfTwoCourses);		
//			//A\B
//			AnotB = initializeVectorWithdifferenceOfTwoSetsAndReturnSize(course1, course2, programsBelongingToSpecificCourseVectorSet, AnotBOfTwoCourses);
//			//B\A
//			BnotA = initializeVectorWithdifferenceOfTwoSetsAndReturnSize(course2, course1, programsBelongingToSpecificCourseVectorSet, BnotAOfTwoCourses);
//			//U\(A&B)
//			auto iterUnionOrTwoCourses = std::set_difference(allProgs.begin(),
//				allProgs.end(),
//				unionOfTwoCourses.begin(),
//				unionOfTwoCourses.end(),
//				inserter(notBAOfTwoCourses, notBAOfTwoCourses.begin()));
//			allnotBandA = notBAOfTwoCourses.size();
//			
//			///cout << "Resulting vector size: "<< notBAOfTwoCourses.size() <<" result of U\A&B: " << endl;
//			///printVector(notBAOfTwoCourses);
//			/// clearing tmp vectors
//			intersectOfTwoCourses.resize(0);
//			unionOfTwoCourses.resize(0);
//			AnotBOfTwoCourses.resize(0);
//			BnotAOfTwoCourses.resize(0);
//			notBAOfTwoCourses.resize(0);
//			
//
//			if (hasBetterSeparation(AandB, AnotB, BnotA, allnotBandA))
//			{
//				///cout << "numbers which are changed in mas " << course1 << course2 << endl;
//				mas[0] = course1;
//				mas[1] = course2;
//			}
//			///cout << endl;
//
//		}
//		
//	}
//	cout << minElem << endl;
//	cout << mas[0] + 1 << ' ' << mas[1] + 1 << endl ;
//
//	
//}

///printSetElements(const T& a, int id1, int id2, string info)
/*cout << "union" << endl;
for (auto elem : unionOfTwoCourses)
{
cout << elem << ' ';
}*/

/// Check saved values
/*cout << "saved results:" << endl;
for (int programs = 0; programs < degProgrNInt; ++programs)
{
for (int coursesCount = 0; coursesCount < courcesMInt; ++coursesCount)
{

cout << allPrograms[programs][coursesCount] << ' ';
}
cout << endl;
}*/

///// Test values
//0 0 0 1
//0 0 1 0
//0 1 1 1
//1 1 1 1
//0 0 0 0
//1 0 0 1



/// Print set with courses
//for (auto vectorit : programsBelongingToSpecificCourseVectorSet)
//{
//	for (auto it : vectorit)
//	{
//		cout << it;
//	}
//	cout << endl;
//}






/////////////////////////////////////////////////////////////////////////////////
//
//
//if (degProgrNInt < 3 || courcesMInt > 100)
//return -1; /// dummy error check
//		   //for (int programs = 0; programs < degProgrNInt; ++programs)
//		   //{
//vector<bool> intVector(std::istream_iterator<bool>(cin),
//	std::istream_iterator<bool>());
////allPrograms.push_back((vector<bool>)intVector);
////}
//for (bool i : intVector)
//{
//
//}
///////////////////////////////////////////////////////////////////////////////



//const int marginTop = 50;
//const int marginLeft = 70;
//const int marginRight = 50;
//const int marginBottom = 30;
//
//const int screenWidth = 600;
//const int screenHeight = 380;
//
//const int encoderWidth = 800;
//const int encoderHeight = 480;
///// first transform old x - > new x
//void scaleAndTranslateCoords(int x, int y, int& resX, int & resY)
//{
//	float scaleWidth = (float)(screenWidth - marginLeft - marginRight) / (float)encoderWidth;
//	float scaleHeight = (float)(screenHeight - marginTop - marginBottom) / (float)encoderHeight;
//	//scale + translate
//	resX = x * scaleWidth + marginLeft;
//	resY = y * scaleHeight + marginTop;
//}
///// obratna transformaciq new x -> old x  << raboti
//void scaleAndTransformCoordsReverse1(float newX, float newY, float& x, float & y)
//{
//	float scaleWidth  = (float)(encoderWidth + marginLeft + marginRight) / (float)screenWidth ;
//	float scaleHeight = (float)(encoderHeight + marginTop + marginBottom) / (float)screenHeight;
//
//	x = (newX  - marginLeft)* scaleWidth;
//	y = (newY  - marginTop) * scaleHeight;
//}
//
//void scaleAndTransformCoordsReverse11(float newX, float newY, float& x, float & y)
//{
//	float scaleWidth = (float)(encoderWidth + marginLeft + marginRight) / screenWidth;
//	float scaleHeight = (float)(encoderHeight + marginTop + marginBottom) / screenHeight;
//
//	x = (newX )* scaleWidth - marginLeft;
//	y = (newY ) * scaleHeight - marginTop;
//}
//
//void scaleAndTransformCoordsReverse2(float newX, float newY, float& x, float & y)
//{
//	float scaleWidth = (float)(screenWidth - marginLeft - marginRight) / encoderWidth;
//	float scaleHeight = (float)(screenHeight - marginTop - marginBottom) / encoderHeight;
//
//	x = (newX - marginLeft)* scaleWidth;
//	y = (newY - marginTop) * scaleHeight;
//}
//
//void scaleAndTransformCoordsReverse3(int newX, int newY, int& x, int & y)
//{
//	float scaleWidth = (float)encoderWidth  / (float)(screenWidth - marginLeft - marginRight);
//	float scaleHeight = (float)encoderHeight / (float)(screenHeight - marginTop - marginBottom);
//
//	x = (newX - marginLeft)* scaleWidth;
//	y = (newY - marginTop) * scaleHeight;
//} 
//int main() 
//{
//	int originalX = 1200;
//	int originalY = 2000;
//
//	int tmpX;
//	int tmpY;
//
//	int resultX;
//	int resultY;
//	scaleAndTranslateCoords(originalX, originalY, tmpX, tmpY);
//	scaleAndTransformCoordsReverse3(tmpX, tmpY, resultX, resultY);
//	cout << originalX << ", " << originalY <<endl<< resultX << ", " << resultY;
//}




//#include <iostream>
//#include <stdio.h> 
//#include <curl/curl.h> 
//#include <string>
//
//int main(void)
//{
//	CURL *curl;
//	CURLcode res;
//	string a;
//	curl = curl_easy_init();
//	if (curl) {
//		curl_easy_setopt(curl, CURLOPT_URL, "https://hobbyking.com/en_us/motor.html?kv=386-11663&p=1");
//		
//		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &a);
//		res = curl_easy_perform(curl);
//
//		/* always cleanup */
//		curl_easy_cleanup(curl);
//	}
//	return 0;
//}
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <curl/curl.h>
//
//struct string1 {
//	char *ptr;
//	size_t len;
//};
//
//void init_string(struct string1 *s) {
//	s->len = 0;
//	s->ptr = (char*)malloc(s->len + 1);
//	if (s->ptr == NULL) {
//		fprintf(stderr, "malloc() failed\n");
//		exit(EXIT_FAILURE);
//	}
//	s->ptr[0] = '\0';
//}
//
//size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string1 *s)
//{
//	size_t new_len = s->len + size*nmemb;
//	s->ptr = (char*)realloc(s->ptr, new_len + 1);
//	if (s->ptr == NULL) {
//		fprintf(stderr, "realloc() failed\n");
//		exit(EXIT_FAILURE);
//	}
//	memcpy(s->ptr + s->len, ptr, size*nmemb);
//	s->ptr[new_len] = '\0';
//	s->len = new_len;
//
//	return size*nmemb;
//}
//
//int main(void)
//{
//	CURL *curl;
//	CURLcode res;
//
//	curl = curl_easy_init();
//	if (curl) {
//		struct string1 s;
//		init_string(&s);
//
//		curl_easy_setopt(curl, CURLOPT_URL, "https://hobbyking.com/en_us/motor.html?kv=386-11663&p=1");
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
//		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
//		res = curl_easy_perform(curl);
//
//		printf("%s\n", s.ptr);
//		free(s.ptr);
//
//		/* always cleanup */
//		curl_easy_cleanup(curl);
//	}
//	return 0;
//}
//
//#include <string.h>
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include "rapidxml-1.13/rapidxml.hpp"
//
//using namespace rapidxml;
//using namespace std;
//
//int main(void)
//{
//	cout << "Parsing my beer journal..." << endl;
//	xml_document<> doc;
//	xml_node<> * root_node;
//	// Read the xml file into a vector
//	ifstream theFile("a.xml");
//	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
//	buffer.push_back('\0');
//	// Parse the buffer using the xml file parsing library into doc 
//	doc.parse<0>(&buffer[0]);
//	// Find our root node
//	root_node = doc.first_node("div");
//	// Iterate over the brewerys
//	for (xml_node<> * brewery_node = root_node->first_node("Brewery"); brewery_node; brewery_node = brewery_node->next_sibling())
//	{
//		printf("I have visited %s in %s. ",
//			brewery_node->first_attribute("name")->value(),
//			brewery_node->first_attribute("location")->value());
//		// Interate over the beers
//		for (xml_node<> * beer_node = brewery_node->first_node("Beer"); beer_node; beer_node = beer_node->next_sibling())
//		{
//			printf("On %s, I tried their %s which is a %s. ",
//				beer_node->first_attribute("dateSampled")->value(),
//				beer_node->first_attribute("name")->value(),
//				beer_node->first_attribute("description")->value());
//			printf("I gave it the following review: %s", beer_node->value());
//		}
//		cout << endl;
//	}
//}
//
//#include <tidy.h>
//#include <tidybuffio.h>
//#include <stdio.h>
//#include <errno.h>
//#include <fstream>
//#include <vector>
//
//
//
////	ifstream theFile("abc.xml");
////	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
////	buffer.push_back('\0');
//int main(int argc, char **argv)
//{
//	ifstream theFile("a.txt");
//	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
//	buffer.push_back('\0');
//
//	const char* input = "<title>Foo</title><p>Foo!";
//	TidyBuffer output = { 0 };
//	TidyBuffer errbuf = { 0 };
//	int rc = -1;
//	Bool ok;
//
//	TidyDoc tdoc = tidyCreate();                     // Initialize "document"
//	printf("Tidying:\t%s\n", input);
//
//	ok = tidyOptSetBool(tdoc, TidyXhtmlOut, yes);  // Convert to XHTML
//	if (ok)
//		rc = tidySetErrorBuffer(tdoc, &errbuf);      // Capture diagnostics
//	if (rc >= 0)
//		//rc = tidyParseFile(tdoc, "a.txt");
//		rc = tidyParseString(tdoc, input);           // Parse the input
//	if (rc >= 0)
//		rc = tidyCleanAndRepair(tdoc);               // Tidy it up!
//	if (rc >= 0)
//		rc = tidyRunDiagnostics(tdoc);               // Kvetch
//	if (rc > 1)                                    // If error, force output.
//		rc = (tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1);
//	if (rc >= 0)
//		rc = tidySaveBuffer(tdoc, &output);          // Pretty Print
//
//	if (rc >= 0)
//	{
//		if (rc > 0)
//			printf("\nDiagnostics:\n\n%s", errbuf.bp);
//		printf("\nAnd here is the result:\n\n%s", output.bp);
//	}
//	else
//		printf("A severe error (%d) occurred.\n", rc);
//
//	tidyBufFree(&output);
//	tidyBufFree(&errbuf);
//	tidyRelease(tdoc);
//	return rc;
//}

/**
* section: Parsing
* synopsis: Parse an XML document in memory to a tree and free it
* purpose: Demonstrate the use of xmlReadMemory() to read an XML file
*          into a tree and and xmlFreeDoc() to free the resulting tree
* usage: parse3
* test: parse3
* author: Daniel Veillard
* copy: see Copyright for the status of this software.
*/
//
//#include <stdio.h>
//#include <libxml/parser.h>
//#include <libxml/tree.h>
//
//static const char *document = "<doc/>";
//
///**
//* example3Func:
//* @content: the content of the document
//* @length: the length in bytes
//*
//* Parse the in memory document and free the resulting tree
//*/
//static void
//example3Func(const char *content, int length) {
//	xmlDocPtr doc; /* the resulting document tree */
//
//				   /*
//				   * The document being in memory, it have no base per RFC 2396,
//				   * and the "noname.xml" argument will serve as its base.
//				   */
//	doc = xmlReadMemory(content, length, "a.xml", NULL, 0);
//	if (doc == NULL) {
//		fprintf(stderr, "Failed to parse document\n");
//		return;
//	}
//	xmlFreeDoc(doc);
//}
//
//int main(void) {
//	/*
//	* this initialize the library and check potential ABI mismatches
//	* between the version it was compiled for and the actual shared
//	* library used.
//	*/
//	LIBXML_TEST_VERSION
//
//		example3Func(document, 6);
//
//	/*
//	* Cleanup function for the XML library.
//	*/
//	xmlCleanupParser();
//	/*
//	* this is to debug memory for regression tests
//	*/
//	xmlMemoryDump();
//	return(0);
//}