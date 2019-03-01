#ifndef HASH_DJB2_H
#define HASH_DJB2_H

/* Some explanations about the hash function and the reason
 * for it great performance with strings.
 *
 * https://stackoverflow.com/questions/10696223/reason-for-5381-number-in-djb-hash-function
 * http://www.cse.yorku.ca/~oz/hash.html
 *
 * by Daniel J. Bernstein
 */
unsigned long hash_djb2(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

#endif
