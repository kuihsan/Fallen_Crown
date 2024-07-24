#include "Mushroom.h"



Mushroom::Mushroom(AssetManager* _am, sf::Vector2f pos): Enemy(_am, pos)
{
	current_sprite.setTexture(am->enemy1_idle[0]);
	x_speed = mspeed;
	hitbox = Hitbox(current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height, 5, 5);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
}

Mushroom::~Mushroom()
{
}

void Mushroom::update_tex()
{
	if (killed) 
		current_sprite.setTexture(am->enemy1_hit);
	else
	{
		anim_counter++;
		if (anim_counter > max_anim_delay)
		{
			current_sprite.setTexture(am->enemy1_idle[anim_index]);
			anim_index++;
			anim_index %= 8;
			anim_counter = 0;
		}
	}
}
