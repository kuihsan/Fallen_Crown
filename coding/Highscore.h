#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "AssetManager.h"
class Highscore : public sf::RectangleShape
{
public:
	Highscore(AssetManager* _am);
	~Highscore();
	AssetManager* am;
	void load();
	void save(int score);
	void draw(sf::RenderWindow& window);

	int highscore;
	int record_time;
	int minutes;
	int seconds;
	sf::FloatRect rect;
	std::vector<std::string> strings;
	std::vector<sf::Text> texts;
};

