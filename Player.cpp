#include "Player.h"
#include "Screen_1.h"

Player::Player(AssetManager* _am): am(_am)
//This is the constructor of the Player class. It takes a pointer to an 
//AssetManager object as an argument and it initializes the member variable am and sets it equal to the input pointer _am.
{
	//Set the texture of the player sprite to the idle texture from the AssetManager
	current_sprite.setTexture(am->player_idle);
	//Set the scale of the sprite to be smaller
	current_sprite.setScale(0.2, 0.2);
	//Set the initial position of the sprite
	current_sprite.setPosition(0, 50);

	//Create a hitbox for the player, with the width and height of the sprite, and the offsets from the sprite's top left corner.
	hitbox = Hitbox(current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height, 15, 36);
	//Update the position of the hitbox
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
}

Player::Player(const Player& p): Player(p.am){}
//This is the copy constructor for the Player class.
//It initializes the new Player object with the same AssetManager pointer
//as the Player object that was passed in as an argument.The "Player(p.am)" 
//is calling the constructor again with the AssetManager pointer from the passed in object.
//This is used to create a new object with the same properties as an existing object.

Player::~Player()
{
}

void Player::update(Screen_1& screen)
{
	//Let gravity change y_speed
	y_speed += (g*am->seconds_pr_frame);
	//Make sure sprite direction is correct.
	flip_correct();
	update_current_tiles(screen);
	check_map_collision_x(screen);
	move_x(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
	update_current_tiles(screen);
	check_map_collision_y(screen);
	move_y(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);

	//Check a bunch of stuff if player isnt dead, and level isn't cleared
	//If the player isn't killed and level isn't cleared, update the texture 
	//by calling update_tex() function, check out of bounds, check damage, 
	//check coins, and check teleport by calling those respective functions.
	if (!killed && !screen.exit && !screen.level_cleared)
	{
		//Update texture to get proper animation
		update_tex();
		check_out_of_bounds(screen);
		check_damage(screen);
		check_coin(screen);
		check_teleport(screen);
	}
	//Change the sprites for death scene
	if(killed) anim_death();

}

void Player::check_out_of_bounds(Screen_1& screen)// if the player fall
{
	auto rect = current_sprite.getGlobalBounds();
	if (rect.top > 20 * 64 || screen.status_bar.time == 0)
	{
		am->soundfall.play();
		if (screen.status_bar.lives == 0) am->soundgameover.play();
		killed = true;
		return;
	}
}

void Player::move_x(Screen_1& screen)
{
	//Move screen by character movement
	if (((x_speed > 0 && hitbox.getGlobalBounds().left > am->view->getCenter().x) 
		|| (x_speed < 0 && hitbox.getGlobalBounds().left < am->view->getCenter().x /*- 100)*/)))
	{
		am->view->move(x_speed, 0);
		screen.back_map.move(x_speed*(0.7), 0);
	}
	//Move sprite and update hitbox
	current_sprite.move(x_speed, 0);
}

void Player::move_y(Screen_1& screen)
{
	current_sprite.move(0, y_speed);
}

void Player::check_map_collision_x(Screen_1& screen)
{
	//Get closest obstacle pos x_dir
	if (x_speed > 0)
	{
		for (int i = current_tile_y_top; i <= current_tile_y_bottom; i++)
		{
			if (!screen.check_map_void(current_tile_x_right + 1, i))
			{
			double dist_to_obstacle = screen.get_cord_of_tile(current_tile_x_right + 1, i).x - 
			(hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width);
			x_speed = (x_speed <= dist_to_obstacle) ? x_speed : (dist_to_obstacle - 1);
			}
		}
	}
	//Get closest obstacle neg x_dir;
	else if (x_speed < 0)
	{
		for (int i = current_tile_y_top; i <= current_tile_y_bottom; i++)
		{
			if (!screen.check_map_void(current_tile_x_left - 1, i))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(current_tile_x_left + -1, i).x + am->tile_size - hitbox.getGlobalBounds().left;
				x_speed = (x_speed > dist_to_obstacle) ? x_speed : (dist_to_obstacle + 1);
			}
		}
	}
}

void Player::check_map_collision_y(Screen_1& screen)
{
	//Get closest obstacle pos y_dir;
	if (y_speed > 0)
	{
		for (int i = current_tile_x_left; i <= current_tile_x_right; i++)
		{
			if (!screen.check_map_void(i, current_tile_y_bottom + 1))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(i, current_tile_y_bottom + 1).y - 
				(hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height);
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
				double dist_to_obstacle = screen.get_cord_of_tile(i, current_tile_y_top - 1).y + 
				am->tile_size - (hitbox.getGlobalBounds().top);
				y_speed = (y_speed > dist_to_obstacle) ? y_speed : (dist_to_obstacle + 1);
			}
		}
	}
}

