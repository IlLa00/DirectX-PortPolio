#include "framework.h"
#include "Clip.h"

Clip::Clip(vector<Frame*> frames, CLIP_TYPE t, float fps)
	: frames(frames), repeat_type(t), fps(fps),
	cur_frame_num(0), is_play(true), is_reverse(false), time(0.0f)
{
}

Clip::~Clip()
{
	for (auto frame : frames)
		delete frame;
}

void Clip::Update()
{
	if (!is_play) return;
	
	time += DELTA;
	
	if (time <= fps) return; 

	switch (repeat_type) 
	{
	case Clip::CLIP_TYPE::END: 
		cur_frame_num++;
		if (cur_frame_num >= frames.size()) 
		{
			cur_frame_num--; 
			Stop();
		}
		break;
	case Clip::CLIP_TYPE::LOOP: 
		++cur_frame_num %= frames.size();
		break;
	case Clip::CLIP_TYPE::PINGPONG: 
		if (is_reverse) 
		{
			cur_frame_num--;
			if (cur_frame_num <= 0) 
				is_reverse = true; 	
		}
		else 
		{
			cur_frame_num++;
			if (cur_frame_num >= frames.size() - 1) 
				is_reverse = false; 
		}
		break;
	default:
		break;
	}

	time -= fps;
}

void Clip::Render()
{
	if(is_play)
		frames[cur_frame_num]->Render();
}

void Clip::Play(UINT type) 
{
	is_play = true;
	is_reverse = false;
	is_end = false;
	
	switch (type)
	{
	case 0: 
		time = 0.0f;
		cur_frame_num = 0;
		break;
	default:
		break;
	}
}

void Clip::Pause() 
{
}

void Clip::Stop()
{
	is_play = false;
	is_end = true;
}
