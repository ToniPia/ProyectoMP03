#ifndef BOMB_H
#define BOMB_H

#include "Entity.h"

class Camera;
class Map;


//! Bomb class
/*
	Represents the bombs spawned by the player.
*/
class Bomb : public Entity
{
public:
	Bomb(void);
	Bomb(int _posXWorld, int _posYWorld);
	~Bomb(void);

	void		Init();
	void		Update();
	void		Render(int _idCharacterTexture, Camera* _ptrCamera);

	void		SetBombState(bool _value) { _mHasExplodedYet = _value; };
	bool		GetBombState() { return _mHasExplodedYet; };
	void		SetEliminateFlag(bool _value) { _mEliminateFlag = _value; };
	bool		GetEliminateFlag() { return _mEliminateFlag; };

private:
	bool		_mHasExplodedYet;
	int			_mExplosionPhase[9];
	bool		_mEliminateFlag;
};

#endif

