#include "TimeManager.h"

#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "../SDL/include/SDL.h"


TimeManager* TimeManager::_pInstance = nullptr;

TimeManager::TimeManager(unsigned int fps = 60)
{
    SetFPS(fps);
    _mLastTime = SDL_GetTicks();
    _mCurrentTime = 0;
    _mDeltaTime = 0;
	_mTimerMap.clear();
}

TimeManager::~TimeManager()
{

}

void TimeManager::RandomTime()
{
	srand((int)time(NULL));
}

void TimeManager::SetFPS(unsigned int _fps)
{
	_mFPS = _fps;
	_mMsFrame = 1000.0f / _mFPS;
}

void TimeManager::UpdateTime()
{
	_mCurrentTime = SDL_GetTicks();
	_mDeltaTime = _mCurrentTime - _mLastTime;
	if (_mDeltaTime < (int)_mMsFrame)
	{
		SDL_Delay((int)_mMsFrame - _mDeltaTime);
	}
	_mLastTime = _mCurrentTime;
}

void TimeManager::StartNewTimer(const std::string _name, unsigned int _duration)
{
	_mCurrentTime = SDL_GetTicks();
	_mTimerMap[_name] = _mCurrentTime + _duration;
}

bool TimeManager::HasTimerExpired(const std::string _name)
{
	std::map<std::string, unsigned int>::iterator it;
	it = _mTimerMap.find(_name);
	if (it != _mTimerMap.end())
	{
		_mCurrentTime = SDL_GetTicks();
		if (_mCurrentTime >= it->second)
		{
			StopTimer(_name);
			return true;
		}
	}
	return false;
}

void TimeManager::StopTimer(const std::string _name)
{
	_mTimerMap.erase(_name);
}

void TimeManager::PrintActiveTimers()
{
	_mCurrentTime = SDL_GetTicks();
	for (std::map<std::string, unsigned int>::iterator it = _mTimerMap.begin(); it != _mTimerMap.end(); ++it)
	{
		std::cout << "[Timer " << it->first << "]	: " << (it->second - _mCurrentTime) << " ms\n";
	}
}

TimeManager* TimeManager::GetInstance()
{
	if (TimeManager::_pInstance == nullptr)
	{
		TimeManager::_pInstance = new TimeManager(60);
	}

	return TimeManager::_pInstance;
}
