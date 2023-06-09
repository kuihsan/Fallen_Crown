#pragma once
#include <SFML/Graphics.hpp>
class Hitbox : public sf::RectangleShape
{
public:
	Hitbox();
	Hitbox(int width, int height, int _off_x_l, int _off_x_r);
	Hitbox(int width, int height, int _off_x_l, int _off_x_r, int _off_y_t, int _off_y_b);
	~Hitbox();
	void update_position(sf::FloatRect sprite_rect, bool is_flipped);

	int off_x_l{};
	int off_x_r{};
	int off_y_t{};
	int off_y_b{};

};

