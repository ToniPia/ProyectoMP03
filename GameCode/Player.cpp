#include "Player.h"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/TimeManager.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/Input.h"

#include "Map.h"
#include "Camera.h"


Player::Player(void)
{
	_mLife = 0;
	_mCurrentState = ST_IDLE;
	_mCurrentAnimationIndex = 0;
}

Player::~Player(void)
{

}

void Player::Init()
{
	SDL_Rect rectGraphicInit = { 0, 0, 88, 88 };
	SDL_Rect rectWorldInit = { 116, 40, 88, 88 };
	SetRectGraphic(rectGraphicInit);
	SetRectWorld(rectWorldInit);

	SetCurrentAnimation(0);
	SetTimeBetweenLastFrame(0);
	SetCurrentSprite(0);
	SetLookDirection(0);


	_mLife = 1;
	_mCurrentState = ST_IDLE;
	_mCurrentAnimationIndex = -1;

	AddNewAnimation(Animation{ 4, 200, 0, 0, 88, 88 });
	AddNewAnimation(Animation{ 4, 200, 0, 88, 88, 88 });
	AddNewAnimation(Animation{ 4, 200, 0, 176, 88, 88 });
	AddNewAnimation(Animation{ 4, 200, 0, 264, 88, 88 });
	AddNewAnimation(Animation{ 9, 200, 0, 352, 88, 88 });
}

void Player::Update()
{
	int deltaTime = TIME_MANAGER->GetDeltaTime();
	bool isMoving = false;

	// Detectar dirección y priorizar en orden: UP > DOWN > LEFT > RIGHT
	if (INPUT->GetPressedKeys(SDL_SCANCODE_UP))
	{
		SetLookDirection(2);
		_mCurrentState = ST_WALK;
		isMoving = true;
		SetCurrentAnimation(2);

		if (!CheckCollisionWithWorld(UP))//|| TrySlideIfBlocked(UP))
			SetPosYWorld(GetPosYWorld() - SPEED);
	}
	else if (INPUT->GetPressedKeys(SDL_SCANCODE_DOWN))
	{
		SetLookDirection(0);
		_mCurrentState = ST_WALK;
		isMoving = true;
		SetCurrentAnimation(0);

		if (!CheckCollisionWithWorld(DOWN))//|| TrySlideIfBlocked(DOWN))
			SetPosYWorld(GetPosYWorld() + SPEED);
	}
	else if (INPUT->GetPressedKeys(SDL_SCANCODE_LEFT))
	{
		SetLookDirection(1);
		_mCurrentState = ST_WALK;
		isMoving = true;
		SetCurrentAnimation(1);

		if (!CheckCollisionWithWorld(LEFT))//|| TrySlideIfBlocked(LEFT))
			SetPosXWorld(GetPosXWorld() - SPEED);
	}
	else if (INPUT->GetPressedKeys(SDL_SCANCODE_RIGHT))
	{
		SetLookDirection(3);
		_mCurrentState = ST_WALK;
		isMoving = true;
		SetCurrentAnimation(3);

		if (!CheckCollisionWithWorld(RIGHT))//|| TrySlideIfBlocked(RIGHT))
			SetPosXWorld(GetPosXWorld() + SPEED);
	}
	else
	{
		_mCurrentState = ST_IDLE;
	}

	// Animaciones
	if (_mCurrentState == ST_WALK)
	{
		SetTimeBetweenLastFrame(GetTimeBetweenLastFrame() + deltaTime);

		if (GetTimeBetweenLastFrame() > GetAnimationsVector()[GetCurrentAnimation()].msPerAnimation)
		{
			SetTimeBetweenLastFrame(0);
			SetCurrentSprite((GetCurrentSprite() + 1) % GetAnimationsVector()[GetCurrentAnimation()].framesPerAnimation);
		}
	}

	Entity::Update(GetRectWorld());
}

