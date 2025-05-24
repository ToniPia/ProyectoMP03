#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Camera;

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
	void		Update();
	void		Render(int _idCharacterTexture, Camera* _ptrCamera);

	void		SetCurrentLives(int _value) { _mLife = _value; };
	int			GetCurrentLives() { return _mLife; };
	void		SetCurrentLives(EState _state) { _mCurrentState = _state; };
	EState		GetCurrentState() { return _mCurrentState; };
	void		SetCurrentAnimationIndex(int _index) { _mCurrentAnimationIndex = _index; };
	int			GetCurrentAnimationIndex() { return _mCurrentAnimationIndex; };

	//bool		TrySlideIfBlocked(int _direction);

private:
	int							_mLife;
	EState						_mCurrentState;
	int							_mCurrentAnimationIndex;
};

#endif

