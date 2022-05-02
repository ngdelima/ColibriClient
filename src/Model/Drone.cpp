#include"Model/Drone.h"
#include<iostream>

Motor::Motor(int _speed) : mSpeed(_speed) {}

void Motor::addSpeed(int _speed) 
{
	if( (mSpeed + _speed) < 0)
		mSpeed = 0;
	else
		mSpeed += _speed;
	clampSpeed();
}

void Motor::setSpeed(int _speed) 
{
	mSpeed = _speed;
	clampSpeed();
}

int Motor::getSpeed() { return mSpeed; }

void Motor::clampSpeed()
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

Drone::Drone()
: mCommandDispatcher(nullptr)
, mMotor1(0)
, mMotor2(0)
, mMotor3(0)
, mMotor4(0)
{
	std::cout << "Drone: Drone instance created" << '\n';
}

Drone::Drone(CommandDispatcher* _commandDispatcher)
: mCommandDispatcher(_commandDispatcher)
, mMotor1(0)
, mMotor2(0)
, mMotor3(0)
, mMotor4(0)
{}

Motor* Drone::getMotor1() { return &mMotor1; }
Motor* Drone::getMotor2() { return &mMotor2; }
Motor* Drone::getMotor3() { return &mMotor3; }
Motor* Drone::getMotor4() { return &mMotor4; }

/*void Drone::onNotify(INPUT_EVENT _event)
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
}*/