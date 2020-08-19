#include"entity.hpp"

class Obstacle : public Entity {
public:

    Obstacle() : Entity() {}

    Obstacle(float x, float y) : Entity(x, y) {}

    void update(sf::Time dt) {}

    const std::string GetSpriteName() const { return "rock.png"; }

    void load() {}

};