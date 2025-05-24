#ifndef SCENEMANAGER_H
#define	SCENEMANAGER_H

#include <vector>

#include "../GameCode/Scene.h"

enum _eScenes
{
	MAIN, OPTIONS, SAVE_LOAD, WORLD_SELECTION, GAME, GAMEOVER, _LASTSCENE
};


//! SceneManager class
/*
	Handles the management of the different scenes in the game.
*/
class SceneManager
{
public:
	//! Destructor.
	~SceneManager(void);

	//! Initializes the SceneManager.
	void Init();

	//! Changes the current scene for another.
	/*
		\param1: next scene to update
		\param2: reinitialize the state of the scene for the new one
	*/
	void ChangeScene(_eScenes _nextScene, bool _reInit = true);

	//! Get for _mCurrentScene (number of existing scenes)
	_eScenes GetCurrentSceneEnum() { return _mCurrentScene; };

	//! Get for _pScenesVector[_mCurrentScene] (current scene being played)
	Scene* GetCurrentScene() { return _pScenesVector[_mCurrentScene]; };

	//! Set for _mGameOn
	void SetGameState(bool _gameState) { _mGameOn = _gameState; };
	//! Get for _mGameOn
	bool GetGameState() { return _mGameOn; };

	//! Gets Singleton instance.
	/*
		\return: Instance of TimeManager (Singleton pattern)
	*/
	static SceneManager* GetInstance();

protected:
	//! Constructor.
	SceneManager(void);

	std::vector<Scene*>		_pScenesVector;		/*< Vector that stores Scene objects */
	_eScenes				_mCurrentScene;		/*< _eScene variable. Used to know which scene is being played */
	bool					_mGameOn;			/*< Bool variable. Used to check if game is on or off*/
	static SceneManager*	_pInstance;			/*< Singleton instance */
};

#endif