//Make sure player sprite is facing direction of movement
void Player::flip_correct()
{
	if (x_speed < 0 && !is_flipped) // if the player is moving left and the sprite is not flipped
	{
		is_flipped = !is_flipped; // sets the is_flipped variable to true
		auto rect = current_sprite.getTextureRect(); // gets the current texture rectangle of the sprite
		rect.left = rect.width; // sets the left side of the rectangle to the width of the rectangle
		rect.width = -rect.width; // inverts the width of the rectangle
		current_sprite.setTextureRect(rect); // sets the new texture rectangle to the sprite
		current_sprite.move(-hitbox.off_x_l - 3, 0); // moves the sprite left by the hitbox offset and an additional 3 pixels
	}
	else if (x_speed > 0 && is_flipped) // if the player is moving right and the sprite is flipped
	{
		is_flipped = !is_flipped; // sets the is_flipped variable to false
		auto rect = current_sprite.getTextureRect(); // gets the current texture rectangle of the sprite
		rect.left = 0; // sets the left side of the rectangle to 0
		rect.width = -rect.width; // inverts the width of the rectangle
		current_sprite.setTextureRect(rect); // sets the new texture rectangle to the sprite
		current_sprite.move(hitbox.off_x_l + 3, 0); // moves the sprite right by the hitbox offset and an additional 3 pixels
		/*This function is used to correct the player's sprite's orientation when the player changes direction.
		It checks the player's x_speed and the is_flipped variable. If the player is 
		moving left and the sprite is not flipped it will flip the sprite, if the player is moving*/
	}
}


void Player::update_tex()
{
	if (killed) return; // if the player is killed, the function exits immediately
	if (casting)
	{
		current_sprite.setTexture(am->casting.at(anim_index)); // sets the player's sprite to the appropriate casting animation frame
		anim_index++; // increments the animation index
		anim_index %= 11; // keeps the animation index within the range of 0 to 10 (11 possible animation frames)
		if (anim_index == 10) // if the animation has reached the end
		{
			casting = !casting; // sets the casting variable to false
			anim_index = 0; // resets the animation index
		}
	}
	else if (x_speed != 0 && y_speed == 0) // if the player is moving horizontally and not vertically
	{
		current_sprite.setTexture(am->run.at(anim_index)); // sets the player's sprite to the appropriate running animation frame
		anim_index++; // increments the animation index
		anim_index %= 6; // keeps the animation index within the range of 0 to 5 (6 possible animation frames)
	}
	else if (y_speed != 0) // if the player is moving vertically (jumping or falling)
	{
		current_sprite.setTexture(am->jump_fall); // sets the player's sprite to the appropriate jumping or falling texture
	}
	else // if the player is not moving
	{
		current_sprite.setTexture(am->player_idle); // sets the player's sprite to the idle texture
	}
	current_sprite.setScale(0.2, 0.2); // sets the scale of the player's sprite
}


void Player::check_damage(Screen_1& screen)
{
	for (auto& e : screen.enemies)
	{
		if (e->killed) continue;//if enemy are killed its okay to have a collision
		if (e->hitbox.getGlobalBounds().intersects(hitbox.getGlobalBounds())) //Enemy hitbox intersect with player
		{
			am->sounddeath.play();
			if (screen.status_bar.lives == 0) am->soundgameover.play();// if lives are equal to 0 play game over sound
			killed = true; //bool for killed are true
			anim_index = 0;// anim index set to 0
			return;
		}
	}
}

void Player::check_coin(Screen_1& screen)
{

	for (auto c = begin(screen.coins); c != end(screen.coins);)
	{
		if (c->current_sprite.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
		{
			am->soundcoin.play();
			screen.found_coins.push_back(c->get_type());
			c = screen.coins.erase(c);
			screen.status_bar.points += screen.status_bar.coin_point;// score and coin sprite added to statusbar
		}
		else c++;
	}
}

void Player::anim_death()
{

	if (anim_count != 0)
	{
		anim_count++;
		if (anim_count >= 2) 
			anim_count = 0;
	}
	else
	{
		current_sprite.setTexture(am->player_die.at(anim_index));

		anim_count++;
		if(anim_index < am->player_die.size()-1) anim_index++;
	}
	sf::Vector2i size(am->player_die[0].getSize().x, am->player_die[0].getSize().y);
	if(!is_flipped) current_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	else current_sprite.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y));
}

void Player::check_teleport(Screen_1& screen)
{
	if (hitbox.getGlobalBounds().intersects(screen.teleport.current_sprite.getGlobalBounds())
		&& screen.coins.empty())
	{
		am->soundtele.play();
		screen.level_cleared = true;
	}
}

void Player::update_current_tiles(Screen_1& screen)
{
	current_tile_x_left = (((hitbox.getGlobalBounds().left) - screen.map.getPosition().x) / am->tile_size);
	current_tile_x_right = (((hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width) - screen.map.getPosition().x) / am->tile_size);
	current_tile_y_top = (((hitbox.getGlobalBounds().top) - screen.map.getPosition().y) / am->tile_size);
	current_tile_y_bottom = (((hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height) - screen.map.getPosition().y) / am->tile_size);
}