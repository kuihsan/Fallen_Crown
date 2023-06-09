#include "Teleport.h"


Teleport::Teleport(){}

Teleport::Teleport(AssetManager* _am): am(_am)
{
	current_sprite.setTexture(am->teleport.at(anim_index));
	current_sprite.setOrigin(am->teleport.at(0).getSize().x / 1.5, (am->teleport.at(0).getSize().y) / 1.5);
	current_sprite.setPosition(50, 600);
}

Teleport::~Teleport()
{
}

void Teleport::set_pos(sf::Vector2f pos)
{
	current_sprite.setPosition(pos.x + 32, pos.y + 32);
}

void Teleport::update()
{
	update_tex();
}

void Teleport::update_tex()
{
	current_sprite.setTexture(am->teleport.at(anim_index));
	anim_index++;
	if (anim_index >= 15) anim_index = 0;
}
