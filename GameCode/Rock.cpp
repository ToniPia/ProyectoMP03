#include "Rock.h"

#include "../EngineCode/Defines.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"

#include "Camera.h"
#include "Map.h"


Rock::Rock(void)
{
	_mHasItBroken = false;
	_mEliminateFlag = false;
}

Rock::~Rock(void)
{

}

void Rock::Init()
{
	SDL_Rect rectGraphicInit = { 0, 0, 64, 64 };
	SDL_Rect rectWorldInit = { 0, 0, 64, 64 };
	SetRectGraphic(rectGraphicInit);
	SetRectWorld(rectWorldInit);

	SetTimeBetweenLastFrame(0);
	SetCurrentSprite(0);

	_mHasItBroken = false;
	_mEliminateFlag = false;

	AddNewAnimation(Animation{ 7, 600, 64, 0, 64, 64 });
}

void Rock::Update(Map* _ptrMap)
{
	if (_mHasItBroken)
	{
		SetCurrentSprite(+1);
	}

	// Animations
	if (GetTimeBetweenLastFrame() > GetAnimationsVector()[GetCurrentAnimation()].msPerAnimation)
	{
		SetTimeBetweenLastFrame(0);
		SetCurrentSprite((GetCurrentSprite() + 1) % GetAnimationsVector()[GetCurrentAnimation()].framesPerAnimation);

		if (GetCurrentSprite() > 5)
		{
			_mEliminateFlag = true;
			SetCurrentSprite(0);
		}
	}
}

void Rock::Render(int _idCharacterTexture, Camera* _ptrCamera)
{
	if (!_mHasItBroken)
	{
		SDL_Rect renderRect = {
			GetPosXWorld() - _ptrCamera->GetPosX(),
			GetPosYWorld() - _ptrCamera->GetPosY(),
			GetWidthWorld(),
			GetHeightWorld()
		};

		Entity::Render(_idCharacterTexture, GetRectGraphic(), renderRect);
	}
	else
	{
		SetPosXGraphic(GetCurrentSprite() * 64);

		SDL_Rect renderRect = {
			GetPosXWorld() - _ptrCamera->GetPosX(),
			GetPosYWorld() - _ptrCamera->GetPosY(),
			GetWidthWorld(),
			GetHeightWorld()
		};

		Entity::Render(_idCharacterTexture, GetRectGraphic(), renderRect);
	}
}
