#include "ResourceManager.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../SDL/include/SDL.h"
#include "../SDL/SDLImage/include/SDL_image.h"
#include "../SDL/SDLMixer/include/SDL_mixer.h"

#include "Defines.h"
#include "Video.h"
#include "Audio.h"


ResourceManager* ResourceManager::_pInstance = nullptr;

ResourceManager::ResourceManager(void)
{
	_mTexturesVector = {};
	_mSoundsVector = {};
	_mIDTextureMap.clear();
	_mIDSoundMap.clear();
	_mFirstFreeSlotTexture = 0;
	_mFirstFreeSlotSound = 0;
}

ResourceManager::~ResourceManager(void)
{

}

Sint32 ResourceManager::LoadAndGetTextureID(const char* _file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _mIDTextureMap.find(_file);
	if (it == _mIDTextureMap.end())
	{
		int numberTexture = AddTexture(_file);
		if (numberTexture != -1)
		{
			_mIDTextureMap.insert(std::pair<std::string, Sint32>(_file, numberTexture));

			return numberTexture;
		}
		else
		{
			std::cout << "Texture could not be loaded! [SDL Error]: "
				<< SDL_GetError() << std::endl;

			return -1;
		}
	}
	else
	{
		std::cout << "Texture could not be found! [SDL Error]: "
			<< SDL_GetError() << std::endl;

		return -1;
	}
	return it->second;
}

SDL_Texture* ResourceManager::GetTextureByID(Sint32 _id)
{
	if ((_id > -1) && (_id < _mTexturesVector.size()))
	{
		return _mTexturesVector[_id];
	}

	std::cout << "Texture could not be reached! [SDL Error]: "
		<< SDL_GetError() << std::endl;

	return nullptr;
}

std::string ResourceManager::GetTexturePathByID(Sint32 _id)
{
	for (auto it = _mIDTextureMap.begin(); it != _mIDTextureMap.end(); ++it)
	{
		if (it->second == _id)
		{
			return it->first;
		}
	}

	std::cout << "Texture path could not be found! [SDL Error]: "
		<< SDL_GetError() << std::endl;

	return "";
}

Sint32 ResourceManager::AddTexture(const char* _file)
{
	SDL_Surface* image = IMG_Load(_file);
	if (!image)
	{
		std::cout << "Image path could not be found! [SDL Error]: "
			<< SDL_GetError() << std::endl;

		return -1;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(VIDEO->GetScreenRenderer(), image);
	if (!texture)
	{
		return -1;
	}

	for (size_t i = 0; i < _mTexturesVector.size(); i++)
	{
		if (_mTexturesVector[i] == texture)
		{
			VIDEO->DestroyTexture(texture);
			return i;
		}
	}

	_mTexturesVector.push_back(texture);

	SDL_FreeSurface(image);

	return _mTexturesVector.size() - 1;
}

void ResourceManager::RemoveTexture(const char* _file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _mIDTextureMap.find(_file);
	if (it != _mIDTextureMap.end())
	{
		VIDEO->DestroyTexture(_mTexturesVector[it->second]);
		_mTexturesVector[it->second] = nullptr;
		_mIDTextureMap.erase(it);
	}
}

void ResourceManager::GetTextureSize(Sint32 _img, int& _width, int& _height)
{
	if ((_img > -1) && (_img < _mTexturesVector.size()))
	{
		SDL_QueryTexture(_mTexturesVector[_img], NULL, NULL, &_width, &_height);
	}
	else
	{
		std::cout << "Texture size could not be reached! [SDL Error]: "
			<< SDL_GetError() << std::endl;
	}
}

Uint16 ResourceManager::GetTextureWidth(Sint32 _img)
{
	int width;
	int height;
	GetTextureSize(_img, width, height);
	return width;
}

Uint16 ResourceManager::GetTextureHeight(Sint32 _img)
{
	int width;
	int height;
	GetTextureSize(_img, width, height);
	return height;
}

Sint32 ResourceManager::LoadAndGetSoundID(const char* _file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _mIDSoundMap.find(_file);
	if (it == _mIDTextureMap.end())
	{
		int numberSound = AddSound(_file);
		if (numberSound != -1)
		{
			_mIDSoundMap.insert(std::pair<std::string, Sint32>(_file, numberSound));

			return numberSound;
		}
		else
		{
			std::cout << "Sound could not be loaded! [SDL Error]: "
				<< SDL_GetError() << std::endl;

			return -1;
		}
	}
	else
	{
		std::cout << "Sound could not be found! [SDL Error]: "
			<< SDL_GetError() << std::endl;

		return -1;
	}
	return it->second;
}

Mix_Chunk* ResourceManager::GetSoundByID(Sint32 _id)
{
	if ((_id > -1) && (_id < _mSoundsVector.size()))
	{
		return _mSoundsVector[_id];
	}
	else
	{
		std::cout << "Sound could not be reached! [SDL Error]: "
			<< SDL_GetError() << std::endl;

		return nullptr;
	}
}

std::string ResourceManager::GetSoundPathByID(Sint32 _id)
{
	for (auto it = _mIDSoundMap.begin(); it != _mIDSoundMap.end(); ++it)
	{
		if (it->second == _id)
		{
			return it->first;
		}
	}

	std::cout << "Sound path could not be found! SDL Error! [SDL Error]: "
		<< SDL_GetError() << std::endl;

	return "";
}

Sint32 ResourceManager::AddSound(const char* _file)
{
	Mix_Chunk* sound = AUDIO->LoadSound(_file);

	for (size_t i = 0; i < _mSoundsVector.size(); i++)
	{
		if (_mSoundsVector.at(i) == sound)
		{
			AUDIO->FreeSound(i);
			return i;
		}
	}

	_mSoundsVector.push_back(sound);

	return _mSoundsVector.size() - 1;
}

void ResourceManager::RemoveSound(const char* _file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _mIDSoundMap.find(_file);
	if (it != _mIDSoundMap.end())
	{
		AUDIO->FreeSound(it->second);
		_mSoundsVector.at(it->second) = nullptr;
		_mIDSoundMap.erase(it);
	}
}

Uint32 ResourceManager::UpdateFirstFreeSlotTexture()
{
	for (size_t i = 0; i < _mTexturesVector.size(); i++)
	{
		if (_mTexturesVector.at(i) == nullptr)
		{
			_mFirstFreeSlotTexture = i;
			break;
		}
	}

	if (_mFirstFreeSlotTexture == NULL)
	{
		_mFirstFreeSlotTexture = _mTexturesVector.size();
	}

	return _mFirstFreeSlotTexture;
}

Uint32 ResourceManager::UpdateFirstFreeSlotSound()
{
	for (size_t i = 0; i < _mSoundsVector.size(); i++)
	{
		if (_mSoundsVector.at(i) == nullptr)
		{
			_mFirstFreeSlotSound = i;
			break;
		}
	}

	if (_mFirstFreeSlotSound == NULL)
	{
		_mFirstFreeSlotSound = _mSoundsVector.size();
	}

	return _mFirstFreeSlotSound;
}

ResourceManager* ResourceManager::GetInstance()
{
	if (ResourceManager::_pInstance == nullptr)
	{
		ResourceManager::_pInstance = new ResourceManager();
	}

	return ResourceManager::_pInstance;
}
