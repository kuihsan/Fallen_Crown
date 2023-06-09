#include "Menu.h"
#include "Screen_1.h"

// constructor of the Menu class, initializes the menu with the given AssetManager object
Menu::Menu(AssetManager* _am): am(_am)
{
	setSize(sf::Vector2f(am->s_width, am->s_height));// set the size of the menu to the width and height of the screen
	setFillColor(sf::Color(0x00000088));// set the color of the menu to a semi-transparent black
	menu_rect = getGlobalBounds();// save the global bounds of the menu as a rectangle
	// create a position vector for the menu text with an x value of the center of the menu and a y value of 300
	sf::Vector2f pos(menu_rect.left + menu_rect.width / 2, 300);
	
	// loop through all the strings in the menu
	for (int i = 0; i < strings.size(); i++)
	{
		sf::Text t;// create a new text object
		t.setFont(am->font1);// set the font of the text object to the main font
		t.setCharacterSize((i == 0) ? 80 : 50);// set the character size of the text object to 80 if it is the first string, otherwise 50
		t.setOutlineThickness(5);// set the outline thickness of the text object to 5
		// set the fill color of the text object to red if it is the selected choice, otherwise white
		t.setFillColor((i == choice) ? sf::Color(0xff0000FF) : sf::Color(255, 255, 255, 255));
		t.setOutlineColor(sf::Color(0x000000FF));// set the outline color of the text object to black
		t.setString(strings[i]);// set the string of the text object to the corresponding string in the menu strings array
		t.setStyle(sf::Text::Bold);// set the text style to bold
		auto rect = t.getGlobalBounds();// get the global bounds of the text object
		t.setOrigin(rect.width / 2, rect.height / 2);// set the origin of the text object to the center of the text
		t.setPosition(pos);// set the position of the text object to the current position vector
		texts.push_back(t);// add the text object to the texts array
		pos.y += (i == 0) ? 200 : 100;// increment the y value of the position vector by 200 if it is the first string, otherwise 100
	}
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(*this);// function to draw the menu and its text to the window
	for (auto i : texts) window.draw(i);// loop through all the text objects in the texts array and draw them to the window
}

// function to update the menu based on the input
void Menu::update(char c)
{
	switch (c)
	{
	case 'u':// menu choice up
		if (choice > min_choice) choice--;
		break;
	case 'd':// menu choice down
		if (choice < max_choice) choice++;
		break;
	}

	for (int i = 0; i < texts.size(); i++)
	{
		texts[i].setFillColor((i == choice) ? sf::Color(0xff0000FF) : sf::Color(255, 255, 255, 255));// text of choices set to red
	}
}

void Menu::do_action(Screen_1& screen)
{
	switch (choice)
	{
	//case 2: starts the game by setting show_menu to false, level to 0, resetting the game state, and setting the master_clock to the current time
	case 2:
		screen.show_menu = false;
		screen.level = 0;
		screen.reset();
		screen.master_clock = std::chrono::high_resolution_clock::now();
		break;
	//case 3: sets show_menu to false and show_scores to true, which displays the scores screen
	case 3:
		screen.show_menu = false;
		screen.show_scores = true;
		break;
		//case 4: sets exit to true, which will close the game.
	case 4:
		screen.exit = true;
		break;
	}
}