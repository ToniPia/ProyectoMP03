#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <vector>

#include "Scene.h"

class Map;
class Tileset;
class Camera;
class Player;
class Bomb;
class Rock;


//! SceneGame class
/*!
	Handles the Game Scene for the game.
*/
class SceneGame : public Scene
{
public:
	SceneGame(void);
	~SceneGame(void);

	void	Init() override;
	void	Update() override;
	void	Render() override;
	void	UnloadResources() override;

	void	SetCurrentLevel(int _value) { _mCurrentLevel = _value; };
	int		GetCurrentLevel() { return _mCurrentLevel; };

private:
	int						_mCurrentLevel;

	std::vector<int>		_mIdsTexturesVector;
	std::vector<int>		_mIdsSoundsVector;
	bool					_mAllTexturesLoaded;
	bool					_mAllSoundsLoaded;

	Map*					_pMap;
	Tileset*				_pTileset;
	Camera*					_pCamera;
	Player*					_pPlayer;
	Bomb*					_pBomb;
	Rock*					_pRock;
};

#endif

