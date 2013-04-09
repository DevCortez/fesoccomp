#include "cadeia.h"

int main()
{
    void* x = 0;
    add(&x, 1);
    add(&x, 2);
    addpos(&x, 1, 0);
    addunique(&x, 3);
    addorder(&x, 4);
    del(&x, 1);
    delvalue(&x, 1);
    showall(x);
    if(isinorder(x))
        revert(&x);
    delast(&x);
    showall(x);
    knotfree(&x);
}
