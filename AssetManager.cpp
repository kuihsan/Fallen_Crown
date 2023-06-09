#include "AssetManager.h"

AssetManager::AssetManager()
{
	//Load map and tiles
	tiles.loadFromFile("Image/Tiles_64x64.png"); // loads the tiles texture from the file "Image/Tiles_64x64.png"
	for (int i = 0; i < no_of_maps; i++) // loop from start of the map to no_of_maps
	{
		sf::Image map;
		map.loadFromFile("Image/Level/" + std::to_string(i) + ".png"); // loads the map image from the file "Image/Level/<i>.png"
		maps.push_back(map); // add the map to the maps vector
	}
	map_x = maps[1].getSize().x; // get the x size of the second map
	map_y = maps[1].getSize().y; // get the y size of the second map
	
	//Load back_map and background
	back_tex.loadFromFile("Image/background1.jpg");// loads the background texture from the file "Image/background1.jpg"
	back_sprite.setTexture(back_tex); // sets the texture of the back_sprite to back_tex
	back_sprite.setScale(1,1); // sets the scale of the back_sprite to 1,1
	map_back.loadFromFile("Image/Level/map_back.png"); // loads the map_back image from the file "Image/Level/map_back.png"
	
	//Setup views
	view = new sf::View(sf::FloatRect(0, 0, s_width, s_height));// creates a new view with the dimensions s_width and s_height
	menu_view = new sf::View(sf::FloatRect(0, 0, s_width, s_height)); // creates a new menu_view with the dimensions s_width and s_height
	stat_view = new sf::View(sf::FloatRect(0, 0, s_width, status_bar_height));// creates a new stat_view with the dimensions s_width and status_bar_height
	stat_view->setViewport(sf::FloatRect(0, 0, 1, 0.1)); // sets the viewport of stat_view to the top 10 % of the screen
	view->setCenter((maps[0].getSize().x*tile_size) / 2, s_height / 2);  // sets the center of the view to the center of the first map
	
	//Load player sprites
	player_idle.loadFromFile("Image/Ali/Idle/adventurer-idle-00.png");// loads the player idle sprite 
	jump_fall.loadFromFile("Image/Ali/Jump/adventurer-fall-00.png");// loads the player jump/fall sprite
	
	for (int i = 0; i <= 5; i++)
	{
		sf::Texture rn;
		rn.loadFromFile("Image/Ali/Run/adventurer-run-0" + std::to_string(i) + ".png");
		run.push_back(rn);// loads the player run sprites
	}

	for (int i = 0; i <= 9; i++)
	{
		sf::Texture die;
		die.loadFromFile("Image/Ali/Die/adventurer-die-0" + std::to_string(i) + ".png");
		player_die.push_back(die);// loads the player die sprites
	}
	
	for (int i = 0; i <= 11; i++)
	{
		sf::Texture cast;
		
		if (i < 10)
		cast.loadFromFile("Image/Ali/Cast/adventurer-cast-0" + std::to_string(i) + ".png");
		else
		cast.loadFromFile("Image/Ali/Cast/adventurer-cast-" + std::to_string(i) + ".png");
		casting.push_back(cast);
	}// loads the player cast sprites
	
	//Load enemy sprites
	//Enemy 1 idle:
	for (int i = 1; i <= 8; i++)
	{
		sf::Texture en1_id;
		en1_id.loadFromFile("Image/Mushroom/Move/row-1-column-" + std::to_string(i) + ".png");
		enemy1_idle.push_back(en1_id);
	}
	//Enemy 1 Die
	enemy1_hit.loadFromFile("Image/Mushroom/Die/row-1-column-2.png");
	
	//Enemy 2 idle:
	for (int i = 1; i <= 8; i++)
	{
		sf::Texture en2_id;
		en2_id.loadFromFile("Image/Bat/row-1-column-" + std::to_string(i) + ".png");
		enemy2.push_back(en2_id);
	}
	
	//Load coins
	for (int i = 0; i < 6; i++)
	{
		sf::Texture t;
		t.loadFromFile("Image/Coin/" + std::to_string(i) + ".png");
		coins.push_back(t);
	}

	//Load Teleport
	for (int i = 1; i < 16; i++)
	{
		sf::Texture t;
		if (i < 10)
			t.loadFromFile("Image/Teleport/1/sprite_0" + std::to_string(i) + ".png");
		else
			t.loadFromFile("Image/Teleport/1/sprite_" + std::to_string(i) + ".png");

		teleport.push_back(t);
	}

	//Load fonts
	font1.loadFromFile("fonts/Melted Monster.ttf");

	//Load sounds
	buffgameover.loadFromFile("sound/game_over.wav");
	soundgameover.setBuffer(buffgameover);

	buffdeath.loadFromFile("sound/death.wav");
	sounddeath.setBuffer(buffdeath);

	bufffall.loadFromFile("sound/fall.wav");
	soundfall.setBuffer(bufffall);

	bufftele.loadFromFile("sound/Teleport.wav");
	soundtele.setBuffer(bufftele);

	buffspell.loadFromFile("sound/Spell casted.wav");
	soundspell.setBuffer(buffspell);
	soundspell.setVolume(45);

	buffmonster.loadFromFile("sound/monster_death.wav");
	soundmonster.setBuffer(buffmonster);
	soundmonster.setVolume(45);

	buffcoin.loadFromFile("sound/coin.wav");
	soundcoin.setBuffer(buffcoin);

	buffjump.loadFromFile("sound/jump.wav");
	soundjump.setBuffer(buffjump);
	soundjump.setVolume(45);

	music1.openFromFile("sound/DARKNESS.ogg");
	music1.setVolume(45);
}


AssetManager::~AssetManager()
{
}
