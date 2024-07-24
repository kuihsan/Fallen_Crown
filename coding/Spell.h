#pragma once
#include <SFML/Graphics.hpp>
class Spell : public sf::CircleShape
{
public:
	Spell(sf::FloatRect player_rect, bool left_dir, bool up, bool down);
	~Spell();

	sf::Vector2f speed;
	void update();
};

