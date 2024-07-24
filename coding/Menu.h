#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
class Screen_1;

class Menu : public sf::RectangleShape
{
public:
	Menu(AssetManager* _am);
	~Menu();

	int choice = 2;
	int min_choice = 2;
	int max_choice = 4;
	void draw(sf::RenderWindow& window);
	void update(char c);
	void do_action(Screen_1& screen);
private:
	AssetManager* am;
	sf::FloatRect menu_rect;
	sf::Text header;
	sf::Text menu1;
	sf::Text menu2;
	sf::Text menu3;
	sf::Text menu4;
	std::vector<std::string> strings =
	{
	    "Fallen Crown",
		"How to play: W,A,S,D to move, Space to jump, J to use magic",
        "Start",
        "Score",
        "Exit"
    };
	std::vector<sf::Text> texts;
};

