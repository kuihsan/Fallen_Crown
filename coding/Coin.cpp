#include "Coin.h"

//initialize count to 0
int Coin::count = 0;

//default constructor
Coin::Coin(){}

//constructor that takes in the AssetManager and position of coin
Coin::Coin(AssetManager* _am, sf::Vector2f pos): am(_am)
{
	//set texture to the current count of coins
	current_sprite.setTexture(am->coins.at(count));
	//set texture rect to the current frame of animation
	current_sprite.setTextureRect(sf::IntRect(0, 0, am->coins.at(0).getSize().x / no_of_tiles, am->coins.at(0).getSize().y));
	//set the origin of the sprite to the center
	current_sprite.setOrigin((am->coins.at(0).getSize().x / no_of_tiles) / 2, (am->coins.at(0).getSize().y) / 2);
	//set the position of the sprite to the passed in position
	current_sprite.setPosition(pos.x+32, pos.y+32);
	//set the type of the coin to the current count
	type = count;
	//increment the count
	count++;
}


Coin::~Coin()
{
}

//update function
void Coin::update()
{
	update_tex();
}

//function to update the texture of the coin
void Coin::update_tex()
{
	//if the delay has been reached
	if (current_anim_delay >= anim_delay)
	{
		//set the texture rect to the current frame of animation
		current_sprite.setTextureRect
		(sf::IntRect(current_anim_index *(am->coins.at(0).getSize().x / no_of_tiles),
			0,
			am->coins.at(0).getSize().x / no_of_tiles,
			am->coins.at(0).getSize().y));
		//increments the current_anim_index, which will be used to select the next frame of the animation on the next update.
		current_anim_index++;
		//if the current_anim_index is larger than the number of tiles, if so it resets the current_anim_index to 0, to start the animation again.
		if (current_anim_index >= no_of_tiles) current_anim_index = 0;
		current_anim_delay = 0;
	}
	else current_anim_delay++;
}

//reset coin
void Coin::reset_statics()
{
	count = 0;
}
