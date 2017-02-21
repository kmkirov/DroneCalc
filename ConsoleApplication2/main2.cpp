/////////////////////////////////////
///// Includes
//////////////////////
#include <ios>
#include <iostream>
#include <algorithm>    // std::sort
#include "sqlite3.h"
#include "Constants.h"


////////////////
// ImGui - standalone example application for Glfw + OpenGL 2, using fixed pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

#include <Windows.h>
using namespace std;

/////////////////////////////////////
///// Functions
//////////////////////
// geti diam and pitch in inches


void readSQLiteDBAndReturnResults(sqlite3* db, std::string& exec, int& rows, int& cols, char*** results) 
{	
	char *error;
	int rc = sqlite3_get_table(db, exec.c_str(), results, &rows, &cols, &error);
	if (rc)
	{
		cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_free(error);
		///exit ?
	}
}

void openSQLiteDb(sqlite3* & db, string dbName) 
{
	int rc;
	char *error;

	// Open Database
	cout << "Opening " << dbName << endl;

	
	rc = sqlite3_open(dbName.c_str(), &db);
	if (rc)
	{
		cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << endl << endl;
		sqlite3_close(db);
		return;// exit
	}
	else
	{
		cout << "Openning " << dbName << endl << endl;
	}
}
void closeSQLiteDb(sqlite3 * db)
{
	// Close Database
	cout << "Closing MyDb.db ..." << endl;
	sqlite3_close(db);
	cout << "Closed MyDb.db" << endl << endl;

	// Wait For User To Close Program
	cout << "Please press any key to exit the program ..." << endl;
	//cin.get();
}
const float wantedThrust = 0;
/// wantedThrust = 4 * expectedThrustFromOneMotorInKg
float expectedThrustFromOneMotorInKg = 0.5;//5.9;

float WEIGHTCONSTANTMIN = 2.0;
float WEIGHTCONSTANTMAX = 100;//2.2;
float RPMCOEF = 1.2;

float MOTORPOWERCOEF = 2;
float MOTORPOWERVALUE = 1.3;

float droneWeight = 1;
float wantedDroneWeihgtThrust = droneWeight * WEIGHTCONSTANTMIN;

float EFFECTIVETHRUST = 0.7;

bool propComparator(CProps a, CProps b) 
{
	return a.mf_diameter < b.mf_diameter;
	//return a.mf_maxThrust < b.mf_maxThrust;
}

bool motorComparator(CMotorHK a, CMotorHK b)
{
	return a.mf_maxEffPersentage70 > b.mf_maxEffPersentage70;
}


void sortMotors(vector<CMotorHK> & vec)
{
	sort(vec.begin(), vec.end(), motorComparator);
}

void sortAndResizeVectorProps(vector<CProps> & vec) 
{
	sort(vec.begin(), vec.end(), propComparator);
	if (vec.size() > 5)
	{
		vec.resize(5);
	}
}

void filterPropellersAccordingToThrustNeeded(float thrust, vector<CProps> & vec) 
{
	vector<CProps> newVect;
	std::cout << thrust/0.102 << std::endl;
	for (auto & elem : vec) 
	{ 
		if (elem.mf_maxRPM < elem.mf_wantedThrustRPM) 
		{
			continue;
		}
		if (!(elem.mf_maxThrust > WEIGHTCONSTANTMIN * thrust && elem.mf_maxThrust < WEIGHTCONSTANTMAX * thrust))
		{
			continue;
		}
		newVect.push_back(elem);
	}
	
	vec = newVect;
}

