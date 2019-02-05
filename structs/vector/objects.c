#include "objects.h"

struct number
{
    OBJECT_HEADER
    unsigned long data;
};

struct text
{
    OBJECT_HEADER
    cstring *data;
};

struct boolean
{
    OBJECT_HEADER
    bool data;
};

void object_release(object **this)
{
    object *rthis = *this;
    if (rthis == NULL || rthis->refcnt == 0) {
        *this = NULL;
        return;
    }

    if (rthis->refcnt > 1) {
        rthis->refcnt--;
        *this = NULL;
        return;
    }

    if (rthis->type == STRING) {
        cstring_destroy(((text*)rthis)->data);
    }

    free(*this);
    *this = NULL;
}

const object *const object_view(object *this)
{
    return this;
}

object *object_add_ref(object *this)
{
    this->refcnt++;
    return this;
}

object *object_number_create(unsigned long data)
{
    number *num = (number*)malloc(sizeof(number));
    if (num == NULL) {
        return NULL;
    }

    num->refcnt = 1;
    num->type = NUMBER;
    num->data = data;

    return (object*)num;
}

object *object_text_create(cstring *data)
{
    text *txt = (text*)malloc(sizeof(text));
    if (txt == NULL) {
        return NULL;
    }

    txt->refcnt = 1;
    txt->type = STRING;
    txt->data = cstring_clone(data);

    return (object*)txt;
}

object *object_text_c_create(const char *data)
{
    text *txt = (text*)malloc(sizeof(text));
    if (txt == NULL) {
        return NULL;
    }

    txt->refcnt = 1;
    txt->type = STRING;
    txt->data = cstring_create(data);

    return (object*)txt;
}

object *object_bool_create(bool data)
{
    boolean *booln = (boolean*)malloc(sizeof(boolean));
    if (booln == NULL) {
        return NULL;
    }

    booln->refcnt = 1;
    booln->type = NUMBER;
    booln->data = data;

    return (object*)booln;
}
