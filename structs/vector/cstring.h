#ifndef CSTRING_H
#define CSTRING_H

#include <stdlib.h>

typedef struct cstring cstring;

cstring *cstring_create(const char *str);
cstring *cstring_clone(const cstring *that);
cstring *cstring_from_int(int value);
void cstring_destroy(cstring *this);

size_t cstring_size(const cstring *const this);
char *cstring_cstr(cstring *this);
char cstring_at(const cstring *const this, size_t index);

cstring *cstring_append(cstring *this, const char *str);
cstring *cstring_append_cstring(cstring *this, cstring *that);

unsigned long cstring_hash(cstring *this);

#endif /* CSTRING_H */
