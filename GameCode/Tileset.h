#ifndef TILESET_H
#define TILESET_H

#include <string>


//! Tileset class
/*
	Represents the tilemap info for any level of the game.
*/
class Tileset
{
public:
	Tileset(void);
	~Tileset(void);

	void			SetFirstGrid(int _value) { _mFirstGrid = _value; };
	int				GetFirstGrid() { return _mFirstGrid; };
	void			SetTileWidth(int _value) { _mTileWidth = _value; };
	int				GetTileWidth() { return _mTileWidth; };
	void			SetTileHeight(int _value) { _mTileHeight = _value; };
	int				GetTileHeight() { return _mTileHeight; };
	void			SetGraphicFileName(std::string _value) { _mGraphicFileName = _value; };
	std::string		GetGraphicFileName() { return _mGraphicFileName; };
	void			SetTextureId(int _value) { _mTextureID = _value; };
	int				GetTextureId() { return _mTextureID; };

private:
	int				_mFirstGrid;
	int				_mTileWidth;
	int				_mTileHeight;
	std::string		_mGraphicFileName;
	int				_mTextureID;
};

#endif

