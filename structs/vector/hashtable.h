#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "vector.h"

typedef struct hashtable hashtable;

hashtable *hashtable_create(void);
bool hashtable_add(hashtable *this, cstring *key, object *value);
bool hashtable_remove(hashtable *this, const cstring *key);
bool hashtable_has_key(hashtable *this, const cstring *key);
object *hashtable_get(hashtable *this, const cstring *key);
vector *hashtable_keys(hashtable *this);

#endif /* HASHTABLE_H */
