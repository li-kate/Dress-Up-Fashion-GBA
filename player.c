// player.c
#include "player.h"
#include "gba.h"
#include "images/floorImage.h"
#include "images/fairy.h"
#include "images/curtains.h"
#include "character.h"

extern int numPartOptions;

void initPlayer(Player* player) {
    player->x = WIDTH / 2 - PLAYER_WIDTH / 2;
    player->y = HEIGHT / 2 - PLAYER_HEIGHT / 2;
    player->width = PLAYER_WIDTH;
    player->height = PLAYER_HEIGHT;
    player->velX = 0;
    player->velY = 0;
}

void updatePlayer(Player* player, u32 currentButtons) {
    // Reset velocity
    player->velX = 0;
    player->velY = 0;
    player->prevX = player->x;
    player->prevY = player->y;
    
    // Handle input
    if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
        player->velX = -PLAYER_SPEED;
    }
    if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
        player->velX = PLAYER_SPEED;
    }
    if (KEY_DOWN(BUTTON_UP, currentButtons)) {
        player->velY = -PLAYER_SPEED;
    }
    if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
        player->velY = PLAYER_SPEED;
    }
    
    // Update position
    player->x += player->velX;
    player->y += player->velY;
    
    // Calculate wing boundaries
    int leftWingBoundary = player->x - WING_WIDTH;
    int rightWingBoundary = player->x + player->width + WING_WIDTH;
    int topBoundary = player->y;
    int bottomBoundary = player->y + player->height;
    
    // Screen boundary collision including wings
    if (leftWingBoundary < CURTAINS_WIDTH) {  // Left curtain collision
        player->x = CURTAINS_WIDTH + WING_WIDTH;
    }
    if (rightWingBoundary > WIDTH) {  // Right screen edge
        player->x = WIDTH - player->width - WING_WIDTH;
    }
    if (topBoundary < 0) {  // Top screen edge
        player->y = 0;
    }
    if (bottomBoundary > HEIGHT - FLOOR_HEIGHT) {  // Floor collision
        player->y = HEIGHT - FLOOR_HEIGHT - player->height;
    }
}

void drawPlayer(Player* player) {
    // Left wing of fairy
    drawRectDMA(player->y + (player->height - WING_HEIGHT)/2, player->x - WING_WIDTH, WING_WIDTH, WING_HEIGHT, YELLOW);
    // Draw main body (fairy image)
    drawImageDMA(player->y, player->x, PLAYER_WIDTH, PLAYER_HEIGHT, fairy);
    // Right wing of fairy
    drawRectDMA(player->y + (player->height - WING_HEIGHT)/2, player->x + player->width, WING_WIDTH, WING_HEIGHT, YELLOW);
}

// Check collision with all part options
int checkPartSelection(Player* player) {
    for (int i = 0; i < numPartOptions; i++) {
        if (player->x + player->width >= partOptions[i].x && 
            player->x <= partOptions[i].x + partOptions[i].width &&
            player->y + player->height >= partOptions[i].y && 
            player->y <= partOptions[i].y + partOptions[i].height) {
            return i;
        }
    }
    return -1;
}