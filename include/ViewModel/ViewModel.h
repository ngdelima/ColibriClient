#ifndef VIEW_MODEL_H
#define VIEW_MODEL_H

#include"Model/Drone.h"

class ViewModel
{
public:

	virtual void update() = 0;

protected:

};

class DroneViewModel : public ViewModel
{
public:

	DroneViewModel()
	: mDrone(nullptr)
	, mNorthEastMotorSpeed(0)
	, mNorthWestMotorSpeed(0)
	, mSouthEastMotorSpeed(0)
	, mSouthWestMotorSpeed(0)
	, mIsRunning(false)
	{}

	void setDrone(Drone* drone) { mDrone = drone; }
	void setIsRunning(bool isRunning) { mIsRunning = isRunning; }
	inline bool getIsRunning() {return mIsRunning; }

	void update() override
	{
		if(mDrone != nullptr)
		{
			mNorthEastMotorSpeed = mDrone->getMotorSpeed(MOTOR_ID::NORTH_EAST_MOTOR);
			mNorthWestMotorSpeed = mDrone->getMotorSpeed(MOTOR_ID::NORTH_WEST_MOTOR);
			mSouthEastMotorSpeed = mDrone->getMotorSpeed(MOTOR_ID::SOUTH_EAST_MOTOR);
			mSouthWestMotorSpeed = mDrone->getMotorSpeed(MOTOR_ID::SOUTH_WEST_MOTOR);
		}
	}

	int mNorthEastMotorSpeed;
	int mNorthWestMotorSpeed;
	int mSouthEastMotorSpeed;
	int mSouthWestMotorSpeed;

private:

	Drone* mDrone;
	bool mIsRunning;
};

#endif