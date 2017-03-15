/////////////////////////////////////
///// Includes
//////////////////////
#include <ios>
#include <iostream>
#include <algorithm>    // std::sort
#include <string>
#include <vector>
#include "sqlite3.h"

#include "AlgorithmDC.h"



////////////////
// ImGui - standalone example application for Glfw + OpenGL 2, using fixed pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <stdio.h>
#include <GLFW/glfw3.h>


using namespace std;

/////////////////////////////////////
///// Functions
//////////////////////
// geti diam and pitch in inches



CProps bestProp;
CMotorHK bestMotor;

int main2()
{
	sqlite3 *db = NULL;
	openSQLiteDb(db, "test.db");
	std::cout << "Retrieving values in MyTable ... " << endl;


	std::vector<CProps> vectorProps = getPropsVectorFromSQLiteParsingDB(db);
	getPropsAppropriateforThrustSorted(vectorProps, expectedThrustFromOneMotorInKg);
	
	std::vector<CMotorHK> vectorMotors = getMotorVectorFromSQLiteParsingDB(db);
	
	/// Creating new motors vector list with corrected data and info
	vector<CMotorHK> vect;
	vect = correctingMotorData(vectorMotors);
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
/// http://www.electricrcaircraftguy.com/2014/04/propeller-static-dynamic-thrust-equation-background.html