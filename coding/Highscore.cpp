#include "Highscore.h"
#include "Screen_1.h"


// constructor for Highscore class that takes in the AssetManager object as a parameter
Highscore::Highscore(AssetManager* _am) : am(_am)
{
	// calls the load function to load highscore from a file
	load();
	// sets the size of the Highscore object
	setSize(sf::Vector2f(am->s_width, am->s_height));
	// sets the fill color of the Highscore object
	setFillColor(sf::Color(0x00000088));
	// gets the global bounds of the object
	rect = getGlobalBounds();
	// sets position for text objects
	sf::Vector2f pos(rect.left + rect.width / 2, 300);
	// creates four text objects and sets their properties
	for (int i = 0; i < 4; i++)
	{
		//creates a new text object called 't'. a graphical text that can be drawn to render target
		sf::Text t;
		//sets the font of the text object 't' to the font stored in the Asset Manager class
		t.setFont(am->font1);
		//sets the character size of the text object 't' to 80 if the current loop iteration is 0, otherwise it is set to 50.
		t.setCharacterSize((i == 0) ? 80 : 50);
		//sets the outline thickness of the text object 't' to 5.
		t.setOutlineThickness(5);
		//sets the fill color of the text object 't' to white
		t.setFillColor(sf::Color(255, 255, 255, 255));
		//sixth line sets the outline color of the text object 't' to black
		t.setOutlineColor(sf::Color(0x000000FF));
		//set style bold
		t.setStyle(sf::Text::Bold);
		// creates a rectangle object 'rect' that stores the global bounds of the text object 't'.
		auto rect = t.getGlobalBounds();
		//ets the origin of the text object 't' to the center of the rectangle 'rect' both in x and y direction.
		t.setOrigin(rect.width / 2, rect.height / 2);
		//the position of the text object 't' to the position 'pos'
		t.setPosition(pos);
		//pushes the text object 't' into a vector of text objects 'texts
		texts.push_back(t);
		//increments the y position 'pos' by 200 if the current loop iteration is 0, otherwise it is incremented by 100.
		pos.y += (i == 0) ? 200 : 100;
	}
	// This line sets the string of the first text element of the texts vector to "Highscores"
	texts[0].setString("Highscores");
	// This line sets the string of the second text element of the texts vector to "Player: and score " 
	texts[1].setString("Player: " + std::to_string(highscore));
	// This line sets the string of the forth text element of the texts vector to "Back" (for the button back)
	// This line sets the fill color of the forth text element of the texts vector to red (0xff0000FF)
	texts[3].setString("Back");
	texts[3].setFillColor(sf::Color(0xff0000FF));
}


Highscore::~Highscore()
{
}

void Highscore::load()
{
	//Open the highscore file
	std::ifstream ist("highscore.txt");
	//Read the highscore from the file
	ist >> highscore;
	//Close the file
	ist.close();

}

void Highscore::save(int score)
{
	//Open the highscore file
	std::ofstream ost("highscore.txt");
	//Write the highest score to the file, either the current score or the current highscore
	ost << ((highscore < score) ? score : highscore); //conditional operator if the highscore low than existing score
	//Close the file
	ost.close();
	//Reload the highscore
	load();
}

// This function draws the highscore screen.
void Highscore::draw(sf::RenderWindow& window)
{
	// It sets the string for the first element in the texts vector to "Highscores" and the second element to "Player: " + the current highscore.
	texts[0].setString("Highscores");
	texts[1].setString("Player: " + std::to_string(highscore));
	// It sets the origin of each text element to the center of the text and sets the position of each text element to the pos variable, 
	//which is initially set to the center of the Highscore object.
	window.draw(*this);
	sf::Vector2f pos(rect.left + rect.width / 2, 300);
	for (auto t = texts.begin(); t != texts.end();)
	{
		auto rect = t->getGlobalBounds();
		t->setOrigin(rect.width / 2, rect.height / 2);
		t->setPosition(pos);
		window.draw(*t);
		pos.y += (t == texts.begin()) ? 200 : 100;
		t++;
	}
}
