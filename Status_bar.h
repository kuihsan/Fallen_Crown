#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include <vector>
class Screen_1;

class Status_bar : public sf::RectangleShape
{
public:
	Status_bar(AssetManager* _am);
	~Status_bar();

	AssetManager* am;

	sf::FloatRect bar_rect;
	int time = 300;
	int points = 0;
	int lives = 3;
	int frame_count = 0;
	const int monster_point = 50;
	const int coin_point = 100;
	const int time_point = 10;
	const int character_size = 30;
	sf::Text time_text;
	sf::Text point_text;
	sf::Text life_text;
	std::vector<sf::Sprite> coins;


	void update(Screen_1& screen);

	void draw(sf::RenderWindow& window);

	sf::Sprite figure;
	sf::Sprite figure2;


};