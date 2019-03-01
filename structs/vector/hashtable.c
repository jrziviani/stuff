#include "hashtable.h"
#include "objects.h"

struct list
{
    cstring *key;
    object *data;
    struct list *next;
    struct list *previous;
};


struct hashtable
{
    size_t size;
    struct list *buckets[256];
    vector *keys;
};

hashtable *hashtable_create(void)
{
    hashtable *table = (hashtable*)malloc(sizeof(hashtable));
    table->keys = vector_create();
    table->size = 0;
    memset(table->buckets, 0, sizeof(list) * 256);
}

struct list *hashtable_get_(hashtable *this, const cstring *key)
{
    struct list *iter;
    size_t index = key->hash % 256;

    if (this == NULL || this->buckets[index] == NULL) {
        return NULL;
    }

    for (iter = this->buckets[index]; iter != NULL; iter = iter->next) {
        if (cstring_compare(key, iter->key, EQUAL)) {
            return iter;
        }
    }

    return NULL;
}

bool hashtable_add(hashtable *this, cstring *key, object *value)
{
    if (this == NULL) {
        return false;
    }

    struct list *item = hashtable_get_(this, key);
    if (item != NULL) {
        object_release(item->data);
        item->data = object_add_ref(value);
        return true;
    }

    size_t index = key->hash % 256;

    struct list *new_item = (list*)malloc(sizeof(list));
    new_item->key = object_add_ref(key);
    new_item->data = object_add_ref(value);
    new_item->next = this->buckets[index];
    this->buckets[index] = new_item;
    this->size++;
    vector_push_back_object(this->keys, key);
}

bool hashtable_remove(hashtable *this, const cstring *key)
{
    if (this == NULL) {
        return false;
    }

    struct list *item = hashtable_get_(this, key);
    if (item == NULL) {
        return false;
    }

    struct list *prev = item->previous;
    struct list *next = item->next;
    prev->next = next;
    next->previous = prev;

    object_release(item->data);
    object_release(item->key);
    free(item);
}

object *hashtable_get(hashtable *this, const cstring *key)
{
    struct list *item = hashtable_get_(this, key);

    if (item == NULL) {
        return NULL;
    }

    return object_add_ref(item->data);
}

bool hashtable_has_key(hashtable *this, const cstring *key)
{
    if (hashtable_get_(this, key) == NULL) {
        return false;
    }

    return true;
}

vector *hashtable_keys(hashtable *this)
{
    if (this == NULL) {
        return NULL;
    }

    return this->keys;
}
