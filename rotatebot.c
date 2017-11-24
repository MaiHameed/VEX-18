#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           backR,         tmotorVex393TurboSpeed_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           frontR,        tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           frontL,        tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           backL,         tmotorVex393TurboSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void gyroinit() {
	SensorType[gyro] = sensorNone;
	wait1Msec(300);
	SensorType[gyro] = sensorGyro;
	wait1Msec(2000);
}

void rotateBot(int anglex10){
	float startAngle = SensorValue[in1];
	//perfect values - p: .9, i - 0, d:4.4 (speed at .7)
	float kp = 0.9;
	float ki = 0;
	float kd = 4.4;

	float speed = 0;
	int error2 = 1, integral = 0;
	float error = anglex10 - (SensorValue[in1] - startAngle);
	float gyro0 = SensorValue[in1];

	while (abs(error) > 15) {
		error = anglex10 - (SensorValue[in1] - startAngle);
		float speed = 0.7*(error*kp) + ((error - error2)*kd);

		motor[backR] = -speed;
		motor[frontR] = -speed;
		motor[backL] = speed;
		motor[frontL] = speed;

		error2 = error;
		wait1Msec(20);
	}
	motor[backR] = 0;
	motor[frontR] = 0;
	motor[backL] = 0;
	motor[frontL] = 0;
}

void rotateLeft (int angle) {
	rotateBot(angle*10);
}

void rotateRight (int angle) {
	rotateBot(-angle*10);
}

task main()
{
	gyroinit();
	//rotateLeft(90);
	//rotateLeft(180);
	//rotateRight(90);
	//rotateRight(180);
	rotateLeft(90);
}
