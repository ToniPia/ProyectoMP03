#include "Explosion.h"

#include <vector>

#include "../EngineCode/Defines.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"

#include "Camera.h"
#include "Map.h"


Explosion::Explosion(void)
{
	_mRadius = 0;
	_mEliminateFlag = false;

	_mExplosionParts.resize(0);
}

Explosion::~Explosion(void)
{

}

void Explosion::Init()
{
	SDL_Rect rectGraphicInit = { 0, 0, 64, 64 };
	SDL_Rect rectWorldInit = { 0, 0, 64, 64 };
	SetRectGraphic(rectGraphicInit);
	SetRectWorld(rectWorldInit);

	SetTimeBetweenLastFrame(0);
	SetCurrentSprite(0);

	_mEliminateFlag = false;
	_mRadius = 1;

	_mExplosionParts.resize(0);

	AddNewAnimation(Animation{ 5, 400, 192, 0, 64, 64 });
}

void Explosion::Update(Map* _ptrMap)
{
	if (GetBombState())
	{
		int deltaTime = TIME_MANAGER->GetDeltaTime();

		SetTimeBetweenLastFrame(GetTimeBetweenLastFrame() + deltaTime);

		// Animations
		if (GetTimeBetweenLastFrame() > GetAnimationsVector()[GetCurrentAnimation()].msPerAnimation)
		{
			SetTimeBetweenLastFrame(0);
			SetCurrentSprite((GetCurrentSprite() + 1) % GetAnimationsVector()[GetCurrentAnimation()].framesPerAnimation);

			if (GetCurrentSprite() > 3)
			{
				SetCurrentSprite(0);
				_mEliminateFlag = true;
			}
		}
		if (_mEliminateFlag && _mExplosionParts.empty())
		{
			SetEliminateFlag(true);
		}
		GenerateExplosion(_ptrMap);
	}
}

void Explosion::Render(int _idCharacterTexture, Camera* _ptrCamera)
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

void Explosion::GenerateExplosion(Map* _ptrMap)
{
	int tileSize = 64;
	_mExplosionParts.push_back({ 64, 0, 0, 0 }); // Nexus

	for (int i = 0; i < _mRadius; ++i)
	{
		// Up
		if (CanExplosionExpandAtOffset(0, -i * tileSize, _ptrMap)) {
			int spriteX = ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			int spriteY = 192;
			_mExplosionParts.push_back({ spriteX, spriteY, 0, -i * tileSize });
		}
		else break;

		// Right
		if (CanExplosionExpandAtOffset(i * tileSize, 0, _ptrMap)) {
			int spriteX = ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			int spriteY = 256;
			_mExplosionParts.push_back({ spriteX, spriteY, i * tileSize, 0 });
		}
		else break;

		// Down
		if (CanExplosionExpandAtOffset(0, i * tileSize, _ptrMap)) {
			int spriteX = ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			int spriteY = 128;
			_mExplosionParts.push_back({ spriteX, spriteY, 0, i * tileSize });
		}
		else break;

		// Left
		if (CanExplosionExpandAtOffset(-i * tileSize, 0, _ptrMap)) {
			int spriteX = ((GetCurrentSprite() == 4) ? 0 : GetCurrentSprite() * 64);
			int spriteY = 64;
			_mExplosionParts.push_back({ spriteX, spriteY, -i * tileSize, 0 });
		}
		else break;
	}
}

bool Explosion::CanExplosionExpandAtOffset(int _offsetX, int _offsetY, Map* _ptrMap)
{
	int worldX = GetPosXWorld() + _offsetX;
	int worldY = GetPosYWorld() + _offsetY;

	Point point = { worldX, worldY };

	return !_ptrMap->IsThereCollisionWithTileMap(point);
}
