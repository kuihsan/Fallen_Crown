#include "Enemy.h"
#include "Screen_1.h"

//This constructor initializes an enemy object by taking in an AssetManager object and a position vector as arguments.
Enemy::Enemy(AssetManager* _am, sf::Vector2f(pos)): am(_am)
{
	current_sprite.setPosition(pos);//The current_sprite of the enemy is set to the given position
	current_sprite.setScale(0.1, 0.1);// //The current_sprite's scale is set to 0.1 on both x and y axis
}


Enemy::~Enemy()
{
}

void Enemy::flip_correct() //to let enemy flipped the correct way
{
	if (x_speed > 0 && is_flipped)//if x speed positive and is flipped
	{
		is_flipped = !is_flipped;// unflip
		auto rect = current_sprite.getTextureRect();// getting the current texture rect of the enemy sprite,
		rect.left = rect.width; 
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
	}
	else if (x_speed < 0 && !is_flipped)
	{
		is_flipped = !is_flipped;

		auto rect = current_sprite.getTextureRect();
		rect.left = 0;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
	}
}
//By using a reference, the Enemy class can directly access and modify the properties of the Screen_1 class without having to create a new instance of it.
void Enemy::update(Screen_1& screen)
{
	//Let gravity change y_speed
	y_speed += (g*am->seconds_pr_frame);
	//Make sure sprite direction is correct.
	if(!killed) flip_correct();
	//Get current_tile
	update_current_tiles(screen);
	if(!killed) check_map_collision_x(screen);
	move_x(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
	update_current_tiles(screen);
	check_map_collision_y(screen);
	move_y(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);

	update_tex();
}

void Enemy::update_current_tiles(Screen_1& screen)
{
	current_tile_x_left = (((hitbox.getGlobalBounds().left) - screen.map.getPosition().x) / am->tile_size);
	current_tile_x_right = (((hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width) - screen.map.getPosition().x) / am->tile_size);
	current_tile_y_top = (((hitbox.getGlobalBounds().top) - screen.map.getPosition().y) / am->tile_size);
	current_tile_y_bottom = (((hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height) - screen.map.getPosition().y) / am->tile_size);
}

void Enemy::move_x(Screen_1& screen)
{
	current_sprite.move(x_speed, 0);// movement of enemies on x axis
}

void Enemy::move_y(Screen_1& screen)
{
	current_sprite.move(0, y_speed);// movement of enemies on y axis
}

void Enemy::check_map_collision_x(Screen_1& screen)
{
	//Get closest obstacle positive x_direction
	if (!screen.check_map_void(current_tile_x_right, current_tile_y_bottom) ||
		 screen.check_map_void(current_tile_x_right, current_tile_y_bottom + 1))
	{
		x_speed *= -1; // speed set to times -1 which is go to other way
	}
	//Get closest obstacle negative x_direction;
	else if (x_speed < 0)
	{
		if (!screen.check_map_void(current_tile_x_left, current_tile_y_bottom) ||
			 screen.check_map_void(current_tile_x_left, current_tile_y_bottom +1))
		{
			x_speed *= -1;// speed set to times -1 which is go to other way
		}
	}
}

void Enemy::check_map_collision_y(Screen_1& screen)
{
	//Get closest obstacle positive y_direction;
	if (y_speed > 0)
	{
		for (int i = current_tile_x_left; i <= current_tile_x_right; i++)
		{
			if (!screen.check_map_void(i, current_tile_y_bottom + 1))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(i, current_tile_y_bottom + 1).y - (hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height);
				y_speed = (y_speed < dist_to_obstacle) ? y_speed : (dist_to_obstacle - 1);
				if (dist_to_obstacle < 2) y_speed = 0;
			}
		}
	}
	//Get closest obstacle neg x_dir
	else if (y_speed < 0)
	{
		for (int i = current_tile_x_left; i <= current_tile_x_right; i++)
		{
			if (!screen.check_map_void(i, current_tile_y_top - 1))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(i, current_tile_y_top - 1).y + am->tile_size - (hitbox.getGlobalBounds().top);
				y_speed = (y_speed > dist_to_obstacle) ? y_speed : (dist_to_obstacle + 1);
			}
		}
	}
}
