#pragma config(Sensor, in8,    potent,         sensorPotentiometer)
#pragma config(Sensor, dgtl9,  lshaft,         sensorQuadEncoder)
#pragma config(Motor,  port1,           claw1,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           lift1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           lift2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          claw2,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void claw(int degree)
{
	degree = degree*5;
	while(nMotorEncoder[claw2] > degree)
	{
		motor[claw1] = motor[claw2] = 120;
	}
	while(nMotorEncoder[claw2] < degree)
	{
		motor[claw1] = motor[claw2] = -120;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void move(int dis)
{
	int dis2 = dis*360/(4*3.1415926535);
	while(nMotorEncoder[rightMotor] < dis2)
	{
		motor[leftMotor] = motor[rightMotor] = 127;
	}
	while(nMotorEncoder[rightMotor] > dis2)
	{
		motor[leftMotor] = motor[rightMotor] = -127;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
void toFence()//brings robot backwards and throws
{nMotorEncoder[rightMotor] = nMotorEncoder[lift2] = nMotorEncoder[claw2] = 0;
	while(nMotorEncoder[rightMotor] > -30*360/(4*3.1415926535) || nMotorEncoder[lift2] < 120)
	{
		motor[rightMotor] = motor[leftMotor]= -127;
		motor[lift1] = motor[lift2] = 127;
	}
	while(nMotorEncoder[rightMotor] > -34*360/(4*3.1415926535))
	{
		motor[rightMotor] = motor[leftMotor]= -127;
		motor[lift1] = motor[lift2] = 127;
		motor[claw1] = motor[claw2] = 127;
	}
}

void toLoad()//brings arm down then returns for driver load
{nMotorEncoder[rightMotor] = nMotorEncoder[lift2] = nMotorEncoder[claw2] = 0;
	while(nMotorEncoder[lift2] > 120)
	{
		motor[rightMotor] = motor[leftMotor] = 127;
		motor[lift1] = motor[lift2] = -127;
	}
	while(nMotorEncoder[rightMotor] < 34*360/(4*3.1415926535))
		{
			motor[rightMotor] = motor[leftMotor] = 127;
		}
}
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	nMotorEncoder[claw2] = nMotorEncoder[leftMotor] = nMotorEncoder[rightMotor] = nMotorEncoder[lift2] = 0;
while(nMotorEncoder[rightMotor] > -720)
{
	motor[rightMotor] = motor[leftMotor] = -127;
}

	claw(150);





}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		int leftstick = vexRT[Ch3];
		int rightstick = vexRT[Ch2];
		int liftbuttonU = vexRT[Btn6U];
		int liftbuttonD = vexRT[Btn6D];
		int clawopen = vexRT[Btn5U];
		int clawclose = vexRT[Btn5D];


		//left motor control
		if (leftstick > 10 || leftstick < -10){
			motor [leftMotor] = leftstick;
			//			motor [leftMotorB] = leftstick;
		}
		else
			motor [leftMotor] = 0;
		//			motor [leftMotorB] = 0;

		//right motor control
		if (rightstick > 10 || rightstick <-10){
			motor [rightMotor] = rightstick;
			//			motor [rightMotorB] = rightstick;
		}
		else
			motor [rightMotor] = 0;
		//			motor [rightMotorB] = 0;

		//Lift control
		if (liftbuttonU == 1){
			motor [lift1] = -127;
			motor[lift2] = -127;
		}
		else if (liftbuttonD == 1){
			motor [lift1] = 127;
			motor[lift2] = 127;
		}
		else {
			motor [lift1] = 0;
			motor[lift2] = 0;
		}
		//Claw control
		if (clawopen == 1){
			motor [claw1] = 127;
			motor [claw2] = 127;
		}
		else if (clawclose == 1){
			motor [claw1] = -127;
			motor [claw2] = -127;
		}
		else{
			motor[claw1] = 10;
			motor[claw2] = -10;}
	}

}
