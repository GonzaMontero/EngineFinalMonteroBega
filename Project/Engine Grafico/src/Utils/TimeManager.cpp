#include "TimeManager.h"

using namespace Engine;

Engine::Time::Time()
{
	_previousDeltaTime = 0;
}

Engine::Time::~Time()
{

}

float Engine::Time::GetDeltaTime()
{
	return _deltaTime;
}

void Engine::Time::UpdateDeltaTime(float currentTime)
{
	_deltaTime = currentTime - _previousDeltaTime;
	_previousDeltaTime = currentTime;
}
