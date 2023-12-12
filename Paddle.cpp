#include "Paddle.h"

Paddle::Paddle(float x, float y, int width, int height, Color col, int spd)
    : rect({ x, y, static_cast<float>(width), static_cast<float>(height) }),
    color(col), speed(spd) {}

void Paddle::moveUp() {
    rect.y -= speed;
}

void Paddle::moveDown() {
    rect.y += speed;
}

void Paddle::draw() const {
    DrawRectangleRec(rect, color);
}
