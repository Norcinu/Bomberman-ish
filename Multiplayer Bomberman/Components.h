#ifndef ENTITY_COMPONENTS_H
#define ENTITY_COMPONENTS_H

#include "maths.h"
#include "Sprite.h"

struct Component
{
    Component(){}
    virtual ~Component(){}

    const char * name;
};

struct Health : public Component
{
    Health() : life_metre_(100) {}
    ~Health() {}

    int life_metre_;
};

struct Position : public Component
{
    Position() : position_() {}
    ~Position() {}

    math::Vector2 position_;
};

struct Drawable : public Component
{
    Drawable() {}
    ~Drawable() {}

    Sprite * sprite;
};

#endif