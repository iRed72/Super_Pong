#include "Game.h"

Game::Game()
    : gameState(GameState::MainMenu),
    paddle1(20, GetScreenHeight() / 2 - 40, 20, 80, BLUE, 5),
    paddle2(GetScreenWidth() - 40, GetScreenHeight() / 2 - 40, 20, 80, RED, 5),
    ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 5, 5, 10, GREEN),
    scorePaddle1(0), scorePaddle2(0) {}

void Game::update() {
    switch (gameState) {
    case GameState::MainMenu:
        updateMainMenu();
        break;
    case GameState::OnePlayer:
        updateOnePlayer();
        break;
    case GameState::TwoPlayers:
        updateTwoPlayers();
        break;
    case GameState::GameOver:
        updateGameOver();
        break;
    }
}

void Game::draw() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (gameState) {
    case GameState::MainMenu:
        drawMainMenu();
        break;
    case GameState::OnePlayer:
    case GameState::TwoPlayers:
        drawGame();
        break;
    case GameState::GameOver:
        drawGameOver();
        break;
    }

    EndDrawing();
}

void Game::updateMainMenu() {
    Rectangle onePlayerButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 40, 240, 40 };
    Rectangle twoPlayersButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 20, 240, 40 };
    Rectangle exitButton = { GetScreenWidth() / 2 - 60, GetScreenHeight() / 2 + 80, 120, 40 };

    if (CheckCollisionPointRec(GetMousePosition(), onePlayerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameState = GameState::OnePlayer;
        resetGame();
    }
    else if (CheckCollisionPointRec(GetMousePosition(), twoPlayersButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameState = GameState::TwoPlayers;
        resetGame();
    }
    else if (CheckCollisionPointRec(GetMousePosition(), exitButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        CloseWindow();
    }

    DrawText("Super Pong", GetScreenWidth() / 2 - MeasureText("Super Pong", 40) / 2, GetScreenHeight() / 4, 40, BLACK);
    DrawText("1 Jugador", onePlayerButton.x + 40, onePlayerButton.y + 10, 20, BLACK);
    DrawText("2 Jugadores", twoPlayersButton.x + 40, twoPlayersButton.y + 10, 20, BLACK);
    DrawText("Salir", exitButton.x + 40, exitButton.y + 10, 20, BLACK);
    DrawRectangleLinesEx(onePlayerButton, 2, BLACK);
    DrawRectangleLinesEx(twoPlayersButton, 2, BLACK);
    DrawRectangleLinesEx(exitButton, 2, BLACK);
}

void Game::updateOnePlayer() {
    updateGame();

    if (scorePaddle1 >= 10 || scorePaddle2 >= 10) {
        gameState = GameState::GameOver;
    }
}

void Game::updateTwoPlayers() {
    updateGame();

    if (scorePaddle1 >= 10 || scorePaddle2 >= 10) {
        gameState = GameState::GameOver;
    }
}

void Game::updateGameOver() {
    Rectangle playAgainButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 40, 240, 40 };
    Rectangle returnToMenuButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 20, 240, 40 };

    if (CheckCollisionPointRec(GetMousePosition(), playAgainButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        resetGame();
        gameState = (gameState == GameState::OnePlayer) ? GameState::OnePlayer : GameState::TwoPlayers;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), returnToMenuButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        gameState = GameState::MainMenu;
    }

    DrawText("Juego Terminado", GetScreenWidth() / 2 - MeasureText("Juego Terminado", 40) / 2, GetScreenHeight() / 4, 40, BLACK);
    DrawText("Volver a Jugar", playAgainButton.x + 40, playAgainButton.y + 10, 20, BLACK);
    DrawText("Volver al Menu", returnToMenuButton.x + 40, returnToMenuButton.y + 10, 20, BLACK);
    DrawRectangleLinesEx(playAgainButton, 2, BLACK);
    DrawRectangleLinesEx(returnToMenuButton, 2, BLACK);
}

