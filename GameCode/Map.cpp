#include "Map.h"

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "../SDL/include/SDL.h"

#include "../EngineCode/Defines.h"
#include "../EngineCode/Video.h"
#include "../EngineCode/tinyxml2.h"

#include "Tileset.h"
#include "Camera.h"
#include "Rock.h"

using namespace tinyxml2;


Map::Map(void)
{
	_mWidth = 0;
	_mHeight = 0;
	_mTileWidth = 0;
	_mTileHeight = 0;
	_mMaxWidth = 0;
	_mMaxHeight = 0;
	_mCameraX = 0;
	_mLayers.resize(0);
}

Map::~Map(void)
{

}

void Map::Init(Tileset* _ptrTileset, const char* _file)
{
	const char* tmpPath = _file;

	if (_mDocument.LoadFile(tmpPath) != XML_SUCCESS)
	{
		std::cout << "File could not be loaded! [XML Error]: "
			<< _mDocument.ErrorStr() << std::endl;
	}

	XMLElement* map = _mDocument.FirstChildElement("map");
	{
		int tmp = std::stoi(map->Attribute("width"));
		_mWidth = tmp;
	}
	{
		int tmp = std::stoi(map->Attribute("height"));
		_mHeight = tmp;
	}
	{
		int tmp = std::stoi(map->Attribute("tilewidth"));
		_mTileWidth = tmp;
	}
	{
		int tmp = std::stoi(map->Attribute("tileheight"));
		_mTileHeight = tmp;
	}

	XMLElement* tileset = map->FirstChildElement("tileset");
	{
		int tmp = std::stoi(tileset->Attribute("firstgid"));
		_ptrTileset->SetFirstGrid(tmp);
	}
	{
		int tmp = std::stoi(map->Attribute("tilewidth"));
		_ptrTileset->SetTileWidth(tmp);
	}
	{
		int tmp = std::stoi(map->Attribute("tileheight"));
		_ptrTileset->SetTileHeight(tmp);
	}
	{
		std::string tmp = tileset->Attribute("source");
		_ptrTileset->SetGraphicFileName(tmp);
	}

	// --- Tilemap: Level

	XMLElement* layer = map->FirstChildElement("layer");

	int tmpCounterLayer = 0;

	while (layer != NULL)
	{
		SetNewLayer();

		std::string layerRows;
		layerRows = layer->FirstChildElement("data")->GetText();

		size_t currentPos = 0;
		size_t nextPos = 0;
		size_t br = 0;

		while (nextPos != std::string::npos)
		{
			nextPos = layerRows.find(",", currentPos);
			br = layerRows.find("\n", currentPos);
			if (nextPos != std::string::npos)
			{
				int value = std::stoi(layerRows.substr(currentPos, nextPos - currentPos));
				SetLayerValues(tmpCounterLayer, value);
				currentPos = nextPos + 1;
			}
			else
			{
				int value = std::stoi(layerRows.substr(currentPos, layerRows.size() - currentPos));
				SetLayerValues(tmpCounterLayer, value);
			}
		}

		layer = layer->NextSiblingElement("layer");
		++tmpCounterLayer;
	}

	_mMaxWidth = _mWidth * _mTileWidth;
	_mMaxHeight = _mHeight * _mTileHeight;

	for (int i = 0; i < 35; i++)
	{
		Rock* newRock = new Rock();
		newRock->SetWorldPointer(this);
		_mRocks.push_back(newRock);
	}
	for (int i = 0; i < _mRocks.size(); i++)
	{
		for (int layer = 1; layer < _mLayers.size(); layer++)
		{
			for (int y = 0; y < _mHeight; y++)
			{
				for (int x = 0; x < _mWidth; x++)
				{
					if (((x != 2 && y != 1) &&
						(x != 2 && y != 2) &&
						(x != 2 && y != 3) &&
						(x != 3 && y != 1) &&
						(x != 4 && y != 1)) &&
						(_mLayers[layer][y] != 0))
					{
						bool flag;
						flag = rand() % 1;
						if (flag)
						{
							_mRocks[i]->SetPosXWorld(x * 64);
							_mRocks[i]->SetPosYWorld(y * 64);
						}
					}
				}
			}
		}
	}
}

