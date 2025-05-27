#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <vector>

#include "Bomb.h"

struct ExplosionParts {
	int sourceX;
	int sourceY;
	int offsetX;
	int offsetY;
};


//! Bomb class
/*
	Represents the explosion of any bombs spawned by the player.
*/
class Explosion : public Bomb
{
public:
	Explosion(void);
	~Explosion(void);

	void		Init();
	void		Update(Map* _ptrMap);
	void		Render(int _idCharacterTexture, Camera* _ptrCamera);

	void		SetRadiusExplosion(int _value) { _mRadius = _value; };
	int			GetRadiusExplosion() { return _mRadius; };

	void		GenerateExplosion(Map* _ptrMap);
	bool		CanExplosionExpandAtOffset(int _offsetX, int _offsetY, Map* _ptrMap);

private:
	int			_mRadius;
	bool		_mEliminateFlag;

	std::vector<ExplosionParts>		_mExplosionParts;
};

#endif