void Game::updateGame() {
    if (IsKeyDown(KEY_W) && paddle1.rect.y > 0)
        paddle1.moveUp();
    if (IsKeyDown(KEY_S) && paddle1.rect.y + paddle1.rect.height < GetScreenHeight())
        paddle1.moveDown();

    if (gameState == GameState::TwoPlayers) {
        if (IsKeyDown(KEY_UP) && paddle2.rect.y > 0)
            paddle2.moveUp();
        if (IsKeyDown(KEY_DOWN) && paddle2.rect.y + paddle2.rect.height < GetScreenHeight())
            paddle2.moveDown();
    }
    else {
        // Simple AI for the one-player mode
        if (ball.position.y < paddle2.rect.y + paddle2.rect.height / 2) {
            paddle2.moveUp();
        }
        else if (ball.position.y > paddle2.rect.y + paddle2.rect.height / 2) {
            paddle2.moveDown();
        }
    }

    ball.move();

    // Collision with paddles
    if (CheckCollisionCircleRec(ball.position, ball.radius, paddle1.rect) ||
        CheckCollisionCircleRec(ball.position, ball.radius, paddle2.rect)) {
        ball.speed.x = -ball.speed.x;
    }

    // Collision with walls
    if (ball.position.y - ball.radius <= 0 || ball.position.y + ball.radius >= GetScreenHeight())
        ball.speed.y = -ball.speed.y;

    // Ball out of bounds
    if (ball.position.x - ball.radius <= 0) {
        scorePaddle2++;
        resetRound();
    }
    else if (ball.position.x + ball.radius >= GetScreenWidth()) {
        scorePaddle1++;
        resetRound();
    }
}

void Game::drawMainMenu() const {
    Rectangle onePlayerButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 40, 240, 40 };
    Rectangle twoPlayersButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 20, 240, 40 };
    Rectangle exitButton = { GetScreenWidth() / 2 - 60, GetScreenHeight() / 2 + 80, 120, 40 };

    DrawText("Super Pong", GetScreenWidth() / 2 - MeasureText("Super Pong", 40) / 2, GetScreenHeight() / 4, 40, BLACK);
    DrawText("1 Jugador", onePlayerButton.x + 40, onePlayerButton.y + 10, 20, BLACK);
    DrawText("2 Jugadores", twoPlayersButton.x + 40, twoPlayersButton.y + 10, 20, BLACK);
    DrawText("Salir", exitButton.x + 40, exitButton.y + 10, 20, BLACK);
    DrawRectangleLinesEx(onePlayerButton, 2, BLACK);
    DrawRectangleLinesEx(twoPlayersButton, 2, BLACK);
    DrawRectangleLinesEx(exitButton, 2, BLACK);
}

void Game::drawGame() const {
    paddle1.draw();
    paddle2.draw();
    ball.draw();

    DrawText(TextFormat("%d - %d", scorePaddle1, scorePaddle2), GetScreenWidth() / 2 - 30, 10, 20, BLACK);
}

void Game::drawGameOver() const {
    Rectangle playAgainButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 40, 240, 40 };
    Rectangle returnToMenuButton = { GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 20, 240, 40 };

    DrawText("Juego Terminado", GetScreenWidth() / 2 - MeasureText("Juego Terminado", 40) / 2, GetScreenHeight() / 4, 40, BLACK);
    DrawText("Volver a Jugar", playAgainButton.x + 40, playAgainButton.y + 10, 20, BLACK);
    DrawText("Volver al Menu", returnToMenuButton.x + 40, returnToMenuButton.y + 10, 20, BLACK);
    DrawRectangleLinesEx(playAgainButton, 2, BLACK);
    DrawRectangleLinesEx(returnToMenuButton, 2, BLACK);
}

void Game::resetGame() {
    paddle1.rect.y = GetScreenHeight() / 2 - 40;
    paddle2.rect.y = GetScreenHeight() / 2 - 40;
    scorePaddle1 = 0;
    scorePaddle2 = 0;
    resetRound();
}

void Game::resetRound() {
    ball.position = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
    ball.speed = { 5, 5 };
}
