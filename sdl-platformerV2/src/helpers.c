/**
 * @file levels.c
 * @brief Utility functions for level and cell manipulation in the SDL Platformer game.
 *
 * This file contains functions to check and manipulate game level cells, including validation,
 * collision detection, and interaction with game objects like ladders, water, doors, and items.
 */
#include "helpers.h"
#include "game.h"
#include "levels.h"

/**
 * Checks if a cell position is within the valid range of the level grid.
 * 
 * @param r Row index of the cell.
 * @param c Column index of the cell.
 * @return int Returns 1 if the cell is valid, 0 otherwise.
 */
int isCellValid( int r, int c )
{
    return r >= 0 && r < ROW_COUNT && c >= 0 && c < COLUMN_COUNT;
}

/**
 * Determines if a cell at specified coordinates is solid based on provided flags.
 * 
 * @param r Row index of the cell.
 * @param c Column index of the cell.
 * @param flags Flags to check the solidity against.
 * @return int Returns 1 if the cell is solid with respect to the flags, 0 otherwise.
 */
int isSolid( int r, int c, int flags )
{
    return isCellValid(r, c) ? (level->cells[r][c]->solid & flags) == flags : 0;
}

/**
 * Checks if a cell at specified coordinates contains a ladder.
 * 
 * @param r Row index of the cell.
 * @param c Column index of the cell.
 * @return int Returns 1 if there is a ladder in the cell, 0 otherwise.
 */
int isLadder( int r, int c )
{
    return isCellValid(r, c) ? level->cells[r][c]->generalTypeId == TYPE_LADDER : 0;
}

// Returns 1 if there is a ladder at (r, c) and player can stay on it
int isSolidLadder( int r, int c )
{
    return isLadder(r, c) && (isSolid(r, c - 1, SOLID_TOP) || isSolid(r, c + 1, SOLID_TOP) ||
           !isLadder(r - 1, c));
}

/**
 * Checks if a cell at specified coordinates contains water.
 * 
 * @param r Row index of the cell.
 * @param c Column index of the cell.
 * @return int Returns 1 if there is water in the cell, 0 otherwise.
 */
int isWater( int r, int c )
{
    return isCellValid(r, c) ? level->cells[r][c]->generalTypeId == TYPE_WATER : 0;
}

/**
 * Checks if a cell at specified coordinates contains an object of a given type.
 * 
 * @param r Row index of the cell.
 * @param c Column index of the cell.
 * @param generalType The type ID of the object to check for.
 * @return int Returns 1 if the cell contains an object of the specified type, 0 otherwise.
 */
int cellContains( int r, int c, ObjectTypeId generalType )
{
    return isCellValid(r, c) ? level->cells[r][c]->generalTypeId == generalType : 0;
}

/**
 * Performs a hit test between two game objects.
 * 
 * @param object1 Pointer to the first game object.
 * @param object2 Pointer to the second game object.
 * @return int Returns 1 if the objects intersect, 0 otherwise.
 */
int hitTest( Object* object1, Object* object2 )
{
    const SDL_Rect o1 = object1->type->body;
    const SDL_Rect o2 = object2->type->body;
    if (fabs((object1->x + o1.x + o1.w / 2.0) - (object2->x + o2.x + o2.w / 2.0)) < (o1.w + o2.w) / 2.0 &&
        fabs((object1->y + o1.y + o1.h / 2.0) - (object2->y + o2.y + o2.h / 2.0)) < (o1.h + o2.h) / 2.0) {
        return 1;
    }
    return 0;
}

/**
 * Calculates the cell position of an object based on its current location.
 * 
 * @param object Pointer to the game object.
 * @param r Pointer to store the row index of the cell.
 * @param c Pointer to store the column index of the cell.
 */
void getObjectCell( Object* object, int* r, int* c )
{
    const SDL_Rect body = object->type->body;
    *r = (object->y + body.y + body.h / 2.0) / CELL_SIZE;
    *c = (object->x + body.x + body.w / 2.0) / CELL_SIZE;
}

/**
 * Calculates the physical body boundaries of a game object.
 * 
 * @param object Pointer to the game object.
 * @param borders Pointer to a Borders struct to store the calculated boundaries.
 */
void getObjectBody( Object* object, Borders* borders )
{
    const SDL_Rect body = object->type->body;
    borders->left = object->x + body.x;
    borders->right = borders->left + body.w;
    borders->top = object->y + body.y;
    borders->bottom = borders->top + body.h;
}

/**
 * Calculates both the cell position and physical body boundaries of a game object.
 * 
 * @param object Pointer to the game object.
 * @param r Pointer to store the row index of the cell.
 * @param c Pointer to store the column index of the cell.
 * @param cell Pointer to a Borders struct to store the cell boundaries.
 * @param body Pointer to a Borders struct to store the body boundaries.
 */
void getObjectPos( Object* object, int* r, int* c, Borders* cell, Borders* body )
{
    getObjectCell(object, r, c);
    getObjectBody(object, body);

    cell->left = CELL_SIZE * (*c);
    cell->right = cell->left + CELL_SIZE;
    cell->top = CELL_SIZE * (*r);
    cell->bottom = cell->top + CELL_SIZE;
}

/**
 * Searches for a door near the specified cell coordinates.
 * 
 * @param r Pointer to the row index of the cell. Modified if a near door is found.
 * @param c Pointer to the column index of the cell. Modified if a near door is found.
 * @return int Returns 1 if a door is found near the specified coordinates, 0 otherwise.
 */
int findNearDoor( int* r, int* c )
{
    const int r0 = *r;
    const int c0 = *c;
    if (cellContains(r0, c0, TYPE_DOOR)) {
        return 1;
    }
    if (cellContains(r0, c0 - 1, TYPE_DOOR)) {
        *c = c0 - 1;
        return 1;
    }
    if (cellContains(r0, c0 + 1, TYPE_DOOR)) {
        *c = c0 + 1;
        return 1;
    }
    return 0;
}

/**
 * Finds an item object near the specified cell coordinates.
 * 
 * @param r Row index of the cell.
 * @param c Column index of the cell.
 * @return Object* Returns a pointer to the found item object, or NULL if no item is found.
 */
Object* findNearItem( int r, int c )
{
    for (int i = level->objects.count - 1; i >= 0; -- i) {
        Object* object = level->objects.array[i];
        if (object->type->generalTypeId == TYPE_ITEM && !object->removed) {
            int or, oc;
            getObjectCell(object, &or, &oc);
            if (or == r && oc == c) {
                return object;
            }
        }
    }
    return NULL;
}

/**
 * Finds a game object of a specific type within the current level.
 * 
 * @param level Pointer to the current level.
 * @param typeId ID of the object type to find.
 * @return Object* Returns a pointer to the found object, or NULL if no such object is found.
 */
Object* findObject( Level* level, ObjectTypeId typeId )
{
    for (int i = 0; i < level->objects.count; ++ i) {
        Object* object = level->objects.array[i];
        if (object->type->typeId == typeId) {
            return object;
        }
    }
    return NULL;
}

/**
 * Limits a double value to a specified absolute maximum.
 * 
 * @param value The value to limit.
 * @param max The absolute maximum limit.
 * @return double The limited value.
 */
double limitAbs(double value, double max)
{
    return value >  max ?  max :
           value < -max ? -max :
           value;
}


/**
 * Ensures a condition is true, and displays an error message and exits if not.
 * 
 * @param condition The condition to check.
 * @param message The error message to display if the condition is false.
 */
void ensure(int condition, const char* message)
{
    if (!condition) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);
        exit(EXIT_FAILURE);
    }
}
