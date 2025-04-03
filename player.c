// player.c
#include "player.h"
#include "gba.h"
#include "images/floorImage.h"
#include "images/fairy.h"

void initPlayer(Player* player) {
    player->x = WIDTH / 2 - PLAYER_WIDTH / 2;
    player->y = HEIGHT / 2 - PLAYER_HEIGHT / 2; // Start in center
    player->width = PLAYER_WIDTH;
    player->height = PLAYER_HEIGHT;
    player->velX = 0;
    player->velY = 0;
}

void updatePlayer(Player* player, u32 currentButtons) {
    // Reset velocity
    player->velX = 0;
    player->velY = 0;
    
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
    if (leftWingBoundary < 0) {
        player->x = WING_WIDTH; // Keep wings on screen
    }
    if (rightWingBoundary > WIDTH) {
        player->x = WIDTH - player->width - WING_WIDTH;
    }
    if (topBoundary < 0) {
        player->y = 0; // Keep main body on screen
    }
    if (bottomBoundary > HEIGHT - FLOOR_HEIGHT) {
        player->y = HEIGHT - FLOOR_HEIGHT - player->height;
    }
}

void drawPlayer(Player* player) {
    // Draw left wing (yellow)
    drawRectDMA(player->y + (player->height - WING_HEIGHT)/2, 
                player->x - WING_WIDTH, 
                WING_WIDTH, WING_HEIGHT, YELLOW);
    
    // Draw main body (fairy image)
    drawImageDMA(player->y, player->x, PLAYER_WIDTH, PLAYER_HEIGHT, fairy);
    
    // Draw right wing (yellow)
    drawRectDMA(player->y + (player->height - WING_HEIGHT)/2, 
                player->x + player->width, 
                WING_WIDTH, WING_HEIGHT, YELLOW);
}