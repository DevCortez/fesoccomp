struct _knot
{
    int valor;
    void* next;
};

typedef int bool;
#define knot struct _knot
#define true 1
#define false 0
#define newknot malloc(sizeof(knot));

void add(void** x, int valor);              //Adiciona um valor no final da lista
void showall(void* x);                      //Mostra todos os valores na lista
bool addpos(void** x, int pos, int valor);  //Adiciona um valor numa posi��o especifica
void addorder(void** x, int valor);         //Adiciona um valor em ordem
bool addunique(void** x, int valor);        //Adiciona um valor apenas se for unico, retorna falso se n�o for
bool del(void** x, int pos);                //Deleta um n� na lista
bool delvalue(void** x, int valor);         //Deleta um n� pelo seu valor
void revert(void** x);                      //Inverte a ordem da lista
bool isinorder(void* x);                    //Verifica se a lista esta em ordem ou n�o
void delast(void** x);                      //Deleta o ultimo elemento da lista
void knotfree(void** x);                    //Libera todos os n�s da memoria
