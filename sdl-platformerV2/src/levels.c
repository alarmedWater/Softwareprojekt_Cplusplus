#include "levels.h"
#include "render.h"
#include "game.h"
#include "helpers.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



Level levels[LEVEL_COUNTY][LEVEL_COUNTX];
const char *levelPath = "level/level1.txt";
char *levelsString = NULL; // Initialize global pointers to NULL




// Sprite Manipulation Functions
static void changeSprite(ObjectTypeId typeId, int spriteRow, int spriteColumn);
static void addGraficToSprites(void);

// Level Initialization and Management
static void initLevelsFromString(const char *string);


static void changeSprite(ObjectTypeId typeId, int spriteRow, int spriteColumn)
{
    ObjectType *type = &objectTypes[typeId];
    type->sprite.y = spriteRow * SPRITE_SIZE;
    type->sprite.x = spriteColumn * SPRITE_SIZE;
}


static void addGraficToSprites()
{
    changeSprite(TYPE_WALL_TOP, 4, 6);
    changeSprite(TYPE_WALL, 5, 6);
    changeSprite(TYPE_WALL_STAIR, 4, 6);
    changeSprite(TYPE_GROUND_TOP, 6, 2);
    changeSprite(TYPE_GROUND, 7, 2);
    changeSprite(TYPE_GROUND_STAIR, 6, 2);
    changeSprite(TYPE_GRASS, 40, 0);
    changeSprite(TYPE_GRASS_BIG, 40, 1);
    changeSprite(TYPE_PILLAR_TOP, 48, 1);
    changeSprite(TYPE_PILLAR, 49, 1);
    changeSprite(TYPE_PILLAR_BOTTOM, 50, 1);
    changeSprite(TYPE_DOOR, 10, 0);
    changeSprite(TYPE_LADDER, 12, 2);
}

static inline const char *getLevelString(const char *allLevels, int r, int c)
{
    return allLevels + r * CELL_COUNT * LEVEL_COUNTX + c * COLUMN_COUNT;
}

static inline const char getLevelChar(const char *levelString, int r, int c)
{
    return levelString[r * COLUMN_COUNT * LEVEL_COUNTX + c];
}

static void initLevelsFromString(const char *string)
{
    struct
    {
        int r, c;
    } startLevel;

    // Iterate over the levels
    for (int lr = 0; lr < LEVEL_COUNTY; ++lr)
    {
        for (int lc = 0; lc < LEVEL_COUNTX; ++lc)
        {
            const char *levelString = getLevelString(string, lr, lc);

            Level *level = &levels[lr][lc];
            initLevel(level);
            level->r = lr;
            level->c = lc;
            ObjectArray_append(&level->objects, (Object *)&player);

            // Iterate over the level cells and create objects
            for (int r = 0; r < ROW_COUNT; ++r)
            {
                for (int c = 0; c < COLUMN_COUNT; ++c)
                {
                    const char s = getLevelChar(levelString, r, c);

                    // Wall and ground
                    if (s == '*' || s == 'x')
                    {
                        const ObjectTypeId type = s == '*' ? TYPE_WALL : TYPE_GROUND;
                        const ObjectTypeId type_top = s == '*' ? TYPE_WALL_TOP : TYPE_GROUND_TOP;
                        const char st = getLevelChar(levelString, r - 1, c);
                        if (r == 0 || st == '*' || st == 'x')
                        {
                            createStaticObject(level, type, r, c);
                        }
                        else
                        {
                            createStaticObject(level, type_top, r, c);
                        }
                        // Water
                    }
                    else if (s == '~')
                    {
                        const char st = getLevelChar(levelString, r - 1, c);
                        if (r == 0 || st == '~' || st == 'x' || st == '*')
                        {
                            createStaticObject(level, TYPE_WATER, r, c);
                        }
                        else
                        {
                            createDynamicObject(level, TYPE_WATER_TOP, r, c);
                        }
                        // Pillar
                    }
                    else if (s == '|')
                    {
                        const char st = getLevelChar(levelString, r - 1, c);
                        const char sb = getLevelChar(levelString, r + 1, c);
                        if (r == 0 || st == '*' || st == 'x')
                        {
                            createStaticObject(level, TYPE_PILLAR_TOP, r, c);
                        }
                        else if (r == ROW_COUNT - 1 || sb == '*' || sb == 'x')
                        {
                            createStaticObject(level, TYPE_PILLAR_BOTTOM, r, c);
                        }
                        else
                        {
                            createStaticObject(level, TYPE_PILLAR, r, c);
                        }
                        // Spike
                    }
                    else if (s == '^')
                    {
                        const char st = getLevelChar(levelString, r - 1, c);
                        if (st == '*' || st == 'x')
                        {
                            createStaticObject(level, TYPE_SPIKE_TOP, r, c);
                        }
                        else
                        {
                            createStaticObject(level, TYPE_SPIKE_BOTTOM, r, c);
                        }
                        // Other objects
                    }
                    else if (s == '-')
                    {
                        createStaticObject(level, TYPE_WALL_STAIR, r, c);
                    }
                    else if (s == ',')
                    {
                        createStaticObject(level, (c + 1) % 3 ? TYPE_GRASS : TYPE_GRASS_BIG, r, c);
                    }
                    else if (s == '.')
                    {
                        createStaticObject(level, TYPE_MUSHROOM1 + c % 3, r, c);
                    }
                    else if (s == ';')
                    {
                        createStaticObject(level, c % 2 ? TYPE_TREE1 : TYPE_TREE2, r, c);
                    }
                    else if (s == '@')
                    {
                        createStaticObject(level, TYPE_ROCK, r, c);
                    }
                    else if (s == '=')
                    {
                        createStaticObject(level, TYPE_LADDER, r, c);
                    }
                    else if (s == 'd')
                    {
                        createStaticObject(level, TYPE_DOOR, r, c);
                    }
                    else if (s == 'o')
                    {
                        createDynamicObject(level, TYPE_COIN, r, c);
                    }
                    else if (s == 'O')
                    {
                        createDynamicObject(level, TYPE_GEM, r, c);
                    }
                    else if (s == 'k')
                    {
                        createDynamicObject(level, TYPE_KEY, r, c);
                    }
                    else if (s == 'h')
                    {
                        createDynamicObject(level, TYPE_HEART, r, c);
                    }
                    else if (s == 'a')
                    {
                        createDynamicObject(level, TYPE_APPLE, r, c);
                    }
                    else if (s == 'i')
                    {
                        createDynamicObject(level, TYPE_PEAR, r, c);
                    }
                    else if (s == 'S')
                    {
                        createDynamicObject(level, TYPE_STATUARY, r, c);
                    }
                    else if (s == 'g')
                    {
                        createDynamicObject(level, TYPE_GHOST, r, c);
                    }
                    else if (s == 's')
                    {
                        createDynamicObject(level, TYPE_SCORPION, r, c);
                    }
                    else if (s == 'p')
                    {
                        createDynamicObject(level, TYPE_SPIDER, r, c);
                    }
                    else if (s == 'r')
                    {
                        createDynamicObject(level, TYPE_RAT, r, c);
                    }
                    else if (s == 'b')
                    {
                        createDynamicObject(level, TYPE_BAT, r, c);
                    }
                    else if (s == 'q')
                    {
                        createDynamicObject(level, TYPE_BLOB, r, c);
                    }
                    else if (s == 'f')
                    {
                        createDynamicObject(level, TYPE_FIREBALL, r, c);
                    }
                    else if (s == 'e')
                    {
                        createDynamicObject(level, TYPE_SKELETON, r, c);
                    }
                    else if (s == '`')
                    {
                        Object *drop = createDynamicObject(level, TYPE_DROP, r, c);
                        drop->y = (drop->y / CELL_SIZE) * CELL_SIZE - (CELL_SIZE - drop->type->body.h) / 2 - 1;
                    }
                    else if (s == '_')
                    {
                        createDynamicObject(level, TYPE_PLATFORM, r, c);
                    }
                    else if (s == '/')
                    {
                        createDynamicObject(level, TYPE_SPRING, r, c);
                    }
                    else if (s == '<')
                    {
                        createStaticObject(level, TYPE_ARROW_LEFT, r, c);
                    }
                    else if (s == '>')
                    {
                        createStaticObject(level, TYPE_ARROW_RIGHT, r, c);
                    }
                    else if (s == '&')
                    {
                        createDynamicObject(level, TYPE_CLOUD1, r, c);
                    }
                    else if (s == '!')
                    {
                        createDynamicObject(level, TYPE_TORCH, r, c);
                    }
                    else if (s >= '1' && s <= '9')
                    {
                        Object *action = createDynamicObject(level, TYPE_ACTION, r, c);
                        action->data = s;
                        // Start position
                    }
                    else if (s == 'P')
                    {
                        startLevel.r = lr;
                        startLevel.c = lc;
                        player.y = CELL_SIZE * r;
                        player.x = CELL_SIZE * c;
                    }
                }
            }

            ObjectArray_sortByDepth(&level->objects);
        }
    }

    // Set start level
    setLevel(startLevel.r, startLevel.c);
}

