#ifndef ROCK_H
#define ROCK_H

#include "Entity.h"

class Camera;
class Map;


//! Rock class
/*
	Represents the rocks spawned in the level.
*/
class Rock : public Entity
{
public:
	Rock(void);
	~Rock(void);

	void		Init() override;
	void		Update(Map* _ptrMap);
	void		Render(int _idCharacterTexture, Camera* _ptrCamera);

	void		SetRockState(bool _value) { _mHasItBroken = _value; };
	bool		GetRockState() { return _mHasItBroken; };
	void		SetEliminateFlag(bool _value) { _mEliminateFlag = _value; };
	bool		GetEliminateFlag() { return _mEliminateFlag; };

private:
	bool		_mHasItBroken;
	bool		_mEliminateFlag;
};

#endif

