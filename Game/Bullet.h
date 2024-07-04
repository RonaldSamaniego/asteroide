#pragma once

#include "Entity.h"
#include "Constants.h"
class Bullet : public Entity {
public:
    Bullet();
    void update() override;
};



