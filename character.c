#include "character.h"
#include <string.h>
#include "player.h"

// Part options display
int numPartOptions = 9; // Number of part options

PartOption partOptions[] = {
    // Heads (top row)
    {FIRST_SHIRT_X + 7, FIRST_SHIRT_Y - 30, HEAD_WIDTH, HEAD_HEIGHT, head1, "head"},
    {FIRST_SHIRT_X + 7 + 45, FIRST_SHIRT_Y - 30, HEAD_WIDTH, HEAD_HEIGHT, head2, "head"},
    {FIRST_SHIRT_X + 7 + 90, FIRST_SHIRT_Y - 30, HEAD_WIDTH, HEAD_HEIGHT, head3, "head"},
    
    // Shirts (middle row)
    {FIRST_SHIRT_X, FIRST_SHIRT_Y, SHIRT_WIDTH, SHIRT_HEIGHT, shirt1, "shirt"},
    {FIRST_SHIRT_X + 45, FIRST_SHIRT_Y, SHIRT_WIDTH, SHIRT_HEIGHT, shirt2, "shirt"},
    {FIRST_SHIRT_X + 45 + 45, FIRST_SHIRT_Y, SHIRT_WIDTH, SHIRT_HEIGHT, shirt3, "shirt"},
    
    // // Pants
    {FIRST_SHIRT_X + 7, FIRST_SHIRT_Y + 40, PANTS_WIDTH, PANTS_HEIGHT, pants1, "pants"},
    {FIRST_SHIRT_X + 7 + 45, FIRST_SHIRT_Y + 40, PANTS_WIDTH, PANTS_HEIGHT, pants2, "pants"},
    {FIRST_SHIRT_X + 7 + 90, FIRST_SHIRT_Y + 40, PANTS_WIDTH, PANTS_HEIGHT, pants3, "pants"}
};

void initCharacter(Character* character) {
    character->x = CHARACTER_START_X;
    character->y = CHARACTER_START_Y;
    character->currentHead = head1;
    character->currentShirt = shirt1;
    character->currentPants = pants1;
}

void drawCharacter(Character* character) {
    // Head
    drawImageDMA(character->y, character->x + 8, 
                HEAD_WIDTH, HEAD_HEIGHT, character->currentHead);
    
    // Shirt
    drawImageDMA(character->y + HEAD_HEIGHT, character->x, 
                SHIRT_WIDTH, SHIRT_HEIGHT, character->currentShirt);
    
    // // Pants
    drawImageDMA(character->y + HEAD_HEIGHT + SHIRT_HEIGHT, character->x + 7, 
                PANTS_WIDTH, PANTS_HEIGHT, character->currentPants);
}

void drawPartOptions(void) {  
    // Draw all part options
    for (int i = 0; i < numPartOptions; i++) {
        drawSinglePartOption(i);
    }
}

void drawSinglePartOption(int index) {
    if (index >= 0 && index < numPartOptions) {
        // Draw part image
        drawImageDMA(partOptions[index].y, 
                    partOptions[index].x,
                    partOptions[index].width,
                    partOptions[index].height,
                    partOptions[index].image);
    }
}

PartOption* getPartAtPosition(int x, int y) {
    for (int i = 0; i < numPartOptions; i++) {
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
    else if (strcmp(part->type, "shirt") == 0) {
        character->currentShirt = part->image;
    } 
    else if (strcmp(part->type, "pants") == 0) {
        character->currentPants = part->image;
    }
}

int checkPartsOverlap(int x, int y, int width, int height) {
    int checkX = x - WING_WIDTH;
    int checkWidth = width + 2*WING_WIDTH;
    
    for (int i = 0; i < numPartOptions; i++) {
        if (checkX < partOptions[i].x + partOptions[i].width &&
            checkX + checkWidth > partOptions[i].x &&
            y < partOptions[i].y + partOptions[i].height &&
            y + height > partOptions[i].y) {
            return 1;
        }
    }
    return 0;
}