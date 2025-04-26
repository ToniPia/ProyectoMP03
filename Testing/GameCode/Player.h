#ifndef PLAYER_H
#define PLAYER_H

#include "../SDL/include/SDL.h"

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"

class Map;

enum _eStates
{
	ST_IDLE, ST_WALK, ST_DIE
};


//! Player class
/*
	Represents the player's character.
*/
class Player
{
public:
	Player(void);
	~Player(void);

	void	Init();
	void	Update();
	void	Render(int _idCharacterTexture);

	void	SetPosXWorld(int _value) { _mRectWorld.x = _value; };
	int		GetPosXWorld() { return _mRectWorld.x; };
	void	SetPosYWorld(int _value) { _mRectWorld.y = _value; };
	int		GetPosYWorld() { return _mRectWorld.y; };
	void	SetWidthWorld(int _value) { _mRectWorld.x = _value; };
	int		GetWidthWorld() { return _mRectWorld.w; };
	void	SetHeightWorld(int _value) { _mRectWorld.h = _value; };
	int		GetHeightWorld() { return _mRectWorld.h; };
	void	SetTextureId(int _value) { _mTextureID = _value; };
	int		GetTextureId() { return _mTextureID; };
	void	SetCameraPositionX(int _value) { _mCameraX = _value; };

	int		GetCurrentLives() { return _mLife; };
	int		GetCurrentState() { return _mCurrentState; };
	int		GetLookDirection() { return _mLookDirection; };

	void	SetWorldPointer(Map* _map);

private:
	SDL_Rect	_mRectGraphic;
	SDL_Rect	_mRectWorld;
	int			_mWorldSizeW;
	int			_mWorldSizeH;
	int			_mCameraX;
	int			_mLife;
	
	int			_mTextureID;
	_eStates	_mCurrentState;
	float		_mTimeBetweenStates;
	float		_mTimeBetweenFrames;
	int			_mLookDirection;

	Map*		_pCurrentWorld;

	bool		CheckCollisionWithWorld(int _direction);
};

#endif

