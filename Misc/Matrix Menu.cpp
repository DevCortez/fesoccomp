#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct _pilha{
       int mem[50];
       int topo;
       };
_pilha p;

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//principal
char um[] = "1 Adicionar valor a pilha", dois[] = "2 Remover valor da pilha", tres[] = "3 Mostrar pilha", quatro[] = "4 Sair";
//adicionar valor
char adcv[]= "Digite o valor";

int sinal = 0, mainm = 0;



void animarmenu1()
{
     srand(time(NULL));
     for(int x=0;x<strlen(um);x++)
        {
             while(sinal)Sleep(rand()&3);
             if(mainm==0)ExitThread(1);
             sinal^=1;
             gotoxy(2,x+1);
             printf("%c",um[x]);
             Sleep(rand() & 0x3f);
             sinal^=1;
             Sleep(rand()&3);
         }
 }

void animarmenu2()
{
     srand(time(NULL));

     for(int x=0;x<strlen(dois);x++)
        {

             while(sinal)Sleep(rand()&3);
             if(mainm==0)ExitThread(1);
             sinal^=1;
             gotoxy(5,x+1);
             printf("%c",dois[x]);
             Sleep(rand() & 0x3f);
             sinal^=1;
             Sleep(rand()&3);
         }
 }

void animarmenu3()
{
     srand(time(NULL));

     for(int x=0;x<strlen(tres);x++)
        {
             while(sinal)Sleep(rand()&3);
             if(mainm==0)ExitThread(1);
             sinal^=1;
             gotoxy(8,x+1);
             printf("%c",tres[x]);
             Sleep(rand() & 0x3f);
             sinal^=1;
             Sleep(rand()&3);
         }
 }

void animarmenu4()
{
     srand(time(NULL));

     for(int x=0;x<strlen(quatro);x++)
        {
             while(sinal)Sleep(rand()&3);
             if(mainm==0)ExitThread(1);
             sinal^=1;
             gotoxy(11,x+1);
             printf("%c",quatro[x]);
             Sleep(rand() & 0x3f);
             sinal^=1;
             Sleep(rand()&3);
         }
 }

void animarmenuadc()
{
     srand(time(NULL));

     for(int x=0;x<strlen(adcv);x++)
        {
             gotoxy(1,x+1);
             printf("%c",adcv[x]);
             gotoxy(0,strlen(adcv)+2);
             Sleep((rand() & 0x3f)+50);
         }
 }

void push(int x)
{
     p.mem[p.topo++]=x;
 }

int pop()
{
     int x = p.mem[p.topo];
     p.topo--;
     return x;
 }

int queue()
{
    return p.mem[p.topo];
}

void zprintf(char x[])
{
     for(int y=0;y<strlen(x);y++,Sleep(rand()&0xf))
        printf("%c",x[y]);
 }

void ( __stdcall *_x)(int,int,int,int,int,int);
void menu()
{
   system("CLS");
   mainm=1;
   sinal=0;
   _x(0,0,(DWORD)&animarmenu1,0,0,0);
   _x(0,0,(DWORD)&animarmenu2,0,0,0);
   _x(0,0,(DWORD)&animarmenu3,0,0,0);
   _x(0,0,(DWORD)&animarmenu4,0,0,0);
 }

int adicionarvalor()
{
   system("CLS");
   mainm=0;
   Sleep(50);
   _x(0,0,(DWORD)&animarmenuadc,0,0,0);
   int buffer;
   fflush(stdin);
   scanf("%d",&buffer);
   return buffer;
 }

void mostrar()
{
     system("CLS");

     for(int x=0;x<p.topo;x++)
     {
             char buf[100];
             sprintf(buf,"\n %d: %d",x+1,p.mem[x]);
             zprintf(buf);
             }
     getch();
 }

int main(int argc, char *argv[])
{

    p.topo=0;

    *(DWORD*)(&_x) = (DWORD)&CreateThread;
    system("COLOR 0A");
    int opt=0;
    while(opt!='4'){
    menu();
    opt = getch();
    mainm=0;
    Sleep(90);
    switch(opt){
                case '1': push(adicionarvalor()); break;
                case '2': pop(); break;
                case '3': mostrar();

                     }
    }
    return EXIT_SUCCESS;
}
