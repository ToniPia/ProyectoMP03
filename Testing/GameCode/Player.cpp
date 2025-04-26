#include "Player.h"

#include <iostream>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Input.h"

#include "Map.h"

int frameCounter = 0;
int framesPerAnimation[] = { 0, 4, 12 };
float msPerAnimation[] = { 0.0f, 1000.0f, 3000.0f };
int walkAnimationSequence[] = { 1, 0, 2, 0 };
int diePhase = 0;
int dieAnimationSequence[] = { 0, 1, 0, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int spritesPosX[] = { 0, 88, 176, 264, 352, 440, 528, 616, 704 };
int spritesPosY[] = { 0, 88, 176, 264, 352 };


Player::Player(void)
{
	_mRectGraphic = { 0, 0, 0, 0 };
	_mRectWorld = { 0, 0, 0, 0 };
	_mWorldSizeW = 0;
	_mWorldSizeH = 0;
	_mCameraX = 0;
	_mLife = 0;
	_mTextureID = 0;
	_mCurrentState = ST_IDLE;
	_mTimeBetweenStates = 0;
	_mTimeBetweenFrames = 0;
	_mLookDirection = 0;
	_pCurrentWorld = nullptr;
}

Player::~Player(void)
{

}

void Player::Init()
{
	_mRectGraphic = { 0, 0, 88, 88 };
	_mRectWorld = { 120, 40, 88, 88 };
	_mLife = 1;
	_mCurrentState = ST_IDLE;
	_mTimeBetweenStates = 0;
	_mTimeBetweenFrames = 0;
	_mLookDirection = 0;
}

void Player::Update()
{
	float deltaTime = TIME_MANAGER->GetDeltaTime();

	_mTimeBetweenStates += deltaTime;
	_mTimeBetweenFrames += deltaTime;

	if (INPUT->GetPressedKeys(SDL_SCANCODE_UP)) //up
	{
		_mLookDirection = 2;

		if (!CheckCollisionWithWorld(UP))
		{
			_mRectWorld.y -= SPEED;
		}
	}
	if (INPUT->GetPressedKeys(SDL_SCANCODE_RIGHT)) //right
	{
		_mLookDirection = 3;

		if (!CheckCollisionWithWorld(RIGHT))
		{
			_mRectWorld.x += SPEED;
		}
	}
	else if (INPUT->GetPressedKeys(SDL_SCANCODE_DOWN)) //down
	{
		_mLookDirection = 0;

		if (!CheckCollisionWithWorld(DOWN))
		{
			_mRectWorld.y += SPEED;
		}
	}
	else if (INPUT->GetPressedKeys(SDL_SCANCODE_LEFT)) //left
	{
		_mLookDirection = 1;

		if (!CheckCollisionWithWorld(LEFT))
		{
			_mRectWorld.x -= SPEED;
		}
	}

	//Limits
	if (_mRectWorld.y < 0)
	{
		_mRectWorld.y = 0;
	}
	if (_mRectWorld.x < 0)
	{
		_mRectWorld.x = 0;
	}
	if ((_mRectWorld.x + _mRectWorld.w) > _mWorldSizeW)
	{
		_mRectWorld.x = _mWorldSizeW - _mRectWorld.w;
	}
	if ((_mRectWorld.y + _mRectWorld.h) > _mWorldSizeH)
	{
		_mRectWorld.y = _mWorldSizeH - _mRectWorld.h;
	}

	// P1_IDLE : 0, P1_WALK : 1, P1_BOMB: 2, P1_DIE: 3
	int action = 0;

	if (INPUT->GetPressedKeys(SDL_SCANCODE_SPACE))
	{
		action = 3;
	}
	if (INPUT->GetPressedKeys(SDL_SCANCODE_Z))
	{
		action = 2;
	}
	if (INPUT->GetPressedKeys(SDL_SCANCODE_UP) || INPUT->GetPressedKeys(SDL_SCANCODE_RIGHT) ||
		INPUT->GetPressedKeys(SDL_SCANCODE_DOWN) || INPUT->GetPressedKeys(SDL_SCANCODE_LEFT))
	{
		action = 1;
	}

	if (_mCurrentState == ST_IDLE)
	{
		if (action == 1)
		{
			_mTimeBetweenStates = 0;
			frameCounter = 0;
			walkAnimationSequence[0];
			_mCurrentState = ST_WALK;
			_mTimeBetweenFrames = 0;
		}
		else if (action == 2)
		{
			//
		}
		else if (action == 3)
		{
			_mTimeBetweenStates = 0;
			frameCounter = 0;
			dieAnimationSequence[0];
			_mCurrentState = ST_DIE;
			_mTimeBetweenFrames = 0;
		}
	}
	else if (_mCurrentState == ST_WALK)
	{
		if (_mTimeBetweenFrames >= msPerAnimation[ST_WALK] / framesPerAnimation[ST_WALK])
		{
			_mTimeBetweenFrames = 0;
			frameCounter = (frameCounter + 1) % framesPerAnimation[ST_WALK];
		}
		if (action == 0)
		{
			_mTimeBetweenStates = 0;
			_mCurrentState = ST_IDLE;
			_mTimeBetweenFrames = 0;
		}
		else if (action == 2)
		{
			//
		}
		else if (action == 3)
		{
			_mTimeBetweenStates = 0;
			frameCounter = 0;
			dieAnimationSequence[0];
			_mCurrentState = ST_DIE;
			_mTimeBetweenFrames = 0;
		}
	}
	else if (_mCurrentState == ST_DIE)
	{
		if (_mTimeBetweenFrames >= msPerAnimation[ST_DIE] / framesPerAnimation[ST_DIE])
		{
			_mTimeBetweenFrames = 0;
			++frameCounter;

			if (frameCounter >= framesPerAnimation[ST_DIE])
			{
				frameCounter = framesPerAnimation[ST_DIE] - 1;
			}
		}
		if (frameCounter == 6 && diePhase == 0)
		{
			diePhase = 1;
		}
		if (frameCounter == framesPerAnimation[ST_DIE] - 1 && diePhase == 1)
		{
			_mLife = 0;
		}
	}
}

void Player::Render(int _idCharacterTexture)
{
	int state = _mCurrentState;

	if (state < 0 || state >= 4) return;

	switch (state)
	{
	case ST_IDLE:
	{
		_mRectGraphic.y = spritesPosY[_mLookDirection];
		break;
	}
	case ST_WALK:
	{
		_mRectGraphic.x = spritesPosX[walkAnimationSequence[frameCounter]];
		_mRectGraphic.y = spritesPosY[_mLookDirection];
		break;
	}
	case ST_DIE:
	{
		_mRectGraphic.x = spritesPosX[dieAnimationSequence[frameCounter]];
		_mRectGraphic.y = spritesPosY[4];
		break;
	}
	default:
		break;
	}

	VIDEO->RenderTexture(_idCharacterTexture, _mRectGraphic, _mRectWorld);
}

void Player::SetWorldPointer(Map* _map)
{
	_pCurrentWorld = _map;

	_mWorldSizeW = _pCurrentWorld->GetWidth() * _pCurrentWorld->GetTileWidth();
	_mWorldSizeH = _pCurrentWorld->GetHeight() * _pCurrentWorld->GetTileHeight();
}

bool Player::CheckCollisionWithWorld(int _direction)
{
	if (_direction == UP)
	{
		Point point1(_mRectWorld.x + 8, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()) - SPEED);
		Point point2(_mRectWorld.x + _mRectWorld.w / 2, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()) - SPEED);
		Point point3(_mRectWorld.x + _mRectWorld.w - 12, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()) - SPEED);

		return _pCurrentWorld->IsThereCollisionWithTileMap(point1) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point2) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point3);
	}
	else if (_direction == RIGHT)
	{
		Point point1(_mRectWorld.x + _mRectWorld.w - 12 + SPEED, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()));
		Point point2(_mRectWorld.x + _mRectWorld.w - 12 + SPEED, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()) + (_pCurrentWorld->GetTileHeight() / 2));
		Point point3(_mRectWorld.x + _mRectWorld.w - 12 + SPEED, _mRectWorld.y + _mRectWorld.h - 1);

		return _pCurrentWorld->IsThereCollisionWithTileMap(point1) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point2) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point3);
	}
	else if (_direction == DOWN)
	{
		Point point1(_mRectWorld.x + 8, _mRectWorld.y + _mRectWorld.h + SPEED);
		Point point2(_mRectWorld.x + _mRectWorld.w / 2, _mRectWorld.y + _mRectWorld.h + SPEED);
		Point point3(_mRectWorld.x + _mRectWorld.w - 40, _mRectWorld.y + _mRectWorld.h + SPEED);

		return _pCurrentWorld->IsThereCollisionWithTileMap(point1) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point2) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point3);
	}
	else if (_direction == LEFT)
	{
		Point point1(_mRectWorld.x + 8 - SPEED, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()));
		Point point2(_mRectWorld.x - SPEED, _mRectWorld.y + (_mRectWorld.h - _pCurrentWorld->GetTileHeight()) + (_mRectWorld.h - (_mRectWorld.h - _pCurrentWorld->GetTileHeight()) / 2));
		Point point3(_mRectWorld.x - 12 - SPEED, _mRectWorld.y + _mRectWorld.h - 1);

		return _pCurrentWorld->IsThereCollisionWithTileMap(point1) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point2) ||
			_pCurrentWorld->IsThereCollisionWithTileMap(point3);
	}
}
