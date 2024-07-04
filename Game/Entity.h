#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Animation.h"
#include "Constants.h"

class Entity
{
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation anim;

    Entity();
    virtual ~Entity();
    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);
    virtual void update() = 0;
    void draw(sf::RenderWindow& app);
};

bool isCollide(Entity* a, Entity* b);



