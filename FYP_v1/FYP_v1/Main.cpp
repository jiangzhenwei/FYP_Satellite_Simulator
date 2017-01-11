#include <iostream>
#include <string>
#include "SpacecraftDynamics.h"
#include "Storage.h"

using namespace std;

int main(void) 
{
	/*
	For user input :
	cout << "Enter tX: " << endl;
	cin >> tX;
	cout << "Enter tY: " << endl;
	cin >> tY;
	cout << "Enter tZ: " << endl;
	cin >> tZ;
	cout << "Enter I_xx: " << endl;
	cin >> I_x;
	cout << "Enter I_yy: " << endl;
	cin >> I_y;
	cout << "Enter I_zz: " << endl;
	cin >> I_z;
	*/

	SpacecraftDynamics s1;
	s1.setMOIValues(3.4, 2.18, 1.68);
	s1.setTorque(0.01, 0.01, 0.01);
	s1.setInitialW(0.0, 0.0, 0.0);
	s1.setStepSize(0.02);
	s1.setQuaternionInitialValues(0.01, 0.01, 0.01, 0.01);
	s1.findConstants();
	//run RK4 150 times, 50 for positive torque, 50 in negative torque and 50 with no torque after application of previous torques
	for (int i = 0; i < 9000; i++) 
	{
		//Switch torque values after numberofiterations/timestep iterations
		if (i == 1499) 
		{ 
			s1.setTorque(0.0, 0.0, 0.0);
		}

		//no more torque after 100 iterations
		if (i == 2999) 
		{
			s1.setTorque(-0.01, -0.01, -0.01);
		}

		if (i == 4499)
		{
			s1.setTorque(0.0, 0.0, 0.0);
		}

		///Find acceleration, next velocity and quaternion values and store all values in text file
		s1.findAcc();
		s1.storeValues();
		s1.getNextw();
		s1.findNextQuaternion();
	} 
	system("PAUSE");
}