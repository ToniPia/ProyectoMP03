#include "SceneManager.h"

#include "../EngineCode/Defines.h"

#include "../GameCode/SceneMain.h"
//#include "SceneOptions.h"
//#include "SceneSaveLoad.h"
//#include "SceneIntro.h"
#include "../GameCode/SceneGame.h"
//#include "SceneGameOver.h"


SceneManager* SceneManager::_pInstance = NULL;

SceneManager::SceneManager()
{
	_pScenesVector.resize(0);
	_mCurrentScene = MAIN;
	_mGameOn = true;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	_pScenesVector.resize(NUM_SCENES);

	SceneMain* Main = new SceneMain();
	/*SceneOptions* options = new SceneOptions();
	SceneSaveLoad* save = new SceneSaveLoad();
	SceneIntro* world_select = new SceneIntro();*/
	SceneGame* Game = new SceneGame();
	/*SceneGameOver* gameover = new SceneGameOver();*/

	_pScenesVector[MAIN] = Main;
	/*_pScenesVector[OPTIONS] = options;
	_pScenesVector[SAVE_LOAD] = save;
	_pScenesVector[WORLD_SELECTION] = world_select;*/
	_pScenesVector[GAME] = Game;
	/*_pScenesVector[GAMEOVER] = gameover;*/

	Main->Init();
	/*options->init();
	save->init();
	config->init();
	intro->init();*/
	Game->Init();
	/*gameover->init(); */

	_mCurrentScene = MAIN;
}

void SceneManager::ChangeScene(_eScenes _nextScene, bool _reInit)
{
	//_pScenesVector[_mCurrentScene]->UnloadResources();
	_pScenesVector[_nextScene]->setReInit(_reInit);
	_mCurrentScene = _nextScene;
}

SceneManager* SceneManager::GetInstance()
{
	if (SceneManager::_pInstance == nullptr)
	{
		SceneManager::_pInstance = new SceneManager();
	}

	return SceneManager::_pInstance;
}
