#include "Bomb.h"

#include "../EngineCode/Defines.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"

#include "Camera.h"
#include "Map.h"


Bomb::Bomb(void)
{
	_mHasExplodedYet = false;
	for (int i = 0; i < 9; ++i) {
		_mExplosionPhase[i] = 0;
	}
	_mEliminateFlag = false;
}

Bomb::Bomb(int _posXWorld, int _posYWorld)
{
	Init();

	int tileSize = 64;

	// Usar el centro del jugador
	int centerX = _posXWorld + GetWidthWorld() / 2;
	int centerY = _posYWorld + GetHeightWorld() / 2;

	// Calcular tile más cercano
	int alignedX = (centerX / tileSize) * tileSize;
	int alignedY = (centerY / tileSize) * tileSize;

	SetPosXWorld(alignedX);
	SetPosYWorld(alignedY);
}

Bomb::~Bomb(void)
{

}

void Bomb::Init()
{
	SDL_Rect rectGraphicInit = { 0, 0, 64, 64 };
	SDL_Rect rectWorldInit = { 0, 0, 64, 64 };
	SetRectGraphic(rectGraphicInit);
	SetRectWorld(rectWorldInit);

	SetTimeBetweenLastFrame(0);
	SetCurrentSprite(0);

	_mHasExplodedYet = false;
	int values[9] = { 1, 2, 1, 0, 1, 2, 1, 0, 1 };
	for (int i = 0; i < 9; ++i) {
		_mExplosionPhase[i] = values[i];
	}
	_mEliminateFlag = false;

	AddNewAnimation(Animation{ 10, 600, 64, 0, 64, 64 });
}

void Bomb::Update()
{
	int deltaTime = TIME_MANAGER->GetDeltaTime();

	SetTimeBetweenLastFrame(GetTimeBetweenLastFrame() + deltaTime);

	// Animations
	if (GetTimeBetweenLastFrame() > GetAnimationsVector()[GetCurrentAnimation()].msPerAnimation)
	{
		SetTimeBetweenLastFrame(0);
		SetCurrentSprite((GetCurrentSprite() + 1) % GetAnimationsVector()[GetCurrentAnimation()].framesPerAnimation);

		if (!_mHasExplodedYet && GetCurrentSprite() > 8)
		{
			_mHasExplodedYet = true;
			SetCurrentSprite(0);
		}
	}
}

void Bomb::Render(int _idCharacterTexture, Camera* _ptrCamera)
{
	if (_mHasExplodedYet == false)
	{
		int spriteX = 0;
		if (_mExplosionPhase[GetCurrentSprite()] == 1) spriteX = 64;
		else if (_mExplosionPhase[GetCurrentSprite()] == 2) spriteX = 128;

		SetPosXGraphic(spriteX);

		SDL_Rect renderRect = {
			GetPosXWorld() - _ptrCamera->GetPosX(),
			GetPosYWorld() - _ptrCamera->GetPosY(),
			GetWidthWorld(),
			GetHeightWorld()
		};

		Entity::Render(_idCharacterTexture, GetRectGraphic(), renderRect);
	}
}
