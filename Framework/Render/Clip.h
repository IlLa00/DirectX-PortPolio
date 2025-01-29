#pragma once

class Clip
{
public:
	enum class CLIP_TYPE
	{
		END, LOOP, PINGPONG
	};

private:
	vector<Frame*> frames; 
	CLIP_TYPE repeat_type;
	bool is_play;
	bool is_end;

	UINT cur_frame_num;
	float time; 
	float fps;

	bool is_reverse; 

public:
	Clip(vector<Frame*> frames, CLIP_TYPE t = CLIP_TYPE::LOOP, float fps = 1.0f / 8.0f);
	~Clip();

	bool isPlay() { return is_play; }
	bool isEnd() { return is_end; }
	Vector2 GetFrameSize() { return frames[cur_frame_num]->GetFrameSize(); }
	Vector2 GetFrameOrigSize() { return frames[cur_frame_num]->GetFrameOrigSize(); }
	
	void Update();
	void Render();
	void Play(UINT type = 0);
	void Pause();
	void Stop();

};