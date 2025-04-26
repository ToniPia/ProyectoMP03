#ifndef MAP_H
#define MAP_H

#include <vector>

#include "../EngineCode/Defines.h"
#include "../EngineCode/Helpers.h"
#include "../EngineCode/tinyxml2.h"

class Tileset;
class Camera;

using namespace tinyxml2;


//! Map class
/*
	Represents the playable area in the game. (the area of the current level)
*/
class Map
{
public:
	Map(void);
	~Map(void);

	void	Init(Tileset* _ptrTileset, const char* _file);
	void	Update();
	void	Render(Camera* _ptrCamera, int _idTilesetTexture);

	void	SetWidth(int _value) { _mWidth = _value; };
	int		GetWidth() { return _mWidth; };
	void	SetHeight(int _value) { _mHeight = _value; };
	int		GetHeight() { return _mHeight; };
	void	SetTileWidth(int _value) { _mTileWidth = _value; };
	int		GetTileWidth() { return _mTileWidth; };
	void	SetTileHeight(int _value) { _mTileHeight = _value; };
	int		GetTileHeight() { return _mTileHeight; };
	void	SetMaxWidth(int _value) { _mMaxWidth = _value; };
	int		GetMaxWidth() { return _mMaxWidth; };
	void	SetMaxHeight(int _value) { _mMaxHeight = _value; };
	int		GetMaxHeight() { return _mMaxHeight; };

	void	SetNewLayer();
	void	SetLayerValues(int _layer, int _value);
	int		GetLayerValues(int _layer, int _col, int _row) const;

	bool	IsThereCollisionWithTileMap(Point _point);

	void	SetRenderInitX(int _value) { _mCameraX = _value; };

private:
	int				_mWidth, _mHeight;
	int				_mTileWidth, _mTileHeight;
	int				_mMaxWidth, _mMaxHeight;
	int				_mCameraX;

	XMLDocument		_mDocument;		/*< XMLDocument object. Used to load the map from the XML file */

	std::vector<std::vector<int>>	_mLayers;
};


#endif

