#include "../headers/Audio.h"
#include "sdl.h"
#include "SDL_mixer.h"

Audio* Audio::pInstance = NULL;

Audio::Audio()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(8);

	m_MusicChannel = -1;

	m_MusicVolume = 6;
}

Audio::~Audio()
{
}

int Audio::PlayAudio(Uint32 audioClip, int volume, int loopTimes)
{
	Mix_Chunk* clip = NULL;//= Resources::getInstance()->GetResourceById<Mix_Chunk>(audioClip);

	int channel = -1;

	if (clip) {
		channel = Mix_PlayChannel(-1, clip, loopTimes);
		Mix_Volume(channel, volume);
	}

	return channel;
}

void Audio::PlayMusic(Uint32 audioClip)
{
	Mix_Chunk* clip = NULL;//= Resources::getInstance()->GetResourceById<Mix_Chunk>(audioClip);

	m_MusicChannel = Mix_PlayChannel(-1, clip, -1);
	Mix_Volume(m_MusicChannel, m_MusicVolume);
}

void Audio::StopMusic()
{
	Mix_HaltChannel(m_MusicChannel);
}