vector<CMotorHK> getFastCalculatedMotorsCapabilities(vector<CMotorHK> & vectorMotors, CProps & prop1, float  expectedThrustFromOneMotorInKg) 
{
	std::vector<CMotorHK> vectorPossibleMotors;
	for (auto & elem : vectorMotors) 
	{
		calcAdditionalParamsForProps(prop1, expectedThrustFromOneMotorInKg + elem.mf_weight);
		
		float voltageNeeded = prop1.mf_wantedThrustRPM / elem.mf_Kv; /// const needed ?!
		float neededCurrent = prop1.mf_powerNeededInWatts / voltageNeeded;
		
		elem.mf_neededCurrent = neededCurrent;
		elem.mf_neededPower = neededCurrent * voltageNeeded;
		elem.mf_neededVoltage = voltageNeeded;
		vectorPossibleMotors.push_back(elem);
	}
	return vectorPossibleMotors;
}

void fast(vector<CMotorHK> & vectorMotors, CProps & prop1, float p, float expectedThrustFromOneMotorInKg)
{
	for (auto & elem : vectorMotors)
	{
		calcAdditionalParamsForProps(prop1, expectedThrustFromOneMotorInKg * p + elem.mf_weight);
		float voltageNeeded = prop1.mf_wantedThrustRPM / elem.mf_Kv;
		float neededCurrent = prop1.mf_powerNeededInWatts / voltageNeeded;
		

		float powerIn = elem.mf_neededVoltage * elem.mf_neededCurrent;
		float powerOut = (neededCurrent - elem.mf_noLoadCurrent) * (voltageNeeded - neededCurrent * elem.mf_resistance);

		elem.mf_maxEffPersentage70 =  powerOut / powerIn;
		elem.mf_effectiveCurrent70 = neededCurrent;
	}
	
}

vector<CMotorHK> filterMotorsByCapabilities(vector<CMotorHK> & vectorMotors, CProps & prop1, float  expectedThrustFromOneMotorInKg)
{
	std::vector<CMotorHK> vectorPossibleMotors;
	for (auto  elem : vectorMotors)
	{
		/// adding weight to expecetr trhust with mass of the motor
		calcAdditionalParamsForProps(prop1, expectedThrustFromOneMotorInKg + elem.mf_weight);/// rmp for motor weight and payload
																							 /// check the prop again
		if (prop1.mf_maxRPM < prop1.mf_wantedThrustRPM)
		{
			continue;
		}

		/// check if potor haz the power to lift the thing
		if (!(elem.mf_maxPower > prop1.mf_powerNeededInWatts &&  elem.mf_maxPower < prop1.mf_powerNeededInWatts * MOTORPOWERCOEF))
		{
			continue;
		}
		/// check voltage for the rpm needed
		//1. calculating how much voltage we need for rpm
		float voltageNeeded = prop1.mf_wantedThrustRPM / elem.mf_Kv; /// const needed ?!
		if (elem.mf_maxVoltage < voltageNeeded)
		{
			continue;
		}
		/// remove if max current is less than needed current
		float neededCurrent = prop1.mf_powerNeededInWatts / voltageNeeded;
		if (elem.mf_maxCurrent < neededCurrent)
		{
			continue;
		}
		elem.mf_maxRPM = elem.mf_Kv * elem.mf_maxVoltage; 
		elem.mf_neededCurrent = neededCurrent;
		elem.mf_neededPower = neededCurrent * voltageNeeded;
		elem.mf_neededVoltage = voltageNeeded;
		vectorPossibleMotors.push_back(elem);
	}
	return vectorPossibleMotors;
}

float returnEffectivenessOfMotor(CMotorHK & motor)
{

	float powerIn = motor.mf_neededVoltage * motor.mf_neededCurrent;
	float powerOut = (motor.mf_neededCurrent - motor.mf_noLoadCurrent) * (motor.mf_neededVoltage - motor.mf_neededCurrent * motor.mf_resistance);

	return powerOut / powerIn;
}

void calcEffectivePowerForMotors(vector<CMotorHK> & motors) 
{
	for (auto& elem : motors) 
	{
		elem.mf_bestCurrentEffectiveness = sqrt(elem.mf_maxCurrent*elem.mf_noLoadCurrent);
		elem.mf_bestMotorEffectiveness =  pow(((elem.mf_bestCurrentEffectiveness - elem.mf_noLoadCurrent) / elem.mf_bestCurrentEffectiveness), 2.0);
		
		elem.mf_maxEffPersentage100 = returnEffectivenessOfMotor(elem);


		cout << " eff current " << elem.mf_bestCurrentEffectiveness << "maxEffectivePersentage " << elem.mf_bestMotorEffectiveness << " effPower " << elem.mf_maxEffPersentage100;
	}
	
}

