#include <stdio.h>
#include <windows.h>
#include <conio.h>

const int tam = 50;

struct fila
{
       int valores[tam];
       int topo;
};

typedef struct fila _fila;

void inserir(_fila *f, int pos, int val)
{
     if(f->topo==tam)return;
     if(pos>(f->topo)+1)return;
     int x;
     f->topo++;
     for(x=f->topo; x>pos; x--)
           f->valores[x]=f->valores[x-1];
     f->valores[pos]=val;
     return;
 }

int remover(_fila *f,int pos)
{
    if(f->topo==-1) return 0;
    int res = f->valores[pos];
    int x;
    for(x=pos;x<f->topo;x++)
       f->valores[x]=f->valores[x+1];
    f->topo--;
    return res;
}

int menu()
{
    system("CLS");
    fflush(stdin);
    printf("1: Inserir valor no inicio da fila\n2: Inserir valor numa posicao especifica da fila\n3: Inserir valor no fim da fila\n4: Remover valor do inicio da fila\n5: Remover valor de uma posicao especifica da fila\n6: Remover valor do final da fila\n7: mostrar valor de uma posicao especifica da fila\n8: Mostrar toda a fila\n9: Sair\n");
    return getch();
}

int main()
{
  int x;
  _fila f;
  f.topo=-1;
  int buffer,buffer2,y;
  for(x=-1;x!='9';x=menu())
  {
                         fflush(stdin);
                         system("CLS");
                         switch(x)
                         {
                                  case '1': printf("Digite o valor:\n"); scanf("%d",&buffer); inserir(&f,0,buffer); break;
                                  case '2': printf("Digite o valor:\n"); scanf("%d",&buffer); printf("Digite a posicao:\n"); scanf("%d",&buffer2); inserir(&f,buffer2,buffer); break;
                                  case '3': printf("Digite o valor:\n"); scanf("%d",&buffer); inserir(&f,f.topo+1,buffer); break;
                                  case '4': printf("Valor removido %d\n",remover(&f,0)); getch(); break;
                                  case '5': printf("Digite a posicao\n"); scanf("%d",&buffer); printf("Valor removido %d\n",remover(&f,buffer)); getch(); break;
                                  case '6': printf("Valor removido %d\n",remover(&f,f.topo)); getch(); break;
                                  case '7': printf("Digite a posicao:\n"); scanf("%d",&buffer); printf("\nValor %d",f.valores[buffer]); getch(); break;
                                  case '8': for(y=0;y<=f.topo;y++)printf("%d: %d\n",y+1,f.valores[y]); getch(); break;
                                  }
                         }
}
