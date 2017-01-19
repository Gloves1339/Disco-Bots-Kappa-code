#pragma config(Sensor, dgtl9,  lshaft,         sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rshaft,         sensorQuadEncoder)
#pragma config(Motor,  port1,           claw1,          tmotorVex393, openLoop)
#pragma config(Motor,  port10,          claw2,          tmotorVex393, openLoop)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393, openLoop)
#pragma config(Motor,  port6,           lift1,          tmotorVex393, openLoop)
#pragma config(Motor,  port7,           lift2,          tmotorVex393, openLoop)
#pragma config(Motor,  port9,           leftMotor,     tmotorVex393, openLoop)
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

task autonomous()
{
	wait1Msec(1000);  // 1 Second Delay

	//Clear Encoders
	SensorValue[lshaft] = 0;
	SensorValue[rshaft] = 0;

	while(SensorValue[rshaft] < 360)  // While less than 2 rotations on the leftEncoder...
	{
		//...Move Forward
		motor[rightMotor] = 127;
		motor[leftMotor] = 127;

	}
	wait1Msec(500);

	motor[lift1] = 127;
	motor[lift2] = 127;
	wait1Msec(3000);
	motor[lift1] = 127;
	motor[lift2] = 127;

	motor[claw1] = 127;
	motor[claw2] = 127;
	wait1Msec(500);
	motor[claw1] = 0;
	motor[claw2] = 0;

	motor[rightMotor] = 127;
	wait1Msec(500);
	motor[rightMotor] = 0;

	motor[rightMotor] = 127;
	motor[leftMotor] = 127;
	wait1Msec(5000);
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;



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
			motor[claw2] = 127;
		}
		else if (clawclose == 1){
			motor [claw1] = -127;
			motor[claw2] = -127;
		}
		else{
			motor[claw1] = 10;
			motor[claw2] = -10;}
	}

}
