#ifndef SCENEGAME_H
#define SCENEGAME_H

#include <vector>

#include "Scene.h"

class Map;
class Tileset;
class Camera;
class Player;


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

private:
	bool					_mAllTexturesLoaded;

	Map*					_pMap;
	Tileset*				_pTileset;
	Camera*					_pCamera;
	Player*					_pPlayer;
};

#endif

