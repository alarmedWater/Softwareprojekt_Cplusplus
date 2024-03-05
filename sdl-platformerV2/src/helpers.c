#include "helpers.h"
#include "game.h"
#include "levels.h"
#include <math.h>
#include <stdlib.h>

int cell_is_valid(int r, int c) {
    return r >= 0 && r < ROW_COUNT && c >= 0 && c < COLUMN_COUNT;
}

int cell_is_solid(int r, int c, int flags) {
    return cell_is_valid(r, c) ? (level->cells[r][c]->solid & flags) == flags : 0;
}

int cell_is_ladder(int r, int c) {
    return cell_is_valid(r, c) ? level->cells[r][c]->general_type_id == TYPE_LADDER : 0;
}

int cell_is_solid_ladder(int r, int c) {
    return cell_is_ladder(r, c) && (cell_is_solid(r, c - 1, SOLID_TOP) || cell_is_solid(r, c + 1, SOLID_TOP) ||
           !cell_is_ladder(r - 1, c));
}

int cell_is_water(int r, int c) {
    return cell_is_valid(r, c) ? level->cells[r][c]->general_type_id == TYPE_WATER : 0;
}

int cell_contains(int r, int c, ObjectTypeId general_type) {
    return cell_is_valid(r, c) ? level->cells[r][c]->general_type_id == general_type : 0;
}

int objects_hit_test(Object* object1, Object* object2) {
    const SDL_Rect o1 = object1->type->body;
    const SDL_Rect o2 = object2->type->body;
    if (fabs((object1->x + o1.x + o1.w / 2.0) - (object2->x + o2.x + o2.w / 2.0)) < (o1.w + o2.w) / 2.0 &&
        fabs((object1->y + o1.y + o1.h / 2.0) - (object2->y + o2.y + o2.h / 2.0)) < (o1.h + o2.h) / 2.0) {
        return 1;
    }
    return 0;
}

void object_get_cell(Object* object, int* r, int* c) {
    const SDL_Rect body = object->type->body;
    *r = (object->y + body.y + body.h / 2.0) / CELL_SIZE;
    *c = (object->x + body.x + body.w / 2.0) / CELL_SIZE;
}

void object_get_body(Object* object, Borders* body) {
    const SDL_Rect body_rect = object->type->body;
    body->left = object->x + body_rect.x;
    body->right = body->left + body_rect.w;
    body->top = object->y + body_rect.y;
    body->bottom = body->top + body_rect.h;
}

void object_get_position(Object* object, int* r, int* c, Borders* cell, Borders* body) {
    object_get_cell(object, r, c);
    object_get_body(object, body);

    cell->left = CELL_SIZE * (*c);
    cell->right = cell->left + CELL_SIZE;
    cell->top = CELL_SIZE * (*r);
    cell->bottom = cell->top + CELL_SIZE;
}

int find_near_door(int* r, int* c) {
    const int r0 = *r;
    const int c0 = *c;
    if (cell_contains(r0, c0, TYPE_DOOR)) {
        return 1;
    }
    if (cell_contains(r0, c0 - 1, TYPE_DOOR)) {
        *c = c0 - 1;
        return 1;
    }
    if (cell_contains(r0, c0 + 1, TYPE_DOOR)) {
        *c = c0 + 1;
        return 1;
    }
    return 0;
}

Object* find_near_item(int r, int c) {
    for (int i = level->objects.count - 1; i >= 0; --i) {
        Object* object = level->objects.array[i];
        if (object->type->general_type_id == TYPE_ITEM && !object->removed) {
            int obj_r, obj_c;
            object_get_cell(object, &obj_r, &obj_c);
            if (obj_r == r && obj_c == c) {
                return object;
            }
        }
    }
    return NULL;
}

Object* find_object(Level* level, ObjectTypeId type_id) {
    for (int i = 0; i < level->objects.count; ++i) {
        Object* object = level->objects.array[i];
        if (object->type->typeId == type_id) {
            return object;
        }
    }
    return NULL;
}

double limit_absolute(double value, double max) {
    return value > max ? max : value < -max ? -max : value;
}

void ensure_condition(int condition, const char* message) {
    if (!condition) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, NULL);
        exit(EXIT_FAILURE);
    }
}