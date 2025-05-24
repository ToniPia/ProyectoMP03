#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "../SDL/include/SDL.h"

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"

class Map;

struct Animation
{
	int framesPerAnimation = 0;
	int msPerAnimation = 500;
	int spritesPosX = 0;
	int spritePosY = 0;
	int spriteWidth = 88;
	int spriteHeight = 88;
};


//! Entity class
/*
	Represents any entity of the game.
*/
class Entity
{
public:
	Entity(void);
	~Entity(void);

	virtual void	Init();
	virtual void	Update(SDL_Rect _rectWorld);
	virtual void	Render(int _idCharacterTexture, SDL_Rect _rectGraphic, SDL_Rect _rectWorld);

	void	SetPosXGraphic(int _value) { _mRectGraphic.x = _value; };
	int		GetPosXGraphic() { return _mRectGraphic.x; };
	void	SetPosYGraphic(int _value) { _mRectGraphic.y = _value; };
	int		GetPosYGraphic() { return _mRectGraphic.y; };

	void	SetPosXWorld(int _value) { _mRectWorld.x = _value; };
	int		GetPosXWorld() { return _mRectWorld.x; };
	void	SetPosYWorld(int _value) { _mRectWorld.y = _value; };
	int		GetPosYWorld() { return _mRectWorld.y; };

	void	SetWidthWorld(int _value) { _mRectWorld.x = _value; };
	int		GetWidthWorld() { return _mRectWorld.w; };
	void	SetHeightWorld(int _value) { _mRectWorld.h = _value; };
	int		GetHeightWorld() { return _mRectWorld.h; };

	void		SetRectGraphic(SDL_Rect _rectGraphic) { _mRectGraphic = _rectGraphic; };
	SDL_Rect	GetRectGraphic() { return _mRectGraphic; };
	void		SetRectWorld(SDL_Rect _rectWorld) { _mRectWorld = _rectWorld; };
	SDL_Rect	GetRectWorld() { return _mRectWorld; };

	void	SetTextureId(int _value) { _mTextureID = _value; };
	int		GetTextureId() { return _mTextureID; };

	void					SetCurrentAnimation(int _animation) { _mCurrentAnimation = _animation; };
	int						GetCurrentAnimation() { return _mCurrentAnimation; };
	void					SetTimeBetweenLastFrame(int _time) { timeBetweenLastFrame = _time; };
	int						GetTimeBetweenLastFrame() { return timeBetweenLastFrame; };
	std::vector<Animation>	GetAnimationsVector() { return _mAnimationsVector; };
	void					SetCurrentSprite(int _sprite) { _mCurrentSprite = _sprite; };
	int						GetCurrentSprite() { return _mCurrentSprite; };
	Map*					GetCurrentWorld() { return _pCurrentWorld; };
	void					SetWorldPointer(Map* _map);

	SDL_Rect	GetCollisionBox();
	bool		CheckCollisionWithWorld(int _direction);
	void		AddNewAnimation(Animation _animation);

private:
	SDL_Rect					_mRectGraphic;
	SDL_Rect					_mRectWorld;
	int							_mWorldSizeW;
	int							_mWorldSizeH;

	int							_mTextureID;
	int							_mCurrentAnimation;
	int							timeBetweenLastFrame;
	std::vector<Animation>		_mAnimationsVector;
	int							_mCurrentSprite;

	Map*						_pCurrentWorld;
};

#endif

