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


SceneGame::SceneGame(void)
{
	_mAllTexturesLoaded = false;

	_pMap = new Map();
	_pTileset = new Tileset();
	_pCamera = new Camera();
	_pPlayer = new Player();
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
	_pPlayer->Update();
	_pCamera->Update(_pMap, _pPlayer);
}

void SceneGame::Render()
{
	_pMap->Render(_pCamera, _pTileset->GetTextureId());
	_pPlayer->Render(_pPlayer->GetTextureId(), _pCamera);
}

void SceneGame::UnloadResources()
{
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/PlanetQuarry.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/Player.png");
}
