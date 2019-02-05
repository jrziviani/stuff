#include "objects.h"
#include "vector.h"

int main(void)
{
    vector *vec = vector_create();

    object *numa = object_number_create(54);
    object *numb = object_number_create(11);
    object *numc = object_number_create(27);
    object *texta = object_text_c_create("this is a text");
    object *textb = object_text_c_create("blabla");

    vector_push_back_object(vec, &numa);
    vector_push_back_object(vec, &numb);
    vector_push_back_object(vec, &numc);
    vector_push_back_object(vec, &texta);
    vector_push_back_object(vec, &textb);

    numa = vector_at(vec, 1);
    object_release(&numa);

    vector_release(&vec);

    return 0;
}
