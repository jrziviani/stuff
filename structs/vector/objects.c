#include "objects.h"

#include <stdio.h>

#define INT_TO_STR(n)              \
    char buff[512];                \
    snprintf(buff, 512, "%lu", n);


struct number
{
    OBJECT_HEADER
    unsigned long data;
    char *str;
};

struct decimal
{
    OBJECT_HEADER
    double data;
    char *str;
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

    if (rthis->type == TEXT) {
        cstring_destroy(TO_TEXT(rthis)->data);
    }
    else if (rthis->type == NUMBER) {
        free(TO_NUMBER(rthis)->str);
    }
    else if (rthis->type == DECIMAL) {
        free(TO_DECIMAL(rthis)->str);
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
    size_t buff_size;

    number *num = (number*)malloc(sizeof(number));
    if (num == NULL) {
        return NULL;
    }

    num->refcnt = 1;
    num->type = NUMBER;
    num->data = data;

    buff_size = snprintf(NULL, 0, "%ld", (long)data);
    num->str = (char*)malloc(buff_size + 1);
    snprintf(num->str, buff_size + 1, "%ld", (long)data);

    return (object*)num;
}

object *object_decimal_create(double data)
{
    size_t buff_size;

    decimal *dec = (decimal*)malloc(sizeof(decimal));
    if (dec == NULL) {
        return NULL;
    }

    dec->refcnt = 1;
    dec->type = DECIMAL;
    dec->data = data;

    buff_size = snprintf(NULL, 0, "%f", (double)data);
    dec->str = (char*)malloc(buff_size + 1);
    snprintf(dec->str, buff_size + 1, "%f", (double)data);

    return (object*)dec;
}

object *object_text_create(cstring *data)
{
    text *txt = (text*)malloc(sizeof(text));
    if (txt == NULL) {
        return NULL;
    }

    txt->refcnt = 1;
    txt->type = TEXT;
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
    txt->type = TEXT;
    txt->data = cstring_create(data);

    return (object*)txt;
}

object *object_boolean_create(bool data)
{
    boolean *booln = (boolean*)malloc(sizeof(boolean));
    if (booln == NULL) {
        return NULL;
    }

    booln->refcnt = 1;
    booln->type = BOOLEAN;
    booln->data = data;

    return (object*)booln;
}

void object_print(object *this)
{
    switch (this->type) {
        case NUMBER:
            printf("%ld\n", (long)TO_NUMBER(this)->data);
            break;

        case DECIMAL:
            printf("%f\n", (double)(TO_DECIMAL(this)->data));
            break;

        case TEXT:
            printf("%s\n", cstring_cstr(TO_TEXT(this)->data));
            break;

        case BOOLEAN:
            printf("%s\n", (TO_BOOLEAN(this)->data) ? "true" : "false");
            break;

        default:
            break;
    }

    return;
}

const char* object_to_string(object *this)
{
    if (this == NULL) {
        return NULL;
    }

    switch (this->type) {
        case NUMBER:
            return TO_NUMBER(this)->str;

        case DECIMAL:
            return TO_DECIMAL(this)->str;

        case TEXT:
            return cstring_cstr(TO_TEXT(this)->data);

        case BOOLEAN:
            return (TO_BOOLEAN(this)->data) ? "true" : "false";

        default:
            break;
    }

    return NULL;
}
