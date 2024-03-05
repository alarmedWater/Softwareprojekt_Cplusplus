#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"

int cell_is_valid(int r, int c);
int cell_is_solid(int r, int c, int flags);
int cell_is_ladder(int r, int c);
int cell_is_solid_ladder(int r, int c);
int cell_is_water(int r, int c);
int cell_contains(int r, int c, ObjectTypeId general_type);
int objects_hit_test(Object* object1, Object* object2);

void object_get_cell(Object* object, int* r, int* c);
void object_get_body(Object* object, Borders* body);
void object_get_position(Object* object, int* r, int* c, Borders* cell, Borders* body);

int find_near_door(int* r, int* c);
Object* find_near_item(int r, int c);
Object* find_object(Level* level, ObjectTypeId type_id);

double limit_absolute(double value, double max);
void ensure_condition_condition(int condition, const char* message);

#endif
