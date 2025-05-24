#include "Camera.h"

#include <iostream>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/Input.h"

#include "Map.h"
#include "Player.h"


Camera::Camera(void)
{
	_mPosX = 0;
	_mPosY = 0;
	_mWidth = 0;
	_mHeight = 0;
	_mLimitX1 = 0;
	_mLimitX2 = 0;
}

Camera::~Camera(void)
{

}

void Camera::Init()
{
	_mPosX = 0;
	_mPosY = 0;
	_mWidth = SCREEN_W;
	_mHeight = SCREEN_H;
	_mLimitX1 = (6 * SCREEN_W) / 10;
	_mLimitX2 = SCREEN_W / 3;
}

void Camera::Update(Map* _ptrMap, Player* _ptrPlayer)
{
	if (_ptrMap->GetWidth() > 17)
	{
		if (_ptrPlayer->GetPosXWorld() - _mPosX > _mLimitX1)
		{
			_mPosX = _ptrPlayer->GetPosXWorld() - _mLimitX1;
		}
		else if (_ptrPlayer->GetPosXWorld() - _mPosX < _mLimitX2)
		{
			_mPosX = _ptrPlayer->GetPosXWorld() - _mLimitX2;
		}
	}
	//_mPosY += SPEED;
	//_mPosY -= SPEED;

	if (_mPosX < 0)
	{
		_mPosX = 0;
	}
	else if ((_mPosX + _mWidth) > _ptrMap->GetMaxWidth())
	{
		_mPosX = _ptrMap->GetMaxWidth() - _mWidth;
	}

	if (_mPosY < 0)
	{
		_mPosY = 0;
	}
	else if ((_mPosY + _mHeight) > _ptrMap->GetMaxHeight())
	{
		_mPosY = _ptrMap->GetMaxHeight() - _mHeight;
	}

	_ptrMap->SetRenderInitX(_mPosX);
}
