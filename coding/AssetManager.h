#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	int s_width = 1920;
	int s_height = 1080;
	
	//Tilemap
	sf::Texture tiles;
	int tiles_width = 8;
	int tiles_height = 8;

	//Views
	sf::View* view;
	sf::View* menu_view;
	sf::View* stat_view;
	int status_bar_height = 100;
	double seconds_pr_frame = 0.016666667;
	
	//Image from paint to generate platform
	int no_of_maps = 3;
	int map_start = 0;
	std::vector<sf::Image> maps;
	int map_x;
	int map_y;
	sf::Image map_back;
	int tile_size = 64;
	
	//Background
	sf::Texture back_tex;
	sf::Sprite back_sprite;
	
	//Headline (intro message)
	sf::Text headline;
	sf::Text text2;
	
	//Player sprites
	sf::Texture player_idle;
	sf::Texture jump_fall;
	std::vector<sf::Texture> run;
	std::vector<sf::Texture> casting;
	std::vector<sf::Texture> player_die;
	
	//Enemy sprites
	std::vector<sf::Texture> enemy1_idle;
	sf::Texture enemy1_hit;
	std::vector<sf::Texture> enemy2;
	
	//Coin sprites
	std::vector<sf::Texture> coins;
	
	//Teleport
	std::vector<sf::Texture> teleport;
	
	//Fonts
	sf::Font font1;
	
	//Sounds
	sf::SoundBuffer buffgameover;
	sf::Sound soundgameover;
	sf::SoundBuffer buffdeath;
	sf::Sound sounddeath;
	sf::SoundBuffer bufffall;
	sf::Sound soundfall;
	sf::SoundBuffer bufftele;
	sf::Sound soundtele;
	sf::SoundBuffer buffspell;
	sf::Sound soundspell;
	sf::SoundBuffer buffmonster;
	sf::Sound soundmonster;
	sf::SoundBuffer buffcoin;
	sf::Sound soundcoin;
	sf::SoundBuffer buffjump;
	sf::Sound soundjump;
	sf::Music music1;

};

