#include "cstring.h"

#include <stdio.h>

int main(void)
{
    cstring *data = cstring_create("This is a test");
    printf("%zu: %s\n", cstring_size(data), cstring_cstr(data));

    cstring *ot = cstring_clone(data);
    ot = cstring_append(ot, " lalala");
    printf("%zu: %s\n", cstring_size(ot), cstring_cstr(ot));

    cstring_destroy(data);
    cstring_destroy(ot);
    return 0;
}
