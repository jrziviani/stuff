#include "vector.h"

#include <string.h>

struct vector
{
    CONTAINER_HEADER
    size_t capacity;
    size_t threshold;
    object **items;
};

bool vector_grow(vector *this)
{
    size_t new_capacity = this->capacity * this->threshold;
    object **items = (object**)malloc(sizeof(object*) * new_capacity);
    if (items == NULL) {
        return false;
    }

    memset(items, 0, sizeof(object*) * new_capacity);
    memmove(items, this->items, sizeof(object*) * this->capacity);
    free(this->items);
    free(this);
    this->items = items;
    return true;
}

bool vector_shrink(vector *this)
{
    size_t new_capacity = this->capacity / this->threshold;
    object **items = (object**)malloc(sizeof(object*) * new_capacity);
    if (items == NULL) {
        return false;
    }

    memset(items, 0, sizeof(object*) * new_capacity);
    memmove(items, this->items, sizeof(object*) * new_capacity);
    for (size_t i = new_capacity; i < this->capacity; i++) {
        object_release(&this->items[i]);
    }
    free(this->items);
    free(this);
    this->items = items;
    return true;
}

vector *vector_create()
{
    vector *vec = (vector*)malloc(sizeof(vector));
    if (vec == NULL) {
        return vec;
    }

    vec->refcnt = 1;
    vec->size = 0;
    vec->capacity = 20;
    vec->threshold = 2;
    vec->items = (object**)malloc(sizeof(object*) * vec->capacity);
    if (vec->items == NULL) {
        return NULL;
    }

    memset(vec->items, 0, sizeof(object*) * vec->capacity);
    return vec;
}

void vector_release(vector **this)
{
    vector *rthis = *this;
    if (rthis == NULL || rthis->refcnt == 0) {
        return;
    }

    if (rthis->refcnt > 1) {
        rthis->refcnt--;
        return;
    }

    for (size_t i = 0; i < rthis->capacity; i++) {
        if (rthis->items[i] == NULL) {
            continue;
        }

        object_release(&rthis->items[i]);
    }

    free(rthis->items);
    rthis->items = NULL;
    free(rthis);
    *this = NULL;
}

bool vector_push_back_object(vector *this, object **data)
{
    if (*data == NULL || this == NULL) {
        return false;
    }

    if (this->size >= this->capacity) {
        if (!vector_grow(this)) {
            return false;
        }
    }

    if (this->items[this->size] != NULL) {
        object_release(&this->items[this->size]);
    }

    this->items[this->size++] = *data;
    *data = NULL;

    return true;
}

object *vector_pop_back_object(vector *this)
{
    if (this == NULL || this->size == 0) {
        return NULL;
    }

    object *ret = this->items[this->size--];
    this->items[this->size--] = NULL;

    if (this->size < this->capacity / 4) {
        if (!vector_shrink(this)) {
            return NULL;
        }
    }

    return ret;
}

object *vector_at(vector *this, size_t index)
{
    if (this == NULL || this->size <= index) {
        return NULL;
    }

    return object_add_ref(this->items[index]);
}
