#pragma once
class Timer : public Singleton<Timer>
{
private:
	Timer();
	~Timer();

public:
	friend class Singleton;
	
	float time_scale; 
	float time_elapsed; 
	__int64 cur_time; 
	__int64 last_time;  
	__int64 period_frequency;
	

	int frame_rate; 
	int frame_count; 

	float one_sec_count;
	float run_time; 


	void Update();

	int GetFPS() { return frame_rate; }
	float GetDeltaTime() { return time_elapsed; } 
	float GetRunTime() { return run_time; } 
};