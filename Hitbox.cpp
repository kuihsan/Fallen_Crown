#include "Hitbox.h"

// Creates a default hitbox object with no specified width, height or offsets.
Hitbox::Hitbox(){}

// Creates a hitbox object with specified width, height, left and right offsets, but no top or bottom offsets.
Hitbox::Hitbox(int width, int height, int _off_x_l, int _off_x_r): Hitbox(width, height, _off_x_l, _off_x_r, 0, 0)
{
}

// Creates a hitbox object with specified width, height, left and right offsets, and top and bottom offsets.
Hitbox::Hitbox(int width, int height, int _off_x_l, int _off_x_r, int _off_y_t, int _off_y_b):
	off_x_l(_off_x_l), off_x_r(_off_x_r), off_y_t(_off_y_t), off_y_b(_off_y_b)
{
	// Sets the size of the hitbox, factoring in the left, right, top and bottom offsets.
	setSize(sf::Vector2f(width - off_x_l - off_x_r, height));
}


Hitbox::~Hitbox()
{
}

// Updates the position of the hitbox, based on the position of the sprite and whether the sprite is flipped or not.
void Hitbox::update_position(sf::FloatRect sprite_rect, bool is_flipped)
{
	sf::Vector2f pos(sprite_rect.left, sprite_rect.top);// Sets the position of the hitbox, factoring in the left, right, top and bottom offsets.
	if (is_flipped)
	{
		pos.x += off_x_r;
	}
	else
	{
		pos.x += off_x_l;
	}
	setPosition(pos);
}
