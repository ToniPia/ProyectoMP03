#include "Input.h"

#include <iostream>


Input* Input::_pInstance = nullptr;

Input::Input(void)
{
	_mIsInitialized = false;
	_mPressedKeys = {};
	_mGameController = nullptr;
}

Input::~Input(void)
{

}

void Input::ResetKeys()
{
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		_mPressedKeys[i] = false;
	}
}

void Input::SetPressedKeys(int _key)
{
	_mPressedKeys[_key] = true;
}

void Input::SetReleasedKeys(int _key)
{
	_mPressedKeys[_key] = false;
}

bool Input::GetPressedKeys(int _key)
{
	return _mPressedKeys[_key];
}

SDL_GameController* Input::FindController()
{
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			return SDL_GameControllerOpen(i);
		}
	}
	return nullptr;
}

void Input::CloseController(SDL_GameController* _gameController)
{
	SDL_GameControllerClose(_gameController);
}

void Input::InitInput()
{
	if (!_mIsInitialized)
	{
		int error = SDL_Init(SDL_INIT_GAMECONTROLLER);

		if (error != 0)
		{
			std::cout << "SDL_GameController could not initialize! [SDL Error]: " << SDL_GetError() << std::endl;
		}
		else
		{
			this->_mPressedKeys = new bool[SDL_NUM_SCANCODES];
			this->ResetKeys();

			_mIsInitialized = true;
		}
	}
}

void Input::UpdateInput()
{
	SDL_Event testEvent;
	while (SDL_PollEvent(&testEvent))
	{
		switch (testEvent.type)
		{
		case SDL_KEYDOWN:
			SetPressedKeys(testEvent.key.keysym.scancode);
			break;

		case SDL_KEYUP:
			SetReleasedKeys(testEvent.key.keysym.scancode);
			break;
		default:
			break;
		}
	}
}

Input* Input::GetInstance()
{
	if (Input::_pInstance == nullptr)
	{
		Input::_pInstance = new Input();
	}

	return Input::_pInstance;
}
