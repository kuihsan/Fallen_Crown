#include <SFML/Graphics.hpp>
class cScreen
{
public:
    cScreen(); // constructor
    ~cScreen(); // destructor
    virtual int Run(sf::RenderWindow& window) = 0; // pure virtual function
    // Run, which takes a reference to an SFML RenderWindow object as its argument. 
    // //virtual keyword indicates that the function can be overridden in derived classes and
    //= 0 indicates that this function is a pure virtual function.
};

/*The class has a default constructor cScreen() and a default destructor ~cScreen().
The class has a virtual function Run(sf::RenderWindow & window) which takes a reference 
to an sf::RenderWindow object as an argument.This function is marked as virtual which means that 
it can be overridden by derived classes.The function is also marked as = 0 which makes it a pure 
virtual function.This means that the function has no implementation in the base class and must be
implemented in derived classes. The Run() function is the main game loop of the program.It is called 
by the main program and is responsible for updating the game state and rendering the game objects to 
the screen.The sf::RenderWindow object passed as an argument is  used to display the game on the screen.*/