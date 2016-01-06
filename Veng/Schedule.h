#pragma once

#include <vector>


namespace veng{
class Schedule
{
public:
	Schedule();
	~Schedule();

	void init(int timeSpan);

	bool ready();

private:
	int _timeSpan;
	int _startTime;
};

}