#pragma once

#include "raylib.h"

class Ball {
public:
    Vector2 position;
    Vector2 speed;
    int radius;
    Color color;

    Ball(float x, float y, float spdX, float spdY, int rad, Color col);
    void move();
    void draw() const;
};
