#ifndef OBJECTS_H
#define OBJECTS_H

#include "cstring.h"

#include <stdbool.h>

#define OBJECT_HEADER         \
    object_type type;         \
    size_t refcnt;

#define CONTAINER_HEADER      \
    OBJECT_HEADER             \
    size_t size;

#define TO_NUMBER(obj)        \
    ((number*)obj)

#define TO_DECIMAL(obj)       \
    ((decimal*)obj)

#define TO_TEXT(obj)          \
    ((text*)obj)

#define TO_BOOLEAN(obj)       \
    ((boolean*)obj)

typedef enum object_type
{
    NUMBER,
    DECIMAL,
    TEXT,
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
typedef struct decimal decimal;
typedef struct boolean boolean;
typedef struct text text;

void object_release(object **this);
object *object_number_create(unsigned long data);
object *object_decimal_create(double data);
object *object_text_create(cstring *data);
object *object_text_c_create(const char *data);
object *object_boolean_create(bool data);
const object *const object_view(object *this);
object *object_add_ref(object *this);
void object_print(object *this);
const char* object_to_string(object *this);

struct container
{
    CONTAINER_HEADER
};

struct map
{
    CONTAINER_HEADER
};

#endif /* OBJECTS_H */
