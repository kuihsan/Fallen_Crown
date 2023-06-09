#include "Tile.h"

Tile::Tile(){}

// Initialize a Tile object with the given tile ID and AssetManager pointer
Tile::Tile(int _tile_ID, AssetManager* _am): tile_ID(_tile_ID), am(_am)
{
	// Initialize a Tile object with the given tile ID and AssetManager pointer
	tile_shape.setSize(sf::Vector2f(tile_size, tile_size));
	// Set the texture of the tile shape to the tile texture from the AssetManager
	tile_shape.setTexture(&am->tiles);
	// Set the texture rectangle of the tile shape to the correct portion of the tile texture
	int x = tile_size; //64
	int y = tile_size;//64
	tile_shape.setTextureRect(sf::IntRect(x, y, tile_size, tile_size));
	// based on the tile ID. The exact calculation for this may depend on how the tile texture is laid out.
}


Tile::~Tile()
{
}
