#include "SceneGame.h"

#include <iostream>
#include <string>

#include "../EngineCode/Defines.h"
#include "../EngineCode/ResourceManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Input.h"
#include "../EngineCode/SceneManager.h"

#include "Map.h"
#include "Tileset.h"
#include "Camera.h"
#include "Player.h"
#include "Bomb.h"


SceneGame::SceneGame(void)
{
	_mCurrentLevel = 1;
	
	_mAllTexturesLoaded = false;

	_pMap = new Map();
	_pTileset = new Tileset();
	_pCamera = new Camera();
	_pPlayer = new Player();
	_pBomb = new Bomb();
}

SceneGame::~SceneGame(void)
{

}

void SceneGame::Init()
{
	while (!_mAllTexturesLoaded)
	{
		// condición para tener en cuenta qué nivel del mundo seleccionado
		//Textures:
		_pTileset->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/PlanetQuarry.png"));
		_pPlayer->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/Player.png"));
		if (_mCurrentLevel == 1)
		{
			_pBomb->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/Bomb1.png"));
		}

		//Check:
		_mAllTexturesLoaded = true;
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
	for (auto bomb : _pPlayer->GetBombs()) {
		bomb->Update();
	}
	_pPlayer->Update(_pMap);
	_pCamera->Update(_pMap, _pPlayer);
}

void SceneGame::Render()
{
	_pMap->Render(_pCamera, _pTileset->GetTextureId());
	for (auto bomb : _pPlayer->GetBombs()) {
		bomb->Render(8, _pCamera);
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
	}
}
