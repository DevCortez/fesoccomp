#include <conio.h>
#include <stdio.h>
#include <windows.h>

struct _s {
       int top;
       char mem[50];
       };

typedef struct _s _p;
#define pause() system("PAUSE");

void push(_p *p,char x)
{
     p->mem[++p->top]=x;
 }

char pop(_p *p)
{
     return p->mem[p->top--];
 }


void leitura(char x[60])
{
   printf("Digite a equacao infixa:\n");
   fflush(stdin);
   gets(x);
 }

void mostrar(char x[60])
{
    printf("\nEquacao convertida:\n %s\n\n",x);
    pause();
}

int prioridade(char x)
{
    switch(x)
    {
      case '(': return 0;
      case '+':
      case '-': return 1;
      case '*':
      case '/': return 2;
    }
 }

void converter(char x[60],char y[60])
{
   _p p;
   p.top = -1;
   char buffer;
   for(int pos = 0; pos < strlen(x); pos++)
      {
          switch(x[pos])
             {
                 case                               '(': push(&p,'('); break;
                 case                               ')': while( (buffer=pop(&p)) != '(' ) y[strlen(y)]=buffer; break;
                 case '+': case '-': case '/': case '*': while( p.top>-1 && prioridade(x[pos]) <= prioridade(p.mem[p.top]) )y[strlen(y)]=pop(&p); push(&p,x[pos]); break;
                 default                               : y[strlen(y)]=x[pos]; break;
             }
      }
    while(p.top>-1) y[strlen(y)] = pop(&p);
}


int main()
{
    char infixo[60],posfixo[60] = {0};
    leitura(infixo);
    converter(infixo,posfixo);
    mostrar(posfixo);
 }
