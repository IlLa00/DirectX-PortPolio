#pragma once

class Sound
{
private:
	static FMOD_SYSTEM* g_System;
	FMOD_SOUND* sound;
	FMOD_CHANNEL* channel;

	float volume;
	FMOD_BOOL m_bool;

	bool is_playing;

public:
	Sound(const char* file, bool loop);
	~Sound();

	static UINT Init();
	static UINT Release();

	//void SetVolume();
	void Play();
	void Stop();
	void Update();
};