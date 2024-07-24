#pragma once
#include "cScreen.h"
#include "Map.h"
#include <chrono>
#include <fstream>
#include "Player.h"
#include "Spell.h"
#include "Enemy.h"
#include "Coin.h"
#include "Teleport.h"
#include "Status_bar.h"
#include "Menu.h"
#include "Highscore.h"
#include "Mushroom.h"
#include "Bat.h"

class Screen_1 : public cScreen
{
public:
	Screen_1(AssetManager* _am);
	~Screen_1();
	bool show_menu = true;
	bool show_scores = false;
	bool level_cleared = false;
	bool exit = false;

	int level = 0;
	int no_of_levels = 2;
	int game_over_delay = 120;

	AssetManager* am;
	Status_bar status_bar;
	Menu menu;
	Highscore highscore;
	Player player;
	Map map;
	Map back_map;
	Teleport teleport;
	std::vector<std::unique_ptr<Enemy>> enemies;// unique_ptr is a non-copyable pointer to an object which is enemy
	std::vector<Spell> spells;// unique_ptr is a non-copyable pointer to an object which is spells
	std::vector<Coin> coins;// unique_ptr is a non-copyable pointer to an object which is coins
	std::vector<int> found_coins;
	std::vector<int> current_level;
	std::vector<int> current_background;

	std::chrono::time_point<std::chrono::high_resolution_clock> master_clock = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> end_master = std::chrono::high_resolution_clock::now();

	int Run(sf::RenderWindow& window);
	bool check_map_void(int x, int y);
	sf::Vector2f get_cord_of_tile(int x, int y);
	void reset();

private:
	int millis_pr_frame = 17;
	bool move_left = false;
	bool move_right = false;
	int draw_header_count = 0;
	sf::Text headline;

	void check_spell_hit_enemy();
	void check_spell_out_of_view(sf::RenderWindow& window);
	void init_level();
	void init_background();
	void spell_casted(bool up, bool down);
	void delete_enemies();
	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
};