void Player::Render(int _idCharacterTexture, Camera* _ptrCamera)
{
	int state = _mCurrentState;

	if (state < 0 || state >= 4) return;

	switch (state)
	{
	case ST_IDLE:
	{
		SetPosXGraphic(0);
		SetPosYGraphic(GetAnimationsVector()[GetCurrentAnimation()].spritePosY);
		break;
	}
	case ST_WALK:
	{
		SetPosXGraphic(GetAnimationsVector()[GetCurrentAnimation()].spritesPosX + GetAnimationsVector()[GetCurrentAnimation()].spriteWidth * GetCurrentSprite());
		SetPosYGraphic(GetAnimationsVector()[GetCurrentAnimation()].spritePosY);
		break;
	}
	case ST_DIE:
	{
		SetPosXGraphic(GetAnimationsVector()[GetCurrentAnimation()].spritesPosX + GetAnimationsVector()[GetCurrentAnimation()].spriteWidth * GetCurrentSprite());
		SetPosYGraphic(GetAnimationsVector()[GetCurrentAnimation()].spritePosY);
		break;
	}
	default:
		break;
	}

	SDL_Rect renderRect = {
		GetPosXWorld() - _ptrCamera->GetPosX(),
		GetPosYWorld() - _ptrCamera->GetPosY(),
		GetWidthWorld(),
		GetHeightWorld()
	};

	Entity::Render(_idCharacterTexture, GetRectGraphic(), renderRect);

	/*SDL_SetRenderDrawColor(VIDEO->GetScreenRenderer(), 255, 0, 0, 255);
	SDL_Rect box = GetCollisionBox();
	SDL_RenderDrawRect(VIDEO->GetScreenRenderer(), &box);*/
}

/*
bool Player::TrySlideIfBlocked(int _direction)
{
	SDL_Rect collisionBox = GetCollisionBox();
	// Desplazamiento en número de casillas del personaje para comprobar de nuevo si colisiona
	const int SLIDE_AMOUNT = 4;

	// Centro de la colisión del jugador
	int playerCenterX = collisionBox.x + collisionBox.w / 2;
	int playerCenterY = collisionBox.y + collisionBox.h / 2;

	// Coordenadas del tile en el que está el centro del jugador
	int tileSizeW = GetCurrentWorld()->GetTileWidth();
	int tileSizeH = GetCurrentWorld()->GetTileHeight();

	int tileX = playerCenterX / tileSizeW;
	int tileY = playerCenterY / tileSizeH;

	// Posición real del centro de ese tile
	int tileCenterX = tileX * tileSizeW + tileSizeW / 2;
	int tileCenterY = tileY * tileSizeH + tileSizeH / 2;

	const int EDGE_THRESHOLD = 12; // Cuánto más cerca del borde que del centro para considerarlo esquina

	if (_direction == RIGHT || _direction == LEFT)
	{
		// Solo desliza si el centro Y está alejado del centro del tile
		int dy = abs(playerCenterY - tileCenterY);
		if (dy < EDGE_THRESHOLD)
			return false;

		// Intentar deslizar
		Point upperCorner = (_direction == RIGHT) ?
			Point(collisionBox.x + collisionBox.w + SPEED, collisionBox.y - 1) :
			Point(collisionBox.x - SPEED, collisionBox.y - 1);
		Point lowerCorner = (_direction == RIGHT) ?
			Point(collisionBox.x + collisionBox.w + SPEED, collisionBox.y + collisionBox.h + 1) :
			Point(collisionBox.x - SPEED, collisionBox.y + collisionBox.h + 1);

		if (!GetCurrentWorld()->IsThereCollisionWithTileMap(upperCorner)) {
			SetPosYWorld(GetPosYWorld() - SLIDE_AMOUNT);
			return true;
		}
		else if (!GetCurrentWorld()->IsThereCollisionWithTileMap(lowerCorner)) {
			SetPosYWorld(GetPosYWorld() + SLIDE_AMOUNT);
			return true;
		}
	}
	else if (_direction == UP || _direction == DOWN)
	{
		// Solo desliza si el centro X está alejado del centro del tile
		int dx = abs(playerCenterX - tileCenterX);
		if (dx < EDGE_THRESHOLD)
			return false;

		Point leftCorner = (_direction == DOWN) ?
			Point(collisionBox.x - 1, collisionBox.y + collisionBox.h + SPEED) :
			Point(collisionBox.x - 1, collisionBox.y - SPEED);
		Point rightCorner = (_direction == DOWN) ?
			Point(collisionBox.x + collisionBox.w + 1, collisionBox.y + collisionBox.h + SPEED) :
			Point(collisionBox.x + collisionBox.w + 1, collisionBox.y - SPEED);

		if (!GetCurrentWorld()->IsThereCollisionWithTileMap(leftCorner)) {
			SetPosXWorld(GetPosXWorld() - SLIDE_AMOUNT);
			return true;
		}
		else if (!GetCurrentWorld()->IsThereCollisionWithTileMap(rightCorner)) {
			SetPosXWorld(GetPosXWorld() + SLIDE_AMOUNT);
			return true;
		}
	}

	return false;
}
*/
