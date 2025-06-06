#include "SceneGame.h"

#include <iostream>
#include <string>

#include "../EngineCode/Defines.h"
#include "../EngineCode/ResourceManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Audio.h"
#include "../EngineCode/Input.h"
#include "../EngineCode/SceneManager.h"

#include "Map.h"
#include "Tileset.h"
#include "Camera.h"
#include "Player.h"
#include "Bomb.h"
#include "Rock.h"


SceneGame::SceneGame(void)
{
	_mCurrentLevel = 1;
	
	_mIdsTexturesVector.resize(0);
	_mIdsSoundsVector.resize(0);
	_mAllTexturesLoaded = false;
	_mAllSoundsLoaded = false;

	_pMap = new Map();
	_pTileset = new Tileset();
	_pCamera = new Camera();
	_pPlayer = new Player();
	_pBomb = new Bomb();
	_pRock = new Rock();
}

SceneGame::~SceneGame(void)
{

}

void SceneGame::Init()
{
	while (!_mAllTexturesLoaded)
	{
		// condici�n para tener en cuenta qu� nivel del mundo seleccionado
		//Textures:
		_pTileset->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/PlanetQuarry.png"));
		_pPlayer->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/Player.png"));
		if (_mCurrentLevel == 1)
		{
			_pBomb->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/Bomb1.png"));
			_pRock->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/Rock1.png"));
		}

		//Check:
		_mAllTexturesLoaded = true;
	}
	while (!_mAllSoundsLoaded)
	{
		//Sounds:
		int idSounds[6];
		idSounds[0] = RESOURCE_MANAGER->LoadAndGetSoundID("Assets/Sounds/QuarryPlanet.mp3");
		_mIdsSoundsVector.push_back(idSounds[0]);

		//Check:
		_mAllSoundsLoaded = true;
	}

	_pCamera->Init();
	std::string filePath("Assets/Levels/World" + std::to_string(1) + "/a" + std::to_string(1) + ".tmx");
	_pMap->Init(_pTileset, filePath.c_str());
	_pPlayer->Init();
	_pPlayer->SetWorldPointer(_pMap);

	Scene::Init();
}

void SceneGame::Update()
{
	AUDIO->PlaySound(_mIdsSoundsVector[0], -1);

	for (auto bomb : _pPlayer->GetBombs()) {
		bomb->Update();
	}
	for (auto rock : _pMap->GetRocks()) {
		rock->Update(_pMap);
	}
	_pMap->Update();
	_pPlayer->Update(_pMap);
	_pCamera->Update(_pMap, _pPlayer);
}

void SceneGame::Render()
{
	_pMap->Render(_pCamera, _pTileset->GetTextureId());
	for (auto bomb : _pPlayer->GetBombs()) {
		bomb->Render(8, _pCamera);
	}
	for (auto rock : _pMap->GetRocks()) {
		rock->Render(9, _pCamera);
	}
	_pPlayer->Render(_pPlayer->GetTextureId(), _pCamera);
	RESOURCE_MANAGER->GetTexturesVector();
}

void SceneGame::UnloadResources()
{
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/PlanetQuarry.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/Player.png");
	if (_mCurrentLevel == 1)
	{
		RESOURCE_MANAGER->RemoveTexture("Assets/Textures/Bomb1.png");
		RESOURCE_MANAGER->RemoveTexture("Assets/Textures/Rock1.png");
	}
	RESOURCE_MANAGER->RemoveSound("Assets/Sounds/QuarryPlanet.mp3");
}
