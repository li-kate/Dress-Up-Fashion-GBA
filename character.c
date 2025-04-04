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
    character->currentHead = head1;
    character->currentShirt = shirt1;
    character->currentPants = pants1;
}

void drawCharacter(Character* character, int x, int y) {
    // Head (offset by +8 pixels horizontally)
    drawImageDMA(y, x + 8, HEAD_WIDTH, HEAD_HEIGHT, character->currentHead);
    
    // Shirt (no offset)
    drawImageDMA(y + HEAD_HEIGHT, x, SHIRT_WIDTH, SHIRT_HEIGHT, character->currentShirt);
    
    // Pants (offset by +7 pixels horizontally)
    drawImageDMA(y + HEAD_HEIGHT + SHIRT_HEIGHT, x + 7, 
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

void redrawPartsUnderPlayer(Player* player) {
    // Calculate the exact area the player just vacated
    int left = player->prevX - WING_WIDTH;
    int right = player->prevX + player->width + WING_WIDTH;
    int top = player->prevY;
    int bottom = player->prevY + player->height;
    
    // Check all parts for overlap with this area
    for (int i = 0; i < numPartOptions; i++) {
        PartOption* part = &partOptions[i];
        
        // Calculate intersection between vacated area and part
        int intersectLeft = MAX(left, part->x);
        int intersectRight = MIN(right, part->x + part->width);
        int intersectTop = MAX(top, part->y);
        int intersectBottom = MIN(bottom, part->y + part->height);
        
        if (intersectLeft < intersectRight && intersectTop < intersectBottom) {
            // Calculate source and destination coordinates
            int srcX = intersectLeft - part->x;
            int srcY = intersectTop - part->y;
            int width = intersectRight - intersectLeft;
            int height = intersectBottom - intersectTop;
            
            // Draw only the affected portion of the part
            for (int y = 0; y < height; y++) {
                DMA[3].src = &part->image[(srcY + y) * part->width + srcX];
                DMA[3].dst = &videoBuffer[OFFSET(intersectTop + y, intersectLeft, WIDTH)];
                DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
            }
        }
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