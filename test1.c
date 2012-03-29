#include <stdio.h>
#include <string.h>
#include "gens.h"
#include "cblocks.h"


int main(int argc, char** argv)
{
    EXECUTE_BLOCK(enumerate, (1, 10), int, x)
        printf("Got %d\n", *x);
    END_BLOCK
    char* buf = "Hello, world!";
    EXECUTE_BLOCK(enumerate, (1, 4), int, z)
        printf("Saying it %d time\n", *z);
        EXECUTE_BLOCK(for_each, (buf, buf + strlen(buf)), char, c)
            printf("%c.", *c);
        END_BLOCK
        printf("\n");
    END_BLOCK

    return 0;
}
