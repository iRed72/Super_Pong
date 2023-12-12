#pragma once

#include "raylib.h"
#include "Paddle.h"
#include "Ball.h"

class Game {
public:
    enum class GameState { MainMenu, OnePlayer, TwoPlayers, GameOver };

    GameState gameState;
    Paddle paddle1;
    Paddle paddle2;
    Ball ball;
    int scorePaddle1;
    int scorePaddle2;

    Game();
    void update();
    void draw() const;

private:
    void updateMainMenu();
    void updateOnePlayer();
    void updateTwoPlayers();
    void updateGameOver();
    void updateGame();
    void drawMainMenu() const;
    void drawGame() const;
    void drawGameOver() const;
    void resetGame();
    void resetRound();
};
