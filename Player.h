#pragma once
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include <iostream>

class Screen_1;
class Player
{
public:
	Player(AssetManager* _am);
	Player(const Player& p);
	~Player();
	Hitbox hitbox;
	AssetManager* am;
	sf::Sprite current_sprite;
	bool is_flipped = false;
	bool killed = false;
	double x_speed = 0;
	double y_speed = 0;
	double g = 120;
	bool casting = false;
	int anim_index = 0;
	int anim_count = 0;
	void update(Screen_1& screen);

private:
	void flip_correct();
	void update_tex();
	void update_current_tiles(Screen_1& screen);
	void check_map_collision_x(Screen_1& screen);
	void check_map_collision_y(Screen_1& screen);
	void check_out_of_bounds(Screen_1& screen);
	void anim_death();
	void check_damage(Screen_1& screen);
	void check_coin(Screen_1& screen);
	void check_teleport(Screen_1& screen);
	void move_x(Screen_1& screen);
	void move_y(Screen_1& screen);
	int current_tile_x_left;
	int current_tile_x_right;
	int current_tile_y_top;
	int current_tile_y_bottom;
};

