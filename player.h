// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "gba.h"

typedef struct {
    int x, y;           // Current position
    int prevX, prevY;   // Previous position
    int width, height;
    int velX, velY;
} Player;

// Player dimensions
#define PLAYER_WIDTH FAIRY_WIDTH
#define PLAYER_HEIGHT FAIRY_HEIGHT
#define WING_WIDTH 5
#define WING_HEIGHT 5
#define PLAYER_SPEED 2

void initPlayer(Player* player);
void updatePlayer(Player* player, u32 currentButtons);
void drawPlayer(Player* player);
int checkPartSelection(Player* player);

#endif