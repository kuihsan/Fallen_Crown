#include <SFML/Graphics.hpp>//preprocessor directive
//This include the SFML library for graphics, it allows the program to use classes such as sf::RenderWindow and sf::Event which are used for creating and managing the game window and handling events such as user input.
#include <SFML/Window.hpp>
#include "Screen_1.h"//This include the header file for the Screen_1 class. 
//This class is the main game screen and it contains the game logic and the game loop.
#include "AssetManager.h"
//This class is used to manage assets such as images, sounds, and fonts.

int main()
{
	srand(time(0)); // sets a random seed by calling srand(time(0))
	//srand() is a C / C++ standard library function that is used to seed a random number generator.
	//It is typically called at the beginning of the program to set the initial seed value for the random number generator
	//In this case, time(0) is passed as the argument, which returns the current time in seconds as an unsigned int. 
	//This means that the seed value is different every time the program runs, resulting in different random number sequences.
	
	AssetManager am; // creates an instance of the AssetManager class
	am.music1.play(); // starts playing a music track
	am.music1.setLoop(true); // sets the music to loop
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Fallen Crown.exe", sf::Style::Default); 
	// creates a new SFML RenderWindow object with the width and height specified in the AssetManager class and with the title "Fallen Crown.exe" and in full screen mode
	window.setFramerateLimit(60); // sets the frame rate limit to 60 frames per second
	window.setKeyRepeatEnabled(false); // disables key repeat
	std::vector<cScreen*> Screens; // creates a vector of pointers to cScreen objects
	int screen = 0; // creates an integer variable screen initialized to 0
	cScreen* s0 = new Screen_1(&am); // creates a new instance of the Screen_1 class and assigns it to s0 pointer
	Screens.push_back(s0); // pushes the s0 pointer to the vector
	while (screen <= 0) // enters a while loop
	{
		screen = Screens[screen]->Run(window); // runs the Run function of the current screen, passing the RenderWindow object as an argument
		if (screen == 0) break; // if the return value is 0, it breaks
		if (screen == 2) // if the return value is 2
		{
			delete Screens[0]; // deletes the current screen
			cScreen* s0 = new Screen_1(&am); // creates a new instance of Screen_1
			Screens.push_back(s0); // pushes the new instance to the vector
			screen = 0; // sets the screen variable to 0
		}
	}
	return 0; // returns 0 at the end of the main function
}

