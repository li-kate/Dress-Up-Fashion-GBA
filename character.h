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

#define HEAD_START_X 130
#define HEAD_START_Y 10

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

// typedef struct {
//     int x1, y1, x2, y2; // Bounding box coordinates
// } Bounds;

void initCharacter(Character* character);
void drawCharacter(Character* character);
void drawPartOptions(void);
void selectPart(Character* character, PartOption* part);
void drawSinglePartOption(int index); 
PartOption* getPartAtPosition(int x, int y);
extern PartOption partOptions[3]; 
int checkPartsOverlap(int x, int y, int width, int height);
// Bounds getPartsBounds(void); // Get bounding box of part option

#endif