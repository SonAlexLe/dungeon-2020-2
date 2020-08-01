//todo: Create Entity, an abstract class that represents entities inside the game
//(the player, monsters, projectiles and items. entities should occupy a space in the 2d plane)
//required subclasses: Creature, Player, Shot, Itemdrop, different monsters
//each entity subclass should have a static member function GetSprite() which returns the name of the sprite .png file of that creature type
//default sprite for entity should be "entity.png"

// cannot implement the methods here for some reason; maybe put the .hpp files in the same directory as the .cpp files?
#include "entity.hpp"

Entity::Entity()