// Allocates memory and copies characters except newlines
static char* allocateAndCopyNonNewlineChars(const char* source, long length) {
    char* processedString = malloc(length + 1);
    if (!processedString) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < length; ++i) {
        if (source[i] != '\n') {
            processedString[j++] = source[i];
        }
    }
    processedString[j] = '\0'; // Null-terminate the processed string
    return processedString;
}

// Processes the temporary string to remove newlines
static void processLevelData(char* tempString, long length) {
    levelsString = allocateAndCopyNonNewlineChars(tempString, length);
    free(tempString); // Free the temporary string
}

// Function to free the memory allocated for levelsString
void freeLevelsString()
{
    free(levelsString);
    levelsString = NULL;
}

// Function to load level data from a file
// Function to load level data from a file
char* loadLevelFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* tempString = malloc(length + 1);
    if (!tempString) {
        fclose(file); // Close the file immediately after error
        return NULL;
    }

    if (fread(tempString, 1, length, file) < (size_t)length) {
        fprintf(stderr, "Failed to read the complete file\n");
        free(tempString);
        fclose(file);
        return NULL;
    }
    tempString[length] = '\0';

    processLevelData(tempString, length);
    fclose(file);
    return levelsString;
}

void initLevels()
{
    if (!loadLevelFromFile(levelPath))
    {
        fprintf(stderr, "Failed to load levels from file: %s\n", levelPath);
        return; // Exit if loading fails
    }

    // Ensure levelsString is correctly initialized before proceeding
    if (levelsString == NULL)
    {
        fprintf(stderr, "Levels string is not initialized.\n");
        return;
    }
    printf("Actual length: %zu\n", strlen(levelsString));
    printf("Expected length: %d\n", LEVEL_COUNTY * LEVEL_COUNTX * ROW_COUNT * COLUMN_COUNT);

    ensure(strlen(levelsString) == LEVEL_COUNTY * LEVEL_COUNTX * ROW_COUNT * COLUMN_COUNT,
           "The levels string does not match the levels count or size.");

    initLevelsFromString(levelsString);

    for (int r = 0; r < LEVEL_COUNTY; r++)
    {
        for (int c = 0; c < LEVEL_COUNTX; c++)
        {
            levels[r][c].init = addGraficToSprites();
        }
    }
}