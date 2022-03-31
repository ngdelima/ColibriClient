#pragma once

#include"Listener.h"
#include"CommandDispatcher.h"

#define MOTOR_1 0x0
#define MOTOR_2 0x1
#define MOTOR_3 0x2
#define MOTOR_4 0x3

class Motor
{
public:
	Motor(int _speed) : mSpeed(_speed) {}

	void addSpeed(int _speed) 
	{ 
		mSpeed += _speed;
		clampSpeed();
	}

	void setSpeed(int _speed) 
	{
		mSpeed = _speed;
		clampSpeed();
	}

	int getSpeed() { return mSpeed; }

private:

	uint8_t mSpeed;

	void clampSpeed()
	{
		if (mSpeed > 100)
		{
			mSpeed = 100;
		}
		else if (mSpeed < 0)
		{
			mSpeed = 0;
		}
	}
};

class Drone : public Listener
{
public:

	Drone(CommandDispatcher* _commandDispatcher)
	: mCommandDispatcher(_commandDispatcher)
	, mMotor1(0)
	, mMotor2(0)
	, mMotor3(0)
	, mMotor4(0)
	{}

	Motor* getMotor1() { return &mMotor1; }
	Motor* getMotor2() { return &mMotor2; }
	Motor* getMotor3() { return &mMotor3; }
	Motor* getMotor4() { return &mMotor4; }

	void onNotify(INPUT_EVENT _event)
	{
		switch (_event)
		{
			case INPUT_EVENT::INPUT_EVENT_LEFT_STICK_UP:
			{
				mMotor1.addSpeed(5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_1, mMotor1.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_LEFT_STICK_DOWN:
			{
				mMotor1.addSpeed(-5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_1, mMotor1.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_LEFT_STICK_RIGHT:
			{
				mMotor2.addSpeed(5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_2, mMotor2.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_LEFT_STICK_LEFT:
			{
				mMotor2.addSpeed(-5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_2, mMotor2.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_UP:
			{
				mMotor3.addSpeed(5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_3, mMotor3.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_DOWN:
			{
				mMotor3.addSpeed(-5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_3, mMotor3.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_RIGHT:
			{
				mMotor4.addSpeed(5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_4, mMotor4.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_RIGHT_STICK_LEFT:
			{
				mMotor4.addSpeed(-5);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_4, mMotor4.getSpeed());
				break;
			}
			case INPUT_EVENT::INPUT_EVENT_FULL_STOP:
			{
				mMotor1.setSpeed(0);
				mMotor2.setSpeed(0);
				mMotor3.setSpeed(0);
				mMotor4.setSpeed(0);
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_1, mMotor1.getSpeed());
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_2, mMotor2.getSpeed());
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_3, mMotor3.getSpeed());
				mCommandDispatcher->setMotorSpeedCommand(MOTOR_4, mMotor4.getSpeed());
				break;
			}
			default:
				break;
		}
	}

private:

	Motor mMotor1;
	Motor mMotor2;
	Motor mMotor3;
	Motor mMotor4;

	CommandDispatcher* mCommandDispatcher;

};