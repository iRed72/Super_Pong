// Super_Pong.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "raylib.h"
#include "Game.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Super Pong");

    Game game;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.update();
        game.draw();
    }

    CloseWindow();

    return 0;
}

