#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "AssetManager.h"
class Screen_1;

class Enemy
{
public:
	Enemy(AssetManager* _am, sf::Vector2f(pos));
	~Enemy();
	Hitbox hitbox;
	sf::Sprite current_sprite;
	bool is_flipped = true;
	AssetManager* am;
	double x_speed = 0;
	double y_speed = 0;
	double y_acc = 0;
	double g = 120;
	double x_acc = 0;
	bool killed = false;
	virtual void update(Screen_1& screen);
	int anim_index = 0;
	int anim_counter = 0;
	int max_anim_delay = 3;

protected:
	virtual void flip_correct();
	virtual void update_tex() = 0;
	virtual void update_current_tiles(Screen_1& screen);
	int current_tile_x_left;
	int current_tile_x_right;
	int current_tile_y_top;
	int current_tile_y_bottom;
	virtual void check_map_collision_x(Screen_1& screen);
	virtual void check_map_collision_y(Screen_1& screen);
	virtual void move_x(Screen_1& screen);
	virtual void move_y(Screen_1& screen);
};

