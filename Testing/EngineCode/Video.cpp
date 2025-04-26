#include "Video.h"

#include <iostream>

#include "../SDL/include/SDL.h"
#include "../SDL/SDLImage/include/SDL_image.h"

#include "Defines.h"
#include "ResourceManager.h"


Video* Video::_pInstance = nullptr;

Video::Video(void)
{
	_mIsInitialized = false;
	_mWindow = nullptr;
	_mScreenRenderer = nullptr;
}

Video::~Video(void)
{
	CloseWindow();
}

void Video::RenderTexture(int _id, SDL_Rect _rect, SDL_Rect _rectAux)
{
	SDL_Texture* originTexture = RESOURCE_MANAGER->GetTextureByID(_id);

	int renderCopy = SDL_RenderCopy(_mScreenRenderer, originTexture, &_rect, &_rectAux);
	if (renderCopy)
	{
		std::cout << "Texture could not be copied to GPU! [SDL Error]: "
			<< SDL_GetError() << std::endl;
	}
}

void Video::DestroyTexture(SDL_Texture* _texture)
{
	SDL_DestroyTexture(_texture);
}

void Video::ClearScreen()
{
	SDL_RenderClear(_mScreenRenderer);
}

void Video::UpdateScreen()
{
	SDL_RenderPresent(_mScreenRenderer);
}

void Video::CloseWindow()
{
	SDL_DestroyRenderer(_mScreenRenderer);
	SDL_DestroyWindow(_mWindow);
	IMG_Quit();
	SDL_Quit();
}

void Video::InitVideo()
{
	if (!_mIsInitialized)
	{
		int error = SDL_Init(SDL_INIT_VIDEO);
		if (error != 0)
		{
			std::cout << "SDL could not be initialized! [SDL Error]: "
				<< SDL_GetError() << std::endl;
		}
		else
		{
			_mWindow = SDL_CreateWindow("SDL Game",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
			if (!_mWindow)
			{
				std::cout << "Window could not be generated! [SDL Error]: "
					<< SDL_GetError() << std::endl;
			}
			else
			{
				_mScreenRenderer = SDL_CreateRenderer(_mWindow, -1,
					SDL_RENDERER_ACCELERATED);
				if (!_mScreenRenderer)
				{
					std::cout << "Screen renderer could not be generated! [SDL Error]: "
						<< SDL_GetError() << std::endl;
				}
				else
				{
					int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						std::cout << "SDL_Image could not be initialized! [SDL Error]: "
							<< IMG_GetError() << std::endl;
					}
					else
					{
						_mIsInitialized = true;
					}
				}
			}
		}
	}
}

Video* Video::GetInstance()
{
	if (Video::_pInstance == nullptr)
	{
		Video::_pInstance = new Video();
	}

	return Video::_pInstance;
}
