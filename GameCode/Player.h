#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Entity.h"

class Camera;
class Map;
class Bomb;

enum EState {
	ST_IDLE, ST_WALK, ST_DIE
};


//! Player class
/*
	Represents the player's character.
*/
class Player : public Entity
{
public:
	Player(void);
	~Player(void);

	void		Init() override;
	void		Update(Map* _ptrMap);
	void		Render(int _idCharacterTexture, Camera* _ptrCamera);

	void		SetCurrentLives(int _value) { _mLife = _value; };
	int			GetCurrentLives() { return _mLife; };
	void		SetLookDirection(int _direction) { _mLookDirection = _direction; };
	int			GetLookDirection() { return _mLookDirection; };
	void		SetCurrentLives(EState _state) { _mCurrentState = _state; };
	EState		GetCurrentState() { return _mCurrentState; };
	void		SetBombQuantity(int _value) { _mBombQuantity = _value; };
	int			GetBombQuantity() { return _mBombQuantity; };
	const		std::vector<Bomb*>& GetBombs() const { return _pBombs; }

	bool		IsTileOccupied(int _x, int _y);
	//bool		TrySlideIfBlocked(int _direction);

private:
	int							_mLife;
	int							_mLookDirection;
	EState						_mCurrentState;

	int							_mBombQuantity;
	std::vector<Bomb*>			_pBombs;
};

#endif

