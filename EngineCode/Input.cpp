#include "Input.h"

#include <iostream>

#include "Defines.h"
#include "TimeManager.h"
#include "SceneManager.h"


Input* Input::_pInstance = nullptr;

Input::Input(void)
{
	_mIsInitialized = false;
	_mKeysStates = {};
	_mGameController = nullptr;
}

Input::~Input(void)
{

}

void Input::ResetKeys()
{
	for (size_t i = 0; i < SDL_NUM_SCANCODES; i++)
	{
		_mKeysStates[i] = OFF;
	}
}

void Input::SetPressedKeys(int _keyState)
{
	_mKeysStates[_keyState] = Pressed;
}

bool Input::GetPressedKeys(int _keyState)
{
	return _mKeysStates[_keyState] == Pressed;
}

void Input::SetReleasedKeys(int _keyState)
{
	_mKeysStates[_keyState] = Released;
}

bool Input::GetHoldKeys(int _keyState)
{
	return _mKeysStates[_keyState] == Hold;
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
			this->_mKeysStates = new EKeyState[SDL_NUM_SCANCODES];
			this->ResetKeys();

			_mIsInitialized = true;
		}
	}
}

void Input::UpdateInput()
{
	if (SCENE_MANAGER->GetCurrentSceneEnum() == MAIN)
	{
		for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			if (_mKeysStates[i] == Released)
			{
				_mKeysStates[i] = OFF;
			}
			if (_mKeysStates[i] == Pressed)
			{
				_mKeysStates[i] = Hold;
			}
		}
	}
	else if (SCENE_MANAGER->GetCurrentSceneEnum() == GAME)
	{
		for (int i = 0; i < SDL_NUM_SCANCODES; i++)
		{
			if (_mKeysStates[i] == Released)
			{
				_mKeysStates[i] = OFF;
			}
		}
	}

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
