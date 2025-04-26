#include "Audio.h"

#include <iostream>
#include <string>

#include "../SDL/include/SDL.h"
#include "../SDL/SDLMixer/include/SDL_mixer.h"

#include "Defines.h"
#include "ResourceManager.h"


Audio* Audio::_pInstance = nullptr;

Audio::Audio(void)
{
	_mIsInitialized = false;
}

Audio::~Audio(void)
{
	CloseMixer();
}

Mix_Chunk* Audio::LoadSound(const char* _file)
{
	Mix_Chunk* sound = Mix_LoadWAV(_file);
	if (!sound)
	{
		std::cout << "Sound could not be loaded! [SDL Error]: "
			<< Mix_GetError() << std::endl;

		return nullptr;
	}
	return sound;
}

void Audio::PlaySound(int _id, int _loops)
{
	Mix_Chunk* sound = RESOURCE_MANAGER->GetSoundByID(_id);

	Mix_PlayChannel(-1, sound, _loops);
}

void Audio::StopSound(int _channel)
{
	Mix_HaltChannel(_channel);
}

void Audio::SetVolumeSound(int _id, int _volume)
{
	if (_id > 0 && _id < RESOURCE_MANAGER->GetSoundsVector().size())
	{
		Mix_VolumeChunk(RESOURCE_MANAGER->GetSoundsVector()[_id], _volume);
	}
}

void Audio::FreeSound(int _id)
{
	if (_id > 0 && _id < RESOURCE_MANAGER->GetSoundsVector().size())
	{
		Mix_FreeChunk(RESOURCE_MANAGER->GetSoundsVector()[_id]);
		RESOURCE_MANAGER->GetSoundsVector()[_id] = nullptr;
	}
}

void Audio::FreeAllSounds()
{
	for (Mix_Chunk* sound : RESOURCE_MANAGER->GetSoundsVector())
	{
		if (sound)
		{
			Mix_FreeChunk(sound);
		}
	}
	RESOURCE_MANAGER->GetSoundsVector().clear();
}

void Audio::InitMixer()
{
	if (!_mIsInitialized)
	{
		int error = SDL_InitSubSystem(SDL_INIT_AUDIO);

		if (error != 0)
		{
			std::cout << "Mixer could not be initialized! [SDL Error]: "
				<< Mix_GetError() << std::endl;
		}
		else
		{
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
			Mix_AllocateChannels(128);

			_mIsInitialized = true;
		}
	}
}

void Audio::CloseMixer()
{
	Mix_CloseAudio();
}

Audio* Audio::GetInstance()
{
	if (Audio::_pInstance == nullptr)
	{
		Audio::_pInstance = new Audio();
	}

	return Audio::_pInstance;
}
