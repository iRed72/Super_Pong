#include "Ball.h"

Ball::Ball(float x, float y, float spdX, float spdY, int rad, Color col)
    : position({ x, y }), speed({ spdX, spdY }), radius(rad), color(col) {}

void Ball::move() {
    position.x += speed.x;
    position.y += speed.y;
}

void Ball::draw() const {
    DrawCircleV(position, radius, color);
}
