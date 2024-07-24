#pragma once
#include "Enemy.h"

class Mushroom : public Enemy
{
public:
	Mushroom(AssetManager* _am, sf::Vector2f pos);
	~Mushroom();
	const int type = 0;
	void update_tex();
	int mspeed = 3;
};

