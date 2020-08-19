#include"entity.hpp"

class Rock : public Entity {
public:

    Rock() : Entity() {}

    Rock(float x, float y) : Entity(x, y) {}

    void update(sf::Time dt) {}

    const std::string GetSpriteName() const { return "rock.png"; }

    void load() {}

};