void getPropsAppropriateforThrustSorted(vector<CProps>& vectorProps, float expectedThrustFromOneMotorInKg)
{
	/// working with vector and adding additional info
	setAdditionalParamsToVectorProps(vectorProps, expectedThrustFromOneMotorInKg);/// need changes here ! ++optimization
																				  /// remove all unused propellers ima oshte rabota tuk !
	filterPropellersAccordingToThrustNeeded(expectedThrustFromOneMotorInKg, vectorProps);
	/// sort according to maxt thrust and select top 5 propellers
	sortAndResizeVectorProps(vectorProps);

	for (auto& elem : vectorProps)
	{
		std::cout << elem;
	}

}

vector<CProps> getPropsVectorFromSQLiteParsingDB(sqlite3 * db) 
{
	std::string sqlExPropellers = SQLSELECTSTAR + PROPELLERSTABLENAME + ENDSEMICOLLUMN;
	/// results from db
	char **results = NULL;
	int rows, columns;
	readSQLiteDBAndReturnResults(db, sqlExPropellers, rows, columns, &results);
	auto vectorProps = parseSQLiteToVectorOfProps(results, rows, columns);
	sqlite3_free_table(results);
	results = NULL;
	return vectorProps;
}


vector<CMotorHK> getMotorVectorFromSQLiteParsingDB(sqlite3 * db)
{
	std::string sqlExMotor = SQLSELECTSTAR + MOTORSTABLENAME + ENDSEMICOLLUMN;
	/// results from db
	char **results = NULL;
	int rows, columns;
	readSQLiteDBAndReturnResults(db, sqlExMotor, rows, columns, &results);
	std::vector<CMotorHK> vectorMotors = parseSQLiteToVectorOfMotors(results, rows, columns);
	sqlite3_free_table(results);
	results = NULL;
	return vectorMotors;
}

CProps bestProp;
CMotorHK bestMotor;
int main2()
{
	sqlite3 *db = NULL;
	openSQLiteDb(db, "test.db");
	std::cout << "Retrieving values in MyTable ..." << endl;


	vector<CProps> vectorProps = getPropsVectorFromSQLiteParsingDB(db);
	getPropsAppropriateforThrustSorted(vectorProps, expectedThrustFromOneMotorInKg);
	
	auto vectorMotors = getMotorVectorFromSQLiteParsingDB(db);
	
	/// Creating new motors vector list with corrected data and info
	auto vect = correctingMotorData(vectorMotors);
	/// adding maxRPM, effectiveRPM,
	std::vector<CMotorHK> vectorPossibleMotors100;
	// sorting depending on power and removing under powered solutions
	/// remove all motors that cant handle self and propeller weight
	/// for prop in vec props stops if vector motors is not 0 sized
	for (auto elem : vectorProps)
	{
		auto prop1 = elem;
		vectorPossibleMotors100 = filterMotorsByCapabilities(vectorMotors, prop1, expectedThrustFromOneMotorInKg);
		if (!vectorPossibleMotors100.size()) 
		{
			continue; //big problem
		}

		calcEffectivePowerForMotors(vectorPossibleMotors100);
		fast(vectorPossibleMotors100, prop1, EFFECTIVETHRUST, expectedThrustFromOneMotorInKg);
		sortMotors(vectorPossibleMotors100);

		for (auto elem : vectorPossibleMotors100)
		{
			cout << std::endl;
			cout << " 100 efficeicu % " << elem.mf_maxEffPersentage100 << " best %" << elem.mf_bestMotorEffectiveness << " eff current " << elem.mf_bestCurrentEffectiveness << std::endl
				<< " 70 efficeicu % "<< elem.mf_maxEffPersentage70 <<" 70% current"  << elem.mf_effectiveCurrent70 << std::endl;
		}

		/// if we have motor we are not doing the same with other props
		for (auto& elem : vectorPossibleMotors100)
		{
			std::cout << elem;
		}
		bestMotor = vectorPossibleMotors100[0];
		bestProp = prop1;
		break;
	}

	closeSQLiteDb(db);

	return 0;
}



