#ifndef VECTOR_H
#define VECTOR_H

#include "objects.h"

typedef struct vector vector;

vector *vector_create();
void vector_release(vector **this);

void vector_set_threshold(vector *this, size_t threshold);
size_t vector_get_threshold(vector *this);

void vector_set_capacity(vector *this, size_t capacity);
size_t vector_get_capacity(vector *this);

bool vector_push_back_object(vector *this, object **data);
bool vector_push_back_number(vector *this, unsigned long data);
bool vector_push_back_string(vector *this, cstring *data);
bool vector_push_back_boolean(vector *this, bool data);

object *vector_pop_back_object(vector *this);
unsigned long vector_pop_back_number(vector *this);
cstring *vector_pop_back_string(vector *this);
bool vector_pop_back_boolean(vector *this);

object *vector_at(vector *this, size_t index);
void vector_for_each(vector *this, void (*cb)(const char*));

#endif /* VECTOR_H */
