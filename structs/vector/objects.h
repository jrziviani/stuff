#ifndef OBJECTS_H
#define OBJECTS_H

#include "cstring.h"

#include <stdbool.h>

#define OBJECT_HEADER       \
    object_type type;       \
    size_t refcnt;

#define CONTAINER_HEADER    \
    OBJECT_HEADER           \
    size_t size;

typedef enum object_type
{
    NUMBER,
    STRING,
    BOOLEAN,
    NOTHING,
} object_type;

typedef struct object
{
    OBJECT_HEADER
} object;

struct object_container
{
    CONTAINER_HEADER
};

typedef struct number number;
typedef struct boolean boolean;
typedef struct text text;

void object_release(object **this);
object *object_number_create(unsigned long data);
object *object_text_create(cstring *data);
object *object_text_c_create(const char *data);
object *object_boolean_create(bool data);
const object *const object_view(object *this);
object *object_add_ref(object *this);

struct container
{
    CONTAINER_HEADER
};

struct map
{
    CONTAINER_HEADER
};

#endif /* OBJECTS_H */
