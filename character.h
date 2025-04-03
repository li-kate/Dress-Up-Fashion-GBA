#ifndef CHARACTER_H
#define CHARACTER_H

#include "gba.h"

// Part options
#include "images/head1.h"
#include "images/head2.h"
#include "images/head3.h"
// #include "images/shirt1.h"
// #include "images/shirt2.h"
// #include "images/shirt3.h"
// #include "images/pants1.h"
// #include "images/pants2.h"
// #include "images/pants3.h"

#define HEAD_WIDTH HEAD1_WIDTH
#define HEAD_HEIGHT HEAD1_HEIGHT

typedef struct {
    int x, y; // Character position
    const u16* currentHead;
    // const u16* currentShirt;
    // const u16* currentPants;
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
PartOption* getPartAtPosition(int x, int y);

#endif