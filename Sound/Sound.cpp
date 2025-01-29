#include "framework.h"

FMOD_SYSTEM* Sound::g_System;

Sound::Sound(const char* file, bool loop)
{
	if (loop)
		FMOD_System_CreateSound(g_System,file, FMOD_LOOP_NORMAL,NULL,&sound);
	else
		FMOD_System_CreateSound(g_System, file, FMOD_DEFAULT, NULL, &sound);

	channel = nullptr;
	volume = 0.5f;
}

Sound::~Sound()
{
	FMOD_Sound_Release(sound);
}

UINT Sound::Init()
{
	FMOD_System_Create(&g_System,FMOD_VERSION);
	FMOD_System_Init(g_System, 32, FMOD_INIT_NORMAL, NULL);

	return 0;
}

UINT Sound::Release()
{
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);

	return 0;
}

void Sound::Play()
{
	is_playing = true;
	FMOD_System_PlaySound(g_System, sound, NULL, false, &channel);
}

void Sound::Stop()
{
	is_playing = false;
	FMOD_Channel_Stop(channel);
}

void Sound::Update()
{
	FMOD_Channel_SetVolume(channel, volume);
	FMOD_Channel_IsPlaying(channel, &m_bool);

	if (m_bool)
		FMOD_System_Update(g_System);
}
