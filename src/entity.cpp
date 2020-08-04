#include "entity.hpp"
//todo: Create Entity, an abstract class that represents entities inside the game
//(the player, monsters, projectiles and items. entities should occupy a space in the 2d plane)
//required subclasses: Creature, Player, Shot, Itemdrop, different monsters
//each entity subclass should have a static member function GetSprite() which returns the name of the sprite .png file of that creature type
//default sprite for entity should be "entity.png"
Entity::Entity() {}

Entity::Entity(float x, float y) : currPos_(x, y) {}

void Entity::SetRoom(Room* room) { room_ = room; }

Room* Entity::GetRoom() { return room_; }

sf::Vector2f& Entity::GetPosition() { return currPos_; }

void Entity::SetPosition(sf::Vector2f pos) { currPos_ = pos; }
