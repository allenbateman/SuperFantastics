#include "../headers/Audio.h"
#include "sdl.h"
#include "sdl_mixer.h"

Audio* Audio::pInstance = NULL;

Audio::Audio()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(8);

	mMusicChannel = -1;

	mMusicVolume = 6;
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

	mMusicChannel = Mix_PlayChannel(-1, clip, -1);
	Mix_Volume(mMusicChannel, mMusicVolume);
}

void Audio::StopMusic()
{
	Mix_HaltChannel(mMusicChannel);
}

Audio * Audio::getInstance()
{
	if (pInstance == NULL)
		pInstance = new Audio();

	return pInstance;
}
