#include "Entity.h"

#include <iostream>
#include <vector>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Input.h"

#include "Map.h"


Entity::Entity(void)
{
	_mRectGraphic = { 0, 0, 0, 0 };
	_mRectWorld = { 0, 0, 0, 0 };
	_mWorldSizeW = 0;
	_mWorldSizeH = 0;
	_mTextureID = 0;
	_mCurrentAnimation = 0;
	timeBetweenLastFrame = 0;
	_mAnimationsVector.resize(0);
	_mCurrentSprite = 0;
	_mLookDirection = 0;
	_pCurrentWorld = nullptr;
}

Entity::~Entity(void)
{

}

void Entity::Init()
{

}

void Entity::Update(SDL_Rect _rectWorld)
{
	//Limits
	if (_rectWorld.y < 0)
	{
		_rectWorld.y = 0;
	}
	if (_rectWorld.x < 0)
	{
		_rectWorld.x = 0;
	}
	if ((_rectWorld.x + _rectWorld.w) > _mWorldSizeW)
	{
		_rectWorld.x = _mWorldSizeW - _rectWorld.w;
	}
	if ((_rectWorld.y + _rectWorld.h) > _mWorldSizeH)
	{
		_rectWorld.y = _mWorldSizeH - _rectWorld.h;
	}
}

void Entity::Render(int _idCharacterTexture, SDL_Rect _rectGraphic, SDL_Rect _rectWorld)
{
	VIDEO->RenderTexture(_idCharacterTexture, _mRectGraphic, _mRectWorld);
}

SDL_Rect Entity::GetCollisionBox()
{
	const int collisionBoxWidth = 48;
	const int collisionBoxHeight = 48;

	int boxX = _mRectWorld.x + (_mRectWorld.w - collisionBoxWidth) / 2;
	int boxY = _mRectWorld.y + _mRectWorld.h - collisionBoxHeight;

	return { boxX, boxY, collisionBoxWidth, collisionBoxHeight };
}

void Entity::SetWorldPointer(Map* _map)
{
	_pCurrentWorld = _map;

	_mWorldSizeW = _pCurrentWorld->GetWidth() * _pCurrentWorld->GetTileWidth();
	_mWorldSizeH = _pCurrentWorld->GetHeight() * _pCurrentWorld->GetTileHeight();
}

bool Entity::CheckCollisionWithWorld(int _direction)
{
	SDL_Rect collisionBox = GetCollisionBox();

	std::vector<Point> pointsToCheck;

	if (_direction == UP)
	{
		int nextY = collisionBox.y - SPEED;
		int leftX = collisionBox.x + 4;
		int middleX = collisionBox.x + collisionBox.w / 2;
		int rightX = collisionBox.x + collisionBox.w - 4;

		pointsToCheck.emplace_back(leftX, nextY);
		pointsToCheck.emplace_back(middleX, nextY);
		pointsToCheck.emplace_back(rightX, nextY);
	}
	else if (_direction == RIGHT)
	{
		int nextX = collisionBox.x + SPEED + collisionBox.w;
		int topY = collisionBox.y + 4;
		int middleY = collisionBox.y + collisionBox.h / 2;
		int bottomY = collisionBox.y + collisionBox.h - 4;

		pointsToCheck.emplace_back(nextX, topY);
		pointsToCheck.emplace_back(nextX, middleY);
		pointsToCheck.emplace_back(nextX, bottomY);
	}
	else if (_direction == DOWN)
	{
		int nextY = collisionBox.y + collisionBox.h + SPEED;
		int leftX = collisionBox.x + 4;
		int middleX = collisionBox.x + collisionBox.w / 2;
		int rightX = collisionBox.x + collisionBox.w - 4;

		pointsToCheck.emplace_back(leftX, nextY);
		pointsToCheck.emplace_back(middleX, nextY);
		pointsToCheck.emplace_back(rightX, nextY);
	}
	else if (_direction == LEFT)
	{
		int nextX = collisionBox.x - SPEED;
		int topY = collisionBox.y + 4;
		int middleY = collisionBox.y + collisionBox.h / 2;
		int bottomY = collisionBox.y + collisionBox.h - 4;

		pointsToCheck.emplace_back(nextX, topY);
		pointsToCheck.emplace_back(nextX, middleY);
		pointsToCheck.emplace_back(nextX, bottomY);
	}

	for (const Point& p : pointsToCheck)
	{
		if (_pCurrentWorld->IsThereCollisionWithTileMap(p))
		{
			return true;
		}
	}
	return false;
}

void Entity::AddNewAnimation(Animation _animation)
{
	_mAnimationsVector.emplace_back(_animation);
}
