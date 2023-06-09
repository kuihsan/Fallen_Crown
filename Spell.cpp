#include "Spell.h"

Spell::Spell(sf::FloatRect player_rect, bool left_dir, bool up, bool down)
{
	setRadius(5); //set radius of spell's circle shape to 5
	setFillColor(sf::Color::Color::White); //set the fill color of the spell to white
	setOutlineThickness(4); //set the outline thickness of the spell to 4
	setOutlineColor(sf::Color::Color::Blue); //set the outline color of the spell to blue

	if (left_dir) //if the spell is moving left
	{
		speed.x = 20; //set the x-speed of the spell to 20 (positive value moving right)
		setPosition(player_rect.left + 80, player_rect.top + 35); 
		//set the initial position of the spell to be slightly to the right of the player's hitbox
	}
	else
	{
		speed.x = -20;
		setPosition(player_rect.left, player_rect.top + 35);
	}

	if (up) speed.y = -2;
	else if (down) speed.y = 2;
	else speed.y = 0;
}


Spell::~Spell()
{
}

void Spell::update()
{
	move(speed.x, speed.y);
}
