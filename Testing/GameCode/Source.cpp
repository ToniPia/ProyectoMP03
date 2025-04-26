#include <iostream>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/ResourceManager.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Audio.h"
#include "../EngineCode/Input.h"

#include "Map.h"
#include "Tileset.h"
#include "Camera.h"
#include "Player.h"


int main(int argc, char* args[])
{
	//Randomize Time:
	TIME_MANAGER->RandomTime();

	//Variables:
	Sint32 textureBGD;
	Sint32 texturePlayer;
	
	bool allTexturesLoaded = false;
	
	//Variables - Game:
	Map* MAP = new Map();
	Tileset* TILESET = new Tileset();
	Camera* GAME_CAMERA = new Camera();
	Player* WHITE_BOMBERMAN = new Player();

	//Init - SDL:
	VIDEO->InitVideo();
	AUDIO->InitMixer();
	INPUT->InitInput();
	TIME_MANAGER->SetFPS(FPS);

	//Loading:
	{
		while (!allTexturesLoaded)
		{
			//Textures:
			TILESET->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/PlanetQuarry.png"));
			WHITE_BOMBERMAN->SetTextureId(RESOURCE_MANAGER->LoadAndGetTextureID("Assets/Textures/Player.png"));

			//Check:
			allTexturesLoaded = true;
		}
	}

	//Init - Game:
	GAME_CAMERA->Init();
	MAP->Init(TILESET, "Assets/Levels/a6.tmx");
	WHITE_BOMBERMAN->Init();
	WHITE_BOMBERMAN->SetWorldPointer(MAP);

	do
	{
		//Time Update:
		TIME_MANAGER->UpdateTime();

		//Clear Screen:
		VIDEO->ClearScreen();

		//Update:
		{
			//SDL_Event:
			INPUT->UpdateInput();

			//Game:
			WHITE_BOMBERMAN->Update();
			GAME_CAMERA->Update(MAP, WHITE_BOMBERMAN);
		}

		//Render:
		{
			//Game:
			MAP->Render(GAME_CAMERA, TILESET->GetTextureId());
			WHITE_BOMBERMAN->Render(WHITE_BOMBERMAN->GetTextureId());
		}

		//Update Screen:
		VIDEO->UpdateScreen();

	} while (WHITE_BOMBERMAN->GetCurrentLives() != 0);

	//Free Memory:
	delete WHITE_BOMBERMAN;
	delete MAP;
	delete TILESET;
	delete GAME_CAMERA;

	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/PlanetQuarry.png");
	RESOURCE_MANAGER->RemoveTexture("Assets/Textures/Player.png");

	VIDEO->CloseWindow();

	return 0;
}