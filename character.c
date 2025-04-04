#include "character.h"
#include <string.h>
#include "player.h"

// Part options display
PartOption partOptions[] = {
    // Heads
    {HEAD_START_X, HEAD_START_Y, HEAD_WIDTH, HEAD_HEIGHT, head1, "head"},
    {HEAD_START_X + 40, HEAD_START_Y, HEAD_WIDTH, HEAD_HEIGHT, head2, "head"},
    {HEAD_START_X + 80, HEAD_START_Y, HEAD_WIDTH, HEAD_HEIGHT, head3, "head"},
    
    // Shirts
    // {210, 30, SHIRT_WIDTH, SHIRT_HEIGHT, shirt1, "shirt"},
    // {210, 60, SHIRT_WIDTH, SHIRT_HEIGHT, shirt2, "shirt"},
    // {210, 90, SHIRT_WIDTH, SHIRT_HEIGHT, shirt3, "shirt"},
    
    // // Pants
    // {240, 30, PANTS_WIDTH, PANTS_HEIGHT, pants1, "pants"},
    // {240, 60, PANTS_WIDTH, PANTS_HEIGHT, pants2, "pants"},
    // {240, 90, PANTS_WIDTH, PANTS_HEIGHT, pants3, "pants"}
};

void initCharacter(Character* character) {
    character->x = 20;
    character->y = 40;
    character->currentHead = head1;
    // character->currentShirt = shirt1;
    // character->currentPants = pants1;
}

void drawCharacter(Character* character) {
    // Head
    drawImageDMA(character->y, character->x + 8, 
                HEAD_WIDTH, HEAD_HEIGHT, character->currentHead);
    
    // Shirt
    // drawImageDMA(character->y + HEAD_HEIGHT, character->x, 
    //             SHIRT_WIDTH, SHIRT_HEIGHT, character->currentShirt);
    
    // // Pants
    // drawImageDMA(character->y + HEAD_HEIGHT + SHIRT_HEIGHT, character->x + 8, 
    //             PANTS_WIDTH, PANTS_HEIGHT, character->currentPants);
}

void drawPartOptions(void) {  
    // Draw all part options
    for (int i = 0; i < 3; i++) {
        drawSinglePartOption(i);
    }
}

void drawSinglePartOption(int index) {
    if (index >= 0 && index < 3) {
        // Draw part image
        drawImageDMA(partOptions[index].y, 
                    partOptions[index].x,
                    partOptions[index].width,
                    partOptions[index].height,
                    partOptions[index].image);
    }
}

PartOption* getPartAtPosition(int x, int y) {
    for (int i = 0; i < 3; i++) {
        if (x >= partOptions[i].x && x <= partOptions[i].x + partOptions[i].width &&
            y >= partOptions[i].y && y <= partOptions[i].y + partOptions[i].height) {
            return &partOptions[i];
        }
    }
    return NULL;
}

void selectPart(Character* character, PartOption* part) {
    if (part == NULL) return;
    
    if (strcmp(part->type, "head") == 0) {
        character->currentHead = part->image;
    } 
    // else if (strcmp(part->type, "shirt") == 0) {
    //     character->currentShirt = part->image;
    // } 
    // else if (strcmp(part->type, "pants") == 0) {
    //     character->currentPants = part->image;
    // }
}

// Bounds getPartsBounds(void) {
//     Bounds bounds = {WIDTH, HEIGHT, 0, 0};
//     for (int i = 0; i < 9; i++) {
//         if (partOptions[i].x < bounds.x1) bounds.x1 = partOptions[i].x;
//         if (partOptions[i].y < bounds.y1) bounds.y1 = partOptions[i].y;
//         if (partOptions[i].x + partOptions[i].width > bounds.x2) 
//             bounds.x2 = partOptions[i].x + partOptions[i].width;
//         if (partOptions[i].y + partOptions[i].height > bounds.y2) 
//             bounds.y2 = partOptions[i].y + partOptions[i].height;
//     }
//     return bounds;
// }

int checkPartsOverlap(int x, int y, int width, int height) {
    // Expand check area to include wings
    int checkX = x - WING_WIDTH;
    int checkWidth = width + 2*WING_WIDTH;
    
    for (int i = 0; i < 9; i++) {
        if (checkX < partOptions[i].x + partOptions[i].width &&
            checkX + checkWidth > partOptions[i].x &&
            y < partOptions[i].y + partOptions[i].height &&
            y + height > partOptions[i].y) {
            return 1;
        }
    }
    return 0;
}