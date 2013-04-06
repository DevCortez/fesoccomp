#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

const int ncolunas = 74;

int x[0xfff];

void gotoxy(int xx, int y)
{
  COORD coord;
  coord.X = xx;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int gmin()
{
    int buf = x[0];
      for(int y=1;y<=ncolunas;y++) 
         if(buf>x[y])buf=x[y];
    return buf;
}

int gmax()
{
    int buf = x[0];
      for(int y=1;y<=ncolunas;y++) 
         if(buf<x[y])buf=x[y];
    return buf;
}

int zrand()
{
    int buf = rand() & 0xff;
    while(buf>ncolunas)buf-=ncolunas;
    return buf;
}

void renit()
{
     system("CLS");
     for(int y=0;y<=ncolunas;y++)
        x[y]=-1;
 }


int main(int argc, char *argv[])
{
    
    srand(time(NULL));
    for(int y=0;y<100;y++,x[y]=-1){}
    system("COLOR 0A");
    for(;;)
    {
           int coluna = zrand();
           //while(x[coluna]>gmin()+24)coluna = zrand();
           if(gmax()==25)renit();
           x[coluna]++;
           gotoxy(coluna,x[coluna]);
           int caracter = rand() & 0xff;
           while(caracter<34)caracter+=34;
           caracter--;
           
           printf("%c",caracter);
           Sleep(1); 
           }
    return EXIT_SUCCESS;
}
