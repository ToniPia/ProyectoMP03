#include <iostream>

#include "../EngineCode/Defines.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/SceneManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Audio.h"
#include "../EngineCode/Input.h"

bool _gameOn = true;


int main(int argc, char* argv[])
{
	//Main Loop

	//Time Control:
	TIME_MANAGER->RandomTime();
	TIME_MANAGER->SetFPS(FPS);

	//Init:
	VIDEO->InitVideo();
	AUDIO->InitMixer();
	INPUT->InitInput();
	SCENE_MANAGER->Init();

	while (SCENE_MANAGER->GetGameState())
	{
		//Time Update:
		TIME_MANAGER->UpdateTime();

		//Clear Screen:
		VIDEO->ClearScreen();
		//SDL_SetRenderDrawColor(VIDEO->GetScreenRenderer(), 255, 255, 255, 255);

		//ReInit or not:
		if (SCENE_MANAGER->GetCurrentScene()->mustReInit())
		{
			SCENE_MANAGER->GetCurrentScene()->ReInit();
		}

		//Read Controls:
		INPUT->UpdateInput();

		//Update Scene:
		SCENE_MANAGER->GetCurrentScene()->Update();

		//Render Scene:
		if (!SCENE_MANAGER->GetCurrentScene()->mustReInit())
		{
			SCENE_MANAGER->GetCurrentScene()->Render();
		}

		//Update Screen:
		VIDEO->UpdateScreen();
	}

	return 0;
}
