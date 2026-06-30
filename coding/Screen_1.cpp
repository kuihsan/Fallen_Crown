#include "Screen_1.h"

Screen_1::Screen_1(AssetManager* _am) : am(_am), player(_am), status_bar(_am), menu(_am), highscore(_am), teleport(_am)
//This is the constructor of the Screen_1 class. It takes a single parameter, a pointer to an AssetManager class, which is stored in the am member variable.
//It also initializes other member variables such as player, status_bar, menu, highscore, and teleport passing the AssetManager pointer to their constructors.
{
	init_level();//This initializes the current level, such as spawning obstacles and enemies.
	init_background();//This sets up the background image or animation for the current level.
}

void Screen_1::reset() // reset or start the game
{
	level_cleared = false; // bool level cleared are false
	game_over_delay = 120; // time are taken to revive the character
	status_bar.time = 300; // reset the timer
	player = Player(am); //The player variable is set to a new instance of the Player class, with the AssetManager pointer passed as an argument.
	player.update(*this);//The player.update() function is called with *this as an argument. 
	//This updates the player's position and other properties based on the state of the Screen_1 class.

	Coin c;//Class coin which the silver coin that should be collected before finishing the game
	c.reset_statics();//reset the coin
	found_coins.clear();//The found_coins variable is cleared. This variable keeps track of the coins that the player has collected.

	init_level();//This initializes the current level, such as spawning obstacles and enemies.
	init_background();//This sets up the background image or animation for the current level.

	if(level == 0) //This code checks if the level variable is equal to 0. 
	am->view->setCenter(am->s_width/2 , am->s_height/2 );
	//If it is, it sets the center of the view to the center of the screen by dividing the width and height of the screen 
	//by 2 and passing it to the view's setCenter() function.
	else am->view->setCenter(player.current_sprite.getGlobalBounds().left, am->s_height / 2);
	//If not, it sets the center of the view to the left position of the player's current sprite and the middle of the screen's height 
	//by calling player.current_sprite.getGlobalBounds().left and passing it to the view's setCenter() function along with the am->s_height / 2.
	//The view object is typically used to control what part of the game world is currently being displayed on the screen.
}

Screen_1::~Screen_1()
{
}

