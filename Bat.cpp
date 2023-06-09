#include "Bat.h"
#include "Screen_1.h"
#include"Mushroom.h"

Bat::Bat(AssetManager* _am, sf::Vector2f pos, sf::Vector2i _init_pos): Enemy(_am, pos), init_pos(_init_pos)
{
	//sets current sprite's texture to the first texture in the enemy2 vector of the AssetManager
	current_sprite.setTexture(am->enemy2[0]);
	// set the x_speed and y_speed to specific value
	x_speed = bspeed;
	y_speed = 0.5;
	hitbox = Hitbox(current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height, 14, 5, 11, 9);
	// updates the position of hitbox
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
}

Bat::~Bat()
{
}

void Bat::update(Screen_1& screen)
{
	//Let gravity change y_speed if killed
	if(killed) y_speed += (g*am->seconds_pr_frame);
	//Make sure sprite direction is correct.
	if (!killed) flip_correct();
	//Get current_tile
	update_current_tiles(screen);
	if (!killed) check_map_collision_x(screen);
	move_x(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
	update_current_tiles(screen);
	if(!killed)check_map_collision_y(screen);
	move_y(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);

	update_tex();
}

void Bat::update_tex()
{// flip the bat upside down if killed 
	if (killed) current_sprite.setRotation(180);
	else
	{
		anim_counter++;
		if (anim_counter > max_anim_delay)
		{
			// updates the sprite's texture
			current_sprite.setTexture(am->enemy2[anim_index]);
			anim_index++;
			anim_index %= 8; 
			//used to keep the animation index within the range. If the value of anim_index exceeds maximum limit which is 8, 
			//it will be set back to 0 This allows the animation to loop seamlessly.
			anim_counter = 0;
		}
	}
}

void Bat::flip_correct()
{
	if (x_speed < 0 && is_flipped)
	{
		// flips the sprite if the x_speed is negative and the sprite is flipped
		is_flipped = !is_flipped;
		auto rect = current_sprite.getTextureRect();
		rect.left = rect.width;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
	}
	else if (x_speed > 0 && !is_flipped)
	{
		// flips the sprite if the x_speed is positive and the sprite is not flipped
		is_flipped = !is_flipped;
		auto rect = current_sprite.getTextureRect();
		rect.left = 0;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
	}
}

void Bat::check_map_collision_x(Screen_1& screen)
{
	//Get closest obstacle pos x_dir
	if (x_speed > 0)
	{
		if (!screen.check_map_void(current_tile_x_right, current_tile_y_bottom) ||
			current_tile_x_right - init_pos.x >= limits.x)
		{
			x_speed *= -1;
		}
	}
	//Get closest obstacle neg x_dir;
	else if (x_speed < 0)
	{
		if (!screen.check_map_void(current_tile_x_left, current_tile_y_bottom) ||
			abs(current_tile_x_left - init_pos.x) >= limits.x)
		{
			x_speed *= -1;
		}
	}
}

void Bat::check_map_collision_y(Screen_1& screen)
{
	//Get closest obstacle pos y_dir;
	if (y_speed > 0)
	{

		if (!screen.check_map_void(current_tile_x_right, current_tile_y_bottom) ||
			abs(current_tile_y_bottom - init_pos.y) >= limits.y)
		{
			y_speed *= -1;
		}
	}
	//Get closest obstacle neg x_dir
	else if (y_speed < 0)
	{
		if (!screen.check_map_void(current_tile_x_left, current_tile_y_top) ||
			abs(current_tile_y_top - init_pos.y) >= limits.y)
		{

			y_speed *= -1;
		}
	}
}
