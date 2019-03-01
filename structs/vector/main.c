#include "objects.h"
#include "vector.h"

#include <stdio.h>

void printer(const char *s)
{
    printf("%s\n", s);
}

int main(void)
{
    vector *vec = vector_create();

    object *numa = object_number_create(54);
    object *numb = object_number_create(-11);
    object *numc = object_number_create(27);
    object *texta = object_text_c_create("this is a text");
    object *textb = object_text_c_create("blabla");
    object *b = object_boolean_create(true);
    object *dec = object_decimal_create(-432.21);

    vector_push_back_object(vec, &numa);
    vector_push_back_object(vec, &numb);
    vector_push_back_object(vec, &numc);
    vector_push_back_object(vec, &texta);
    vector_push_back_object(vec, &textb);
    vector_push_back_object(vec, &b);
    vector_push_back_object(vec, &dec);

    vector_for_each(vec, printer);

    numa = vector_at(vec, 1);
    object_release(&numa);

    vector_release(&vec);

    return 0;
}
