#include "cstring.h"

#include <string.h>
#include <limits.h>
#include <stdio.h>

struct cstring
{
    size_t size;
    size_t length;
    char str[];
};

cstring *cstring_create(const char *str)
{
    size_t len = strlen(str);
    cstring *cstr = (cstring*)malloc(sizeof(cstring) + len + 1);
    if (cstr == NULL) {
        return NULL;
    }

    cstr->size = len;
    cstr->length = 0;
    memmove(cstr->str, str, len);
    cstr->str[len] = 0;

    return cstr;
}

cstring *cstring_clone(const cstring *that)
{
    cstring *cstr;
    if (that == NULL) {
        return NULL;
    }

    cstr = (cstring*)malloc(sizeof(cstring) + that->size + 1);
    if (cstr == NULL) {
        return NULL;
    }

    memmove(cstr, that, sizeof(cstring) + that->size );
    cstr->str[that->size] = '\0';
    return cstr;
}

cstring *cstring_from_int(int value)
{
    char buff[UINT_MAX + 1];
    snprintf(buff, UINT_MAX + 1, "%d", value);

    return cstring_create(buff);
}

void cstring_destroy(cstring *this)
{
    if (this == NULL) {
        return;
    }

    free(this);
    this = NULL;
}

size_t cstring_size(const cstring *const this)
{
    if (this == NULL) {
        return 0;
    }

    return this->size;
}

char *cstring_cstr(cstring *this)
{
    if (this == NULL) {
        return NULL;
    }

    return this->str;
}

char cstring_at(const cstring *const this, size_t index)
{
    if (index >= this->size) {
        return '\0';
    }

    return this->str[index];
}

cstring *cstring_append(cstring *this, const char *str)
{
    size_t len = strlen(str);
    cstring *cstr = (cstring*)malloc(sizeof(cstring) + this->size + len + 1);
    if (cstr == NULL) {
        return NULL;
    }

    memmove(cstr, this, sizeof(cstring) + this->size);
    memmove(&cstr->str[this->size], str, len);
    cstr->size = this->size + len;
    cstr->str[cstr->size] = '\0';
    cstr->length = 0;

    free(this);
    return cstr;
}

cstring *cstring_append_cstring(cstring *this, cstring *that)
{
    return cstring_append_cstring(this, that->str);
}