#include "cadeia.h"

void add(void** x, int valor)
{
    knot* a = *x;
    if(!a)
    {
        *x = malloc(sizeof(knot));
        a = *x;
        a->valor = valor;
        a->next = 0;
        return;
    }
    a = *x;
    while(a->next)
        a = a->next;
    a->next = newknot;
    a = a->next;
    a->valor = valor;
    a->next = 0;
}

void showall(void* x)
{
    knot* a = x;
    while(a)
    {
        printf("[%08X @ %08X]: %d\n", a, x, a->valor);
        a = a->next;
    }
    printf("\n");
}

bool addpos(void** x, int pos, int valor)
{
    knot* a = *x;
    if(!a)
        return false;
    if(pos == 1)
    {
        void* y = a;
        *x = newknot;
        a = *x;
        a->next = y;
        a->valor = valor;
        return true;
    }
    pos-=2;
    while(pos-- && a->next)
        a = a->next;
    if(pos != -1)
        return false;
    knot* b = a->next;
    a = a->next = newknot;
    a->next = b;
    a->valor = valor;
    return true;
}

void addorder(void** x, int valor)
{
    knot* a = *x;
    int y = 0;
    while(a->next)
    {
        y++;
        knot* b = a->next;
        if(a->valor <= valor && b->valor > valor)
        {
            addpos(x, y, valor);
            return;
        }
        a = a->next;
    }
    add(x, valor);
}

bool addunique(void** x, int valor)
{
    knot* a = *x;
    while(a->next && (a->valor != valor))
        a = a->next;
    if(a->next || a->valor == valor)
        return false;
    add(x, valor);
}

bool del(void** x, int pos)
{
    knot* a = *x;
    if(pos == 1)
    {
        *x = a->next;
        free(a);
        return true;
    }
    pos -= 2;
    while(a->next && pos--)
        a = a->next;
    if(pos !=- 1)
        return false;
    knot* b = a->next;
    a->next = b->next;
    free(b);
    return true;
}

bool delvalue(void** x, int valor)
{
    knot* a = *x;
    int y = 0;
    while(a)
    {
        y++;
        if(a->valor == valor)
        {
            del(x, y);
            return true;
        }
        a = a->next;
    }
    return false;
}

void revert(void** x)
{
    knot* a = *x;
    int y = 1;
    while(y++ && a)
        a = a->next;
    y -= 2;
    void** buffer = malloc(y * sizeof(void*));
    a = *x;
    int z = y;
    while(a && y)
    {
        buffer[y] = a;
        a = a->next;
        y--;
    }
    *x = buffer[1];
    a = *x;
    a->next = buffer[2];
    y = 2;
    while(a && y<=z)
    {
        knot* b = a->next;
        a->next = buffer[y];
        a = a->next;
        y++;
    }
    a->next = 0;
}

bool isinorder(void* x)
{
    knot* a = x;
    while(a->next)
    {
        knot* b = a->next;
        if(b->valor < a->valor)
            return false;
        a = a->next;
    }
    return true;
}

void delast(void** x)
{
    knot* a = *x;
    int y = 1;
    while(a && y++)
        a = a->next;
    del(x, y-1);
}

void knotfree(void** x)
{
    knot* a = *x;
    while(a)
    {
        knot* b = a->next;
        free(a);
        a = b;
    }
}
