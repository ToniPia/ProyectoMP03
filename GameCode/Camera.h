#ifndef CAMERA_H
#define CAMERA_H

class Map;
class Player;


//! Camera class
/*
	Represents the field of view of the game.
*/
class Camera
{
public:
	Camera(void);
	~Camera(void);

	void	Init();
	void	Update(Map* _ptrMap, Player* _ptrPlayer);

	void	SetPosX(int _value) { _mPosX = _value; };
	int		GetPosX() { return _mPosX; };
	void	SetPosY(int _value) { _mPosY = _value; };
	int		GetPosY() { return _mPosY; };
	void	SetWidth(int _value) { _mWidth = _value; };
	int		GetWidth() { return _mWidth; };
	void	SetHeight(int _value) { _mHeight = _value; };
	int		GetHeight() { return _mHeight; };

private:
	int		_mPosX, _mPosY;
	int		_mWidth, _mHeight;
};

#endif