int Screen_1::Run(sf::RenderWindow& window)
{
	bool pause = false;  //create a boolean variable pause and set it to false
	while (true)
	{
		sf::Event event;//create an event
		while (window.pollEvent(event))//while there are events in the queue
		{
			if (event.type == sf::Event::Closed)//if the event type is closed
			{
				window.close(); //close the window
				return 0;//return 0
			}
			if (event.type == sf::Event::KeyPressed)//if the event type is key pressed
			{
				switch (event.key.code)//use switch case to check the key pressed
				{
				case sf::Keyboard::Escape:
					if(show_menu) show_menu = true;//if the menu is showing set it to true
					else if (show_scores)
					{
						show_scores = false;//if scores are showing set it to false and show menu
						show_menu = true;
					}
					else show_menu = true;//if neither are showing, show menu
					break;
				case sf::Keyboard::W:
				{
					if (show_menu)
						menu.update('u');//if menu is showing, move selection up when W is pressed
					break;
				}
				case sf::Keyboard::S:
					if (show_menu)
						menu.update('d');//move selection to down when S is pressed
					break;
				case sf::Keyboard::Enter:
					if (show_menu)
						menu.do_action(*this); // performs the action selected in the menu
					else if (show_scores)
					{
						show_scores = false; // if highscores are being shown, it will be hidden
						show_menu = true; // menu will be shown
					}
					break;
				case sf::Keyboard::D:
					if (show_menu || show_scores) break;  // if menu or highscores are being shown, do not move the player
					move_left = false; // player is not moving left
					move_right = true; // player is moving right
					break;
				case sf::Keyboard::A://player move when key pressed
					if (show_menu || show_scores) break;
					move_right = false; // player is not moving right
					move_left = true; // player is moving left
					break;
				case sf::Keyboard::Space:
					if (show_menu || show_scores) break;
					if (player.y_speed == 0)
					{
						am->soundjump.play(); // play jump sound
						player.y_speed = -35; // player is jumping
					}
					break;
				case sf::Keyboard::P:
					if (show_menu || show_scores) break;
					pause = !pause; // toggle pause
					break;
				case sf::Keyboard::J:
					if (show_menu || show_scores) break;
					spell_casted(false, false);// cast spell to be linear on y axis
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased)// when key is released the player must stop moving
			{
				switch (event.key.code)
				{
				case sf::Keyboard::D:
					move_right = false;
					break;
				case sf::Keyboard::A:
					move_left = false;
					break;
				}
			}
		}

		if (exit)
		{
			return 0;
		}
		if (player.killed)
		{
			move_left = false;
			move_right = false;

			if (game_over_delay == 0)// if player done reviving
			{
				status_bar.lives--; //lives decreased
				Coin c;
				c.reset_statics(); // coin reset
				if (status_bar.lives < 0) // if the player's lives are less than 0
				{
					highscore.save(status_bar.points);//player's score is saved to the highscore 
					return 2;// the function returns 2, indicating that the game is over
				}
				reset();
			}
			if(game_over_delay > 0) game_over_delay--;


		}
		if (level_cleared)//level cleared
		{
			move_left = false;// player can't move
			move_right = false;

			if (game_over_delay == 0 && status_bar.time == 0) 
			{
				if(level < no_of_levels) level++;
				else
				{
					Coin c;
					c.reset_statics();
					end_master = std::chrono::high_resolution_clock::now();
					auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end_master - master_clock);
					highscore.save(status_bar.points);
					return 2;
				}
				reset();
			}
			if(game_over_delay > 0) game_over_delay--;

		}
		if (move_left)
		{
			player.x_speed = -15;
		}
		else if (move_right)
		{
			player.x_speed = 15;
		}
		else player.x_speed = 0;

		t1 = std::chrono::high_resolution_clock::now();
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t2);
		if (milliseconds.count() > millis_pr_frame)
		{
			if (!pause)
			{

				if(!show_menu && !show_scores) player.update(*this);
				for (auto& i : enemies) i->update(*this);
				for (auto& i : spells) i.update();
				for (auto& i : coins) i.update();
				teleport.update();
				am->back_sprite.setPosition(am->view->getCenter().x - am->view->getSize().y, 0);
				check_spell_out_of_view(window);
				check_spell_hit_enemy();
				delete_enemies();
				status_bar.update(*this);
				if (draw_header_count > 0) draw_header_count--;
			}
			t2 = std::chrono::high_resolution_clock::now();

		}


		window.clear();
		window.setView(*am->view);
		window.draw(am->back_sprite);
		window.draw(back_map);
		window.draw(map);
		for (auto i : coins) window.draw(i.current_sprite);
		window.draw(teleport.current_sprite);
		if(!show_menu && !show_scores) window.draw(player.current_sprite);
		for (const auto& i : enemies)
		{
			window.draw(i->current_sprite);
		}
		for (auto i : spells) window.draw(i);

		if (draw_header_count != 0) window.draw(headline);

		if (show_menu)
		{
			window.setView(*am->menu_view);
			menu.draw(window);
		}
		else if (show_scores)
		{
			window.setView(*am->menu_view);
			highscore.draw(window);
		}
		else
		{
			window.setView(*am->stat_view);
			status_bar.draw(window);
		}

		window.display();
	}
}

void Screen_1::init_background()
{
	int id = -1;// means nothing there
	current_background.clear();

	for (int i = 0; i < am->map_back.getSize().y; i++)
	{
		for (int j = 0; j < am->map_back.getSize().x; j++)
		{
			current_background.push_back(id);
		}
	}
	//this function will base on bool Map from Map class
	back_map.load("Image/Tiles_64x64.png",// the tile set
				sf::Vector2u(am->tile_size, am->tile_size),// size of the tile which is 64x64
				current_background,//current background as vector
				am->map_back.getSize().x,//width of the map
				am->map_back.getSize().y);//height of the map
}

