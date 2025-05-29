#include "SceneMain.h"

#include <iostream>

#include "../EngineCode/Defines.h"
#include "../EngineCode/ResourceManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Audio.h"
#include "../EngineCode/Input.h"
#include "../EngineCode/SceneManager.h"

extern int _gameOn;


SceneMain::SceneMain(void)
{
	_mIdsTexturesVector.resize(0);
	_mIdsSoundsVector.resize(0);
	_mAllTexturesLoaded = false;
	_mAllSoundsLoaded = false;
	_mArrowPosY = 0;
}

SceneMain::~SceneMain(void)
{

}

void SceneMain::Init()
{
	_mArrowPosY = SCREEN_H / 2;

	while (!_mAllTexturesLoaded)
	{
		//Textures:
		int idTextures[6];
		idTextures[0] = RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/UI/Title.png");
		_mIdsTexturesVector.push_back(idTextures[0]);
		idTextures[1] = RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/UI/Arrow.png");
		_mIdsTexturesVector.push_back(idTextures[1]);
		idTextures[2] = RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/UI/Play.png");
		_mIdsTexturesVector.push_back(idTextures[2]);
		idTextures[3] = RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/UI/Options.png");
		_mIdsTexturesVector.push_back(idTextures[3]);
		idTextures[4] = RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/UI/Highscore.png");
		_mIdsTexturesVector.push_back(idTextures[4]);
		idTextures[5] = RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/UI/Exit.png");
		_mIdsTexturesVector.push_back(idTextures[5]);

		//Check:
		_mAllTexturesLoaded = true;
	}
	while (!_mAllSoundsLoaded)
	{
		//Sounds:
		int idSounds[6];
		idSounds[0] = RESOURCE_MANAGER->LoadAndGetSoundID("Assets/Sounds/Title.mp3");
		_mIdsSoundsVector.push_back(idSounds[0]);

		//Check:
		_mAllSoundsLoaded = true;
	}

	Scene::Init();
}

void SceneMain::Update()
{
	AUDIO->PlaySound(_mIdsSoundsVector[0], -1);

	if (INPUT->GetPressedKeys(SDL_SCANCODE_UP))
	{
		if (_mArrowPosY != SCREEN_H / 2)
		{
			_mArrowPosY -= 80;
		}
	}
	if (INPUT->GetPressedKeys(SDL_SCANCODE_DOWN))
	{
		if (_mArrowPosY != SCREEN_H / 2 + 240)
		{
			_mArrowPosY += 80;
		}
	}
	if (INPUT->GetPressedKeys(SDL_SCANCODE_RETURN))
	{
		if (_mArrowPosY == SCREEN_H / 2)
		{
			SCENE_MANAGER->ChangeScene(GAME, false);
		}
		else if (_mArrowPosY == SCREEN_H / 2 + 240)
		{
			SCENE_MANAGER->SetGameState(false);
		}
	}
}

void SceneMain::Render()
{
	SDL_Rect rectScreen;
	SDL_Rect rectWorld;

	for (int i = 0; i < 6; i++)
	{
		rectScreen.x = 0;
		rectScreen.y = 0;
		rectScreen.w = RESOURCE_MANAGER->GetTextureWidth(_mIdsTexturesVector[i]);
		rectScreen.h = RESOURCE_MANAGER->GetTextureHeight(_mIdsTexturesVector[i]);

		if (i == 0)
		{
			rectWorld.x = SCREEN_W / 2 - rectScreen.w / 2;
			rectWorld.y = (SCREEN_H / 2 - rectScreen.h) - 100;
			rectWorld.w = rectScreen.w;
			rectWorld.h = rectScreen.h;
		}
		else if (i == 1)
		{
			rectWorld.x = 100;
			rectWorld.y = _mArrowPosY;
			rectWorld.w = rectScreen.w;
			rectWorld.h = rectScreen.h;
		}
		else if (i == 2)
		{
			rectWorld.x = 200;
			rectWorld.y = SCREEN_H / 2;
			rectWorld.w = rectScreen.w;
			rectWorld.h = rectScreen.h;
		}
		else if (i == 3)
		{
			rectWorld.x = 200;
			rectWorld.y = SCREEN_H / 2 + 80;
			rectWorld.w = rectScreen.w;
			rectWorld.h = rectScreen.h;
		}
		else if (i == 4)
		{
			rectWorld.x = 200;
			rectWorld.y = SCREEN_H / 2 + 160;
			rectWorld.w = rectScreen.w;
			rectWorld.h = rectScreen.h;
		}
		else if (i == 5)
		{
			rectWorld.x = 200;
			rectWorld.y = SCREEN_H / 2 + 240;
			rectWorld.w = rectScreen.w;
			rectWorld.h = rectScreen.h;
		}

		VIDEO->RenderTexture(_mIdsTexturesVector[i], rectScreen, rectWorld);
	}
}

void SceneMain::UnloadResources()
{
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/UI/Title.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/UI/Arrow.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/UI/Play.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/UI/Options.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/UI/Highscore.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/UI/Exit.png");
	RESOURCE_MANAGER->RemoveSound("Assets/Sounds/Title.mp3");
}
