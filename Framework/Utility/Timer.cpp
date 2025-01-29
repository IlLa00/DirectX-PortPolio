#include "framework.h"
#include "Timer.h"

Timer::Timer()
	: frame_rate(0), frame_count(0), time_elapsed(0), one_sec_count(0), run_time(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&period_frequency);
	

	QueryPerformanceCounter((LARGE_INTEGER*)&last_time);
	

	time_scale = 1.0f / (float)period_frequency;


}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&cur_time);


	time_elapsed = (float)(cur_time - last_time) * time_scale;


	last_time = cur_time;

	frame_count++;
	

	one_sec_count += time_elapsed;
	

	if (one_sec_count >= 1.0f) 
	{
		frame_rate = frame_count;
		one_sec_count = frame_count = 0;
		
	}

	run_time += time_elapsed;
}
