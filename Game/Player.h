#pragma once


#include "Entity.h"

class Player : public Entity {
public:
    bool thrust;
    Player();
    void update() override;
};


