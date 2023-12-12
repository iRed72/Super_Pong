#pragma once

#include "raylib.h"

class Paddle {
public:
    Rectangle rect;
    Color color;
    int speed;

    Paddle(float x, float y, int width, int height, Color col, int spd);
    void moveUp();
    void moveDown();
    void draw() const;
};
