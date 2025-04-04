#ifndef CHARACTER_H
#define CHARACTER_H

#include "gba.h"
#include "player.h"

// Part options
#include "images/head1.h"
#include "images/head2.h"
#include "images/head3.h"
#include "images/shirt1.h"
#include "images/shirt2.h"
#include "images/shirt3.h"
#include "images/pants1.h"
#include "images/pants2.h"
#include "images/pants3.h"

#define HEAD_WIDTH HEAD1_WIDTH
#define HEAD_HEIGHT HEAD1_HEIGHT
#define SHIRT_WIDTH SHIRT1_WIDTH
#define SHIRT_HEIGHT SHIRT1_HEIGHT
#define PANTS_WIDTH PANTS1_WIDTH
#define PANTS_HEIGHT PANTS1_HEIGHT

#define FIRST_SHIRT_X 105
#define FIRST_SHIRT_Y 40

#define CHARACTER_START_X 20
#define CHARACTER_START_Y 20

typedef struct {
    int x, y; // Character position
    const u16* currentHead;
    const u16* currentShirt;
    const u16* currentPants;
} Character;

// Part selection areas
typedef struct {
    int x, y, width, height;
    const u16* image;
    const char* type;
} PartOption;

void initCharacter(Character* character);
void drawCharacter(Character* character);
void drawPartOptions(void);
void selectPart(Character* character, PartOption* part);
void drawSinglePartOption(int index); 
PartOption* getPartAtPosition(int x, int y);
extern PartOption partOptions[9]; 
int checkPartsOverlap(int x, int y, int width, int height);
void redrawPartsUnderPlayer(Player* player);

#endif