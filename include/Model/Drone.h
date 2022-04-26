#ifndef DRONE_H
#define DRONE_H

#include"Controller/CommandDispatcher.h"

#define MOTOR_1 0x0
#define MOTOR_2 0x1
#define MOTOR_3 0x2
#define MOTOR_4 0x3

class Motor
{
public:
	Motor(int _speed);

	void addSpeed(int _speed);
	void setSpeed(int _speed);
	int getSpeed();

private:

	uint8_t mSpeed;

	void clampSpeed();
};

class Drone
{
public:

	Drone(CommandDispatcher* _commandDispatcher);

	Motor* getMotor1();
	Motor* getMotor2();
	Motor* getMotor3();
	Motor* getMotor4();

	void onNotify();

private:

	Motor mMotor1;
	Motor mMotor2;
	Motor mMotor3;
	Motor mMotor4;

	CommandDispatcher* mCommandDispatcher;

};

#endif