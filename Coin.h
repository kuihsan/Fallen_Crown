#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"


class Coin
{
public:
	Coin();
	Coin(AssetManager* _am, sf::Vector2f pos);
	~Coin();

	sf::Sprite current_sprite;
	void update();
	void reset_statics();
	int get_type() { return type; }
private:
	static int count;
	int type;
	static const int no_of_tiles = 5;
	static const int anim_delay = 4;;
	int current_anim_index = 0;
	int current_anim_delay = 0;

	void update_tex();
	AssetManager* am;
};

