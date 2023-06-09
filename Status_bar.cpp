#include "Status_bar.h"
#include "Screen_1.h"


Status_bar::Status_bar(AssetManager* _am): am(_am)
{
	//Setup the status rect
	setSize(sf::Vector2f(am->s_width, 100));
	setFillColor(sf::Color(0x00000055));
	bar_rect = getGlobalBounds();
	//Setup lifefigure
	figure.setTexture(am->player_idle);
	figure.setScale(0.2, 0.2);
	auto figure_rect = figure.getGlobalBounds();
	//Setup enemies score
	figure.setPosition(10, 10);
	//Setup lifetext
	life_text.setFont(am->font1); 
	life_text.setCharacterSize(character_size);
	life_text.setString("X " + std::to_string(lives));
	sf::FloatRect life_rect = life_text.getGlobalBounds();
	life_text.setOrigin(life_rect.width / 2, life_rect.height / 2);
	life_text.setPosition(120, bar_rect.top + bar_rect.height / 2);
	
	//Setup timetext
	time_text.setFont(am->font1);
	time_text.setCharacterSize(character_size);
	time_text.setString("Time: " + std::to_string(time));
	sf::FloatRect time_rect = time_text.getGlobalBounds();
	time_text.setOrigin(time_rect.width / 2, time_rect.height / 2);
	time_text.setPosition(bar_rect.left + bar_rect.width /4, bar_rect.top + bar_rect.height/2.5);
	
	//Setup point text
	point_text.setFont(am->font1);
	point_text.setCharacterSize(character_size);
	point_text.setString("Points: " + std::to_string(points));
	sf::FloatRect point_rect = point_text.getGlobalBounds();
	point_text.setOrigin(point_rect.width / 2, point_rect.height / 2);
	point_text.setPosition(bar_rect.left + bar_rect.width / 4, bar_rect.top + bar_rect.height /1.5);
	
	//Setup coin_image
	sf::Vector2f pos(680, bar_rect.height / 2);
	for (int i = 0; i < am->coins.size(); i++)
	{
		sf::Sprite s;
		s.setTexture(am->coins.at(i));
		s.setTextureRect(sf::IntRect(0, 0, am->coins.at(i).getSize().x / 5, am->coins.at(i).getSize().y));
		s.setOrigin((am->coins.at(0).getSize().x / 8) / 2, (am->coins.at(0).getSize().y) / 2);
		s.setPosition(pos);
		s.setColor(sf::Color(0xFFFFFF22));
		coins.push_back(s);

		pos.x += 40;
	}
}


Status_bar::~Status_bar()
{
}


void Status_bar::update(Screen_1& screen)
{
	if (screen.level_cleared)
	{
		points += time_point;// points plus time_point equal to points
		time--;
		time_text.setString("Time: " + std::to_string(time));
	}
	life_text.setString("X " + std::to_string(lives));
	point_text.setString("Points: " + std::to_string(points));
	frame_count++;
	if (frame_count >= 30)
	{
		time_text.setString("Time: " + std::to_string(time));
		time--;
		frame_count = 0;
	}

	for (int i = 0; i < screen.found_coins.size(); i++)
	{
		coins[screen.found_coins[i]].setColor(sf::Color(0xFFFFFFFF));
	}
	if (screen.found_coins.empty())
	{
		for (auto& i : coins) i.setColor(sf::Color(0xFFFFFF22));
	}

}

void Status_bar::draw(sf::RenderWindow& window)
{
	window.draw(*this);
	window.draw(figure);
	window.draw(life_text);
	window.draw(time_text);
	window.draw(point_text);
	for (auto& i : coins) window.draw(i);
}