void Screen_1::init_level()
{
	//clears any previous level data, such as the current level vector, coins, and enemies
	int id = 0;
	current_level.clear();
	coins.clear();
	enemies.clear();

	//for console to show that game has started
	std::cout << "Start" << std::endl;

	//Nested loops through each pixel in the map image of the current level
	for (int i = 0; i < am->maps[level].getSize().y; i++)//for y The outer loop iterates through each row (i) of pixels in the image
	{
		for (int j = 0; j < am->maps[level].getSize().x; j++)// for x The inner loop iterates through each column (j) of pixels in the image
		{
			sf::Color c = am->maps[level].getPixel(j, i);//The color of the current pixel being iterated on is stored in the variable c

			if (c == sf::Color(0x4CFF00FF))
			{
				id = 12;
			}
			else if (c == sf::Color(0x7F6A00FF))
			{
				id = -1;// -1 are background. so the object we want to emplace got background or the object are moveable
				enemies.emplace_back(std::make_unique<Mushroom>(am, get_cord_of_tile(j, i))); //create a mushroom object with the given position
			}
			else if (c == sf::Color(0x0094FFFF))
			{
				id = -1;
				enemies.emplace_back(std::make_unique<Bat>(am, get_cord_of_tile(j, i), sf::Vector2i(j, i)));
			}
			else if (c == sf::Color(0x00FFFFFF))
			{
				id = -1;
				Coin c(am, get_cord_of_tile(j, i));
				coins.push_back(c);
			}
			else if (c == sf::Color(0xFF6A00FF))
			{
				id = -1;
				teleport.set_pos(get_cord_of_tile(j, i));
			}
			else { id = -1; }

			current_level.push_back(id);
		}
	}
	//Load Tiles for each colour base on load bool function in map.cpp
	map.load("Image/Tiles_64x64.png",// the tile set
			sf::Vector2u(am->tile_size, am->tile_size),// size of the tile which is 64x64
			current_level,//current level as vector which is id for each object
			am->maps[level].getSize().x,//width of the map
			am->maps[level].getSize().y);//height of the map
}

//This function checks if the specified tile in the map is a void tile (has a value of -1 in the current_level vector)
bool Screen_1::check_map_void(int x, int y)
{//if x is negative or x more map width or y less than 0 or y more than map height (which base on vector)
	if (x < 0 || x >= map.m_width || y < 0 || y >= map.m_height) 
	return true;//If it is, it returns true (indicating that it is a void tile)
	return (current_level.at(y*map.m_width + x) == -1);//If it is not, it returns false (indicating that it is not a void tile)
}

sf::Vector2f Screen_1::get_cord_of_tile(int x, int y)
{
	return sf::Vector2f((x * am->tile_size) + map.getPosition().x, 
		//multiplies the x - coordinate of the tile by the size of each tile
		//and adds the x-coordinate of the current position of the map
						 y*am->tile_size + map.getPosition().y);
		//for the y-coordinate, multiplying it by the size of each tile 
		//and adding the y-coordinate of the current position of the map
}

void Screen_1::spell_casted(bool up, bool down)
{
	am->soundspell.play();
	player.casting = true;// set the player's casting animation to true
	player.anim_index = 0;// reset the animation index
	auto playerRect = player.current_sprite.getGlobalBounds();// get the global bounds of the player's sprite
	Spell b(player.current_sprite.getGlobalBounds(), !player.is_flipped, up, down);//create a new spell object with the player's sprite bounds, 
	//the opposite of the player's flip state, and whether the spell is moving up or down
	spells.push_back(b);// add the new spell object to the vector of spells

}

void Screen_1::check_spell_hit_enemy()
{
	for (auto s = begin(spells); s != end(spells);)
	{
		for (auto e = begin(enemies); e != end(enemies);)
		{// if spell collision with enemies still in sight and the enemies is still alive
			if (s->getGlobalBounds().intersects((*e)->hitbox.getGlobalBounds()) && !(*e)->killed)
			{
				am->soundmonster.play();//play monster got hit
				(*e)->y_speed = - 15; // give enemies such as bat gravity (falling)
				//if spell speed negative and enemy speed positive or spell speed positive and enemy speed negative
				if ((s->speed.x < 0 && (*e)->x_speed > 0) || s->speed.x > 0 && (*e)->x_speed < 0) 
				(*e)->x_speed *= -1; //enemy x speed flipped
				(*e)->killed = true;// enemy killed is true

				s = spells.erase(s);// erase the spell
				status_bar.points += status_bar.monster_point;//plus point to status bar
				if (s == end(spells)) return;//return spells vector once the spell ends
			}
			e++;
		}
		s++;
	}
}

//To delete enemies when killed
void Screen_1::delete_enemies()
{
	for (auto e = enemies.begin(); e != enemies.end();)
	{
		if ((*e)->y_speed == 0 && (*e)->killed) e = enemies.erase(e);
		else e++;
	}
}

//To remove the spell out of screen
void Screen_1::check_spell_out_of_view(sf::RenderWindow& window)
{

	for (auto s = begin(spells); s != end(spells);)
	{
		auto s_pos = window.mapCoordsToPixel(s->getPosition(), *am->view);
		if (s_pos.x < 0 || s_pos.x > am->s_width)
		{
			s = spells.erase(s);
		}
		else
		{
			s++;
		}
	}

}