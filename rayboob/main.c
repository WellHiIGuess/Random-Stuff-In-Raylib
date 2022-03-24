#include <stdio.h>
#include "raylib.h"
#include "player.c"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct Coin {
    int x;
    int y;
    bool collected;
};

struct GreenBoi {
    int x;
    int y;
    bool beingUsed;
};


struct Coin coins[6];

struct GreenBoi greenBois[50];
int used = 0;


void initGreenBois() {
    // makes all green bois not being used
    for (size_t i = 0; i < 50; i++) {
        greenBois[i].beingUsed = false;
    }
}

void initCoins() {
    for (size_t i = 0; i < 6; i++) {
        coins[i].x = (rand() % (1000 - 0 + 1)) + 0;
        coins[i].y = (rand() % (700 - 0 + 1)) + 0;
    }
}

void displayDots() {
    // the dots on the screen
    for (size_t i = 0; i < 1000; i++) {
        DrawPixel((rand() % (1000 - 0 + 1)) + 0, (rand() % (1000 - 0 + 1)) + 0, BLACK);
    }
}

void drawCoins() {
    // drawing coins
    for (size_t i = 0; i < 6; i++) {
        if (!coins[i].collected) {
            DrawRectangle(coins[i].x, coins[i].y, 40, 50, YELLOW);
            DrawRectangle(coins[i].x + 20 - 5, coins[i].y + 25 - 15, 10, 30, (Color){252, 167, 10, 255});
        }
    }
}

void drawGreenBois() {
    // drawing green bois
    for (size_t i = 0; i < 50; i++) {
        if (greenBois[i].beingUsed) {
            DrawRectangle(greenBois[i].x, greenBois[i].y, 50, 50, GREEN);
        }
    }
}


int main() {
    srand(0);

    InitWindow(1000, 700, "");

    SetTargetFPS(60);

    initGreenBois();

    initCoins();

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            displayDots();

            drawGreenBois();

            DrawRectangle(player_x, player_y, 50, 50, RED);
            DrawRectangle(player2_x, player2_y, 50, 50, BLUE);

            float fade = 0.1;

            for (size_t i = 0; i < 15; i++) {
                DrawCircle(player_x + 50 / 2, player_y + 50 / 2, 50 + i, Fade(RED, fade));
                fade -= 0.02;
            }
            
            float fade2 = 0.1;

            for (size_t i = 0; i < 15; i++) {
                DrawCircle(player2_x + 50 / 2, player2_y + 50 / 2, 50 + i, Fade(BLUE, fade2));
                fade2 -= 0.02;
            }

            drawCoins();
            
        EndDrawing();

        if (IsKeyDown(KEY_D)) {
            player_x += player_speed;
            player2_x += player2_speed;
        }

        if (IsKeyDown(KEY_A)) {
            player_x -= player_speed;
            player2_x -= player2_speed;
        }

        if (IsKeyDown(KEY_W)) {
            player_y -= player_speed;
            player2_y -= player2_speed;
        }

        if (IsKeyDown(KEY_S)) {
            player_y += player_speed;
            player2_y += player2_speed;
        }

        if (IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_D) && dash_wait == 0) {
            player_x += dash_distance;
            player2_x += dash_distance2;
            dash_wait = 50;
        }

        if (IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_A) && dash_wait == 0) {
            player_x -= dash_distance;
            player2_x -= dash_distance2;
            dash_wait = 50;
        }

        if (IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_W) && dash_wait == 0) {
            player_y -= dash_distance;
            player2_y -= dash_distance2;
            dash_wait = 50;
        }

        if (IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_S) && dash_wait == 0) {
            player_y += dash_distance;
            player2_y += dash_distance2;
            dash_wait = 50;
        }

        if (dash_wait > 0) {
            dash_wait -= 1;
        }

        for (size_t i = 0; i < 6; i++) {
            if (CheckCollisionRecs((Rectangle){coins[i].x, coins[i].y, 40, 50}, (Rectangle){player_x, player_y, 50, 50}) || CheckCollisionRecs((Rectangle){coins[i].x, coins[i].y, 40, 50}, (Rectangle){player2_x, player2_y, 50, 50})) {
                coins[i].collected = true;
            }
        }
        
        // green bois
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (used < 50) {
                greenBois[used].x = GetMouseX();
                greenBois[used].y = GetMouseY();
                greenBois[used].beingUsed = true;

                used++;
            }
        }
    }

    CloseWindow();

    return 0;
}