static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}





void goToPageWithDefaultBrowser(std::string url)
{
	HWND hwnd = GetDesktopWindow();
	ShellExecute(hwnd, L"open", std::wstring(url.begin(), url.end()).c_str(), NULL, NULL, NULL);
}

float calculateSpeedOfMotorInMetersPerSecond(const CMotorHK & motor, const CProps & prop) 
{/// http://www.mh-aerotools.de/airfoils/pylonprops_1.htm
	return 3.14159265359 * (motor.mf_Kv * motor.mf_neededVoltage/60.0) * prop.mf_diameter * 0.0254;
}

int main(int, char**)
{
	// Setup window
	
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;
	GLFWwindow* window = glfwCreateWindow(720, 450, "Drone Static Thrust Calculator - Drone Calc", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Setup ImGui binding
	ImGui_ImplGlfw_Init(window, true);

	//////////////

	bool show_test_window = true;
	bool show_another_window = true;
	ImVec4 clear_color = ImColor(114, 144, 154);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		ImGui_ImplGlfw_NewFrame();

		// 1. Show a simple window
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		{
			static float wantedKg = 0.0f;
			static float oldValue = 0.0f;
			ImGui::Text("Welcome to DroneCalc!");
			ImGui::Text("Enter drone payload in kg:");
			ImGui::InputFloat("##KG", &wantedKg, 0.1, 0.2, 3);
			//ImGui::ColorEdit3("clear color", (float*)&clear_color);
			ImGui::Text("Enter drone payload in kg %f:", wantedKg);
			if (wantedKg && abs(wantedKg - oldValue) > 0.05 )
			{
				expectedThrustFromOneMotorInKg = wantedKg / 4.0;
				oldValue = wantedKg;
				main2();
			}
			ImGui::Text("Flight time for battery of 1 Wh in minutes: %f", 60.0 / bestMotor.mf_neededCurrent);//60.f / bestMotor.mf_neededCurrent);
			ImGui::Text("Max speed in m/s: %f", calculateSpeedOfMotorInMetersPerSecond(bestMotor, bestProp));
			ImGui::Text("Prop name %s:", bestProp.ms_name.c_str());//, bestMotor.mf_neededCurrent, 60.0 / bestMotor.mf_neededCurrent, calculateSpeedOfMotorInMetersPerSecond(bestMotor, bestProp));
			//ImGui::Text("Motor Link: %s", bestMotor.ms_URL);
		//	ImGui::Text("Propeller Link: %s and adress %s", bestProp.ms_name );
			if (ImGui::Button("Go To Motor Link")) 
			{
				goToPageWithDefaultBrowser(bestMotor.ms_URL);
			} 
			if (ImGui::Button("Go To Props Link"))
			{
				std::string propsFilter = "https://hobbyking.com/en_us/propeller.html";
				std::string diamAttr = "?diameter_x=" + to_string(bestProp.mf_diameter) + "-" + to_string(bestProp.mf_diameter + 1);
				std::string propAttr = "&pitch_y=" + to_string(bestProp.mf_pitch) + "-15";;
				goToPageWithDefaultBrowser(propsFilter + diamAttr + propAttr);
			}
			//if (ImGui::Button("Another Window")) show_another_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}
		//    // Rendering
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfw_Shutdown();
	glfwTerminate();

	return 0;
}

//// http://klsin.bpmsg.com/how-fast-can-a-quadcopter-fly/
//// http://aviation.stackexchange.com/questions/8819/is-there-any-equation-to-bind-velocity-thrust-and-power/8822#8822