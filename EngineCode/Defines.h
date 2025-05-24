#pragma once

// Defines:

// ---

//* Engine Instances:
#define		RESOURCE_MANAGER ResourceManager::GetInstance()
#define		VIDEO Video::GetInstance()
#define		AUDIO Audio::GetInstance()
#define		INPUT Input::GetInstance()
#define		TIME_MANAGER TimeManager::GetInstance()
#define		SCENE_MANAGER SceneManager::GetInstance()

//*	Resolution Screen:
#define		SCREEN_W	1080		//2048 px
#define		SCREEN_H	832			//480 px

//* Time:
#define		FPS			60			//60 fps

//* Number Scenes:
#define		NUM_SCENES	_LASTSCENE

//* Movement Velocity:
#define		SPEED		2			//2 int

//* Limit Camera Position:
#define		LIMIT		3			//3 int

