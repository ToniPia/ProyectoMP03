#include "Bomb.h"

#include <iostream>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"

#include "Camera.h"
#include "Map.h"


Bomb::Bomb(void)
{
	_mHasExplodedYet = false;
	_mRadius = 0;
	for (int i = 0; i < 9; ++i) {
		_mExplosionPhase[i] = 0;
	}
	_mEliminateFlag = false;

	_mExplosionParts.resize(0);
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

	SetCurrentAnimation(0);
	SetTimeBetweenLastFrame(0);
	SetCurrentSprite(0);

	_mHasExplodedYet = false;
	_mRadius = 1;
	int values[9] = { 1, 2, 1, 0, 1, 2, 1, 0, 1 };
	for (int i = 0; i < 9; ++i) {
		_mExplosionPhase[i] = values[i];
	}
	_mEliminateFlag = false;

	_mExplosionParts.clear();

	AddNewAnimation(Animation{ 10, 600, 64, 0, 64, 64 });
	AddNewAnimation(Animation{ 5, 400, 192, 0, 64, 64 });
}

void Bomb::Update(Map* _ptrMap)
{
	int deltaTime = TIME_MANAGER->GetDeltaTime();

	SetCurrentAnimation(_mHasExplodedYet ? 1 : 0);
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
		else if (_mHasExplodedYet && GetCurrentSprite() > 4)
		{
			_mEliminateFlag = true;
		}
	}
	if (_mHasExplodedYet && _mExplosionParts.empty())
	{
		GenerateExplosion(_ptrMap);
	}
}

void Bomb::Render(int _idCharacterTexture, Camera* _ptrCamera, Map* _ptrMap)
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
	else if (_mHasExplodedYet == true)
	{
		int frame = GetCurrentSprite();
		for (const auto& part : _mExplosionParts)
		{
			SDL_Rect srcRect = {
				part.sourceX,
				part.sourceY,
				GetWidthWorld(),
				GetHeightWorld()
			};
			SDL_Rect destRect = {
				GetPosXWorld() + part.offsetX - _ptrCamera->GetPosX(),
				GetPosYWorld() + part.offsetY - _ptrCamera->GetPosY(),
				GetWidthWorld(),
				GetHeightWorld()
			};
			Entity::Render(_idCharacterTexture, srcRect, destRect);
		}
	}
}

bool Bomb::BombShouldBeDeleted()
{
	return _mEliminateFlag;
}

void Bomb::GenerateExplosion(Map* _ptrMap)
{
	int tileSize = 64;
	_mExplosionParts.push_back({ 64, 0, 0, 0 }); // Nexus

	for (int i = 1; i <= _mRadius; ++i)
	{
		// Up
		if (CanExplosionExpandAtOffset(0, -i * tileSize, _ptrMap)) {
			int spriteX = ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			_mExplosionParts.push_back({ spriteX, 64, 0, -i * tileSize });
		}
		else break;

		// Right
		if (CanExplosionExpandAtOffset(i * tileSize, 0, _ptrMap)) {
			int spriteX = 256 + ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			_mExplosionParts.push_back({ spriteX, 64, i * tileSize, 0 });
		}
		else break;

		// Down
		if (CanExplosionExpandAtOffset(0, i * tileSize, _ptrMap)) {
			int spriteX = ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			_mExplosionParts.push_back({ spriteX, 192, 0, i * tileSize });
		}
		else break;

		// Left
		if (CanExplosionExpandAtOffset(-i * tileSize, 0, _ptrMap)) {
			int spriteX = 256 + ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			_mExplosionParts.push_back({ spriteX, 192, -i * tileSize, 0 });
		}
		else break;
	}
}

bool Bomb::CanExplosionExpandAtOffset(int _offsetX, int _offsetY, Map* _ptrMap)
{
	int worldX = GetPosXWorld() + _offsetX;
	int worldY = GetPosYWorld() + _offsetY;

	Point point = { worldX, worldY };

	return !_ptrMap->IsThereCollisionWithTileMap(point);
}
