#pragma once

#include "Singleton.h"

#include "Resources.h"

class Audio : public Singleton<Audio>
{
	friend class Singleton<Audio>;
private:
	int m_MusicChannel;
	int m_MusicVolume;
public:
	Audio();
	~Audio();

	int PlayAudio(uint32 audioClip, int volume, int loopTimes = 0);

	void PlayMusic(uint32 audioClip);

	void StopMusic();
};