void Map::Update()
{
	// Rocks
	for (auto it = _mRocks.begin(); it != _mRocks.end(); )
	{
		(*it)->Update(this);

		if ((*it)->GetRockState() && (*it)->GetEliminateFlag())
		{
			delete* it;
			it = _mRocks.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Map::Render(Camera* _ptrCamera, int _idTilesetTexture)
{
	/*for (int layer = 0; layer < _mLayers.size(); layer++)
	{
		for (int y = 0; y < _mHeight; y++)
		{
			for (int x = 0; x < _mWidth; x++)
			{
				std::cout << _mLayers.at(layer)[y * _mWidth + x] << ",";
			}
			std::cout << std::endl;
		}
		std::cout << "\n" << std::endl;
	}*/

	int tmpPosX = 0;
	int tmpPosY = 0;

	for (int layer = 0; layer < _mLayers.size(); layer++)
	{
		for (int y = 0; y < _mHeight; y++)
		{
			for (int x = 0; x < _mWidth; x++)
			{
				SDL_Rect rectScreen;
				SDL_Rect rectWorld;

				rectWorld.x = x * _mTileWidth - _mCameraX;
				rectWorld.y = y * _mTileHeight;
				rectWorld.w = _mTileWidth;
				rectWorld.h = _mTileHeight;

				if (rectWorld.x + _mTileWidth >= 0 && rectWorld.x <= _ptrCamera->GetWidth())
				{
					if (_mLayers.at(layer)[y * _mWidth + x] != 0)
					{
						tmpPosX = (_mLayers.at(layer)[y * _mWidth + x] - 1) % 5;
						tmpPosY = (_mLayers.at(layer)[y * _mWidth + x] - 1) / 5;

						rectScreen.x = tmpPosX * _mTileWidth;
						rectScreen.y = tmpPosY * _mTileHeight;
						rectScreen.w = _mTileWidth;
						rectScreen.h = _mTileHeight;

						VIDEO->RenderTexture(_idTilesetTexture, rectScreen, rectWorld);
					}
				}
			}
		}
	}
}

void Map::SetNewLayer()
{
	_mLayers.push_back(std::vector<int>());
}

void Map::SetLayerValues(int _layer, int _value)
{
	_mLayers.at(_layer).push_back(_value);
}

int Map::GetLayerValues(int _layer, int _col, int _row) const
{
	return _mLayers.at(_layer)[_row * _mWidth + _col];
}

bool Map::IsThereCollisionWithTileMap(Point _point)
{
	int tileX = _point.x / _mTileWidth;
	int tileY = _point.y / _mTileHeight;

	int tileID = GetLayerValues(1, tileX, tileY);

	return tileID != 0;
}

/*
int firstTileX = static_cast<int>(GAME_CAMERA->GetPosX() / _mTileWidth);
int firstTileY = static_cast<int>(GAME_CAMERA->GetPosY() / _mTileHeight);
int lastTileX = static_cast<int>((GAME_CAMERA->GetPosX() + GAME_CAMERA->GetWidth()) / _mTileWidth);
int lastTileY = static_cast<int>((GAME_CAMERA->GetPosY() + GAME_CAMERA->GetHeight()) / _mTileHeight);

if (lastTileX >= _mWidth)
{
	lastTileX = _mWidth - 1;
}
if (lastTileY >= _mHeight)
{
	lastTileY = _mHeight - 1;
}

int posScreenWidth = 0;
int posScreenHeight = 0;
int posXTileset = 0;
int posYTileset = 0;

for (int layer = 0; layer < _mLayers.size(); layer++)
{
	for (int y = firstTileY; y <= lastTileY; ++y)
	{
		for (int x = firstTileX; x <= lastTileX; ++x)
		{
			posScreenWidth = x * _mTileWidth - static_cast<int>(GAME_CAMERA->GetPosX());
			posScreenHeight = y * _mTileHeight - static_cast<int>(GAME_CAMERA->GetPosY());

			if (_mLayers.at(layer)[y * _mWidth + x] >= 0)
			{
				posXTileset = ((_mLayers.at(layer)[y * _mWidth + x] - 1) % 5) * _mTileWidth;
				posYTileset = ((_mLayers.at(layer)[y * _mWidth + x] - 1) / 5) * _mTileHeight;

				VIDEO->RenderTexture(id_texture, posXTileset, posYTileset, posScreenWidth, posScreenHeight, _mTileWidth, _mTileHeight, _mTileWidth, _mTileHeight);
			}
		}
	}
}
*/
