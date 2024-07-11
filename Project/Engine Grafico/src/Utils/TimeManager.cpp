#include "TimeManager.h"

using namespace Engine;

namespace Engine{
	Time::Time()
	{
		_previousDeltaTime = 0;
	}

	Time::~Time()
	{

	}

	float Time::_deltaTime = 0.0f;

	float Time::GetDeltaTime()
	{
		return _deltaTime;
	}

	void Time::UpdateDeltaTime(float currentTime)
	{
		_deltaTime = currentTime - _previousDeltaTime;
		_previousDeltaTime = currentTime;
	}
}

