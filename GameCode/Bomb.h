#ifndef BOMB_H
#define BOMB_H

#include "Entity.h"

class Camera;
class Map;

struct ExplosionParts {
	int sourceX;
	int sourceY;
	int offsetX;
	int offsetY;
};


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

	void		Init() override;
	void		Update(Map* _ptrMap);
	void		Render(int _idCharacterTexture, Camera* _ptrCamera, Map* _ptrMap);

	void		SetBombState(bool _value) { _mHasExplodedYet = _value; };
	bool		GetBombState() { return _mHasExplodedYet; };
	void		SetRadiusExplosion(int _value) { _mRadius = _value; };
	int			GetRadiusExplosion() { return _mRadius; };

	bool		BombShouldBeDeleted();
	void		GenerateExplosion(Map* _ptrMap);
	bool		CanExplosionExpandAtOffset(int _offsetX, int _offsetY, Map* _ptrMap);

private:
	bool		_mHasExplodedYet;
	int			_mRadius;
	int			_mExplosionPhase[9];
	bool		_mEliminateFlag;

	std::vector<ExplosionParts>		_mExplosionParts;
};

#endif

