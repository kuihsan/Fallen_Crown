#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
class Tile
{
public:
	Tile();
	Tile(int _tile_ID, AssetManager* _am);
	~Tile();
	int tile_ID;
	sf::RectangleShape tile_shape;
	int tile_size;
	AssetManager* am;
};