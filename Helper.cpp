#include "Helper.h"

Helper::Helper()
{
	_time = 0;
	_time_max = _time;
}

Helper::~Helper()
{
}

void Helper::setTime(float time)
{
	_time = time;
	_time_max = _time;
}

float Helper::getTime()
{
	return _time;
}

bool Helper::isReady()
{
	if (_time >= _time_max)
	{
		_time = 0.f;
		return true;
	}

	return false;
}

void Helper::updateClock()
{
	if (_time < _time_max)
		_time += 0.5f;
}
