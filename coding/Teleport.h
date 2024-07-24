#pragma once
#include "AssetManager.h"
class Teleport
{
public:
	Teleport();
	Teleport(AssetManager* _am);
	~Teleport();

	void set_pos(sf::Vector2f pos);
	sf::Sprite current_sprite;
	void update();

private:
	void update_tex();
	AssetManager* am;
	int anim_index = 0;
};
