#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int casa[9];

int vez = 1;
int ganhou = 0;

void iniciar_jogo()
{
     int x;
     for(x=0;x<9;x++)casa[x]=0;
     vez = 1;
     ganhou = 0;
     }

void desenhar_jogo()
{
   system("CLS");
   cout << "Pressione ESC para fechar \nPressione ENTER para comecar um novo jogo\n\n";
   switch(casa[0])
   {              case 0: cout << "1 "; break;
                  case 1: cout << "X "; break;
                  case 2: cout << "O "; break;}
   switch(casa[1])
   {              case 0: cout << "2 "; break;
                  case 1: cout << "X "; break;
                  case 2: cout << "O "; break;}
   switch(casa[2])
   {              case 0: cout << "3\n"; break;
                  case 1: cout << "X\n"; break;
                  case 2: cout << "O\n"; break;}
   switch(casa[3])
   {              case 0: cout << "4 "; break;
                  case 1: cout << "X "; break;
                  case 2: cout << "O "; break;}
   switch(casa[4])
   {              case 0: cout << "5 "; break;
                  case 1: cout << "X "; break;
                  case 2: cout << "O "; break;}
   switch(casa[5])
   {              case 0: cout << "6\n"; break;
                  case 1: cout << "X\n"; break;
                  case 2: cout << "O\n"; break;}
   switch(casa[6])
   {              case 0: cout << "7 "; break;
                  case 1: cout << "X "; break;
                  case 2: cout << "O "; break;}
   switch(casa[7])
   {              case 0: cout << "8 "; break;
                  case 1: cout << "X "; break;
                  case 2: cout << "O "; break;}
   switch(casa[8])
   {              case 0: cout << "9"; break;
                  case 1: cout << "X"; break;
                  case 2: cout << "O"; break;}
   cout << endl << endl;
   if(vez == 1)cout << "Vez do X"; else cout << "Vez do O";
   cout << endl;
}

void verificar()
{
     int x;
     //Horizontal
     x = casa[0]*casa[0]+casa[1]*casa[1]+casa[2]*casa[2];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     x = casa[3]*casa[3]+casa[4]*casa[4]+casa[5]*casa[5];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     x = casa[6]*casa[6]+casa[7]*casa[7]+casa[8]*casa[8];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     //Vertical
     x = casa[0]*casa[0]+casa[3]*casa[3]+casa[6]*casa[6];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     x = casa[1]*casa[1]+casa[4]*casa[4]+casa[7]*casa[7];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     x = casa[2]*casa[2]+casa[5]*casa[5]+casa[8]*casa[8];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     //Diagonal
     x = casa[0]*casa[0]+casa[4]*casa[4]+casa[8]*casa[8];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     x = casa[2]*casa[2]+casa[4]*casa[4]+casa[6]*casa[6];
     if(x==3)ganhou = 1;
     if(x==12)ganhou = 2;
     }
     
void vencedor()
{
     system("CLS");
     if(ganhou == 1)cout << "O vencedor foi X"; else cout << "O vencedor foi O";
     cout << endl << "Pressione ENTER para um novo jogo" << endl;

     }

int main(int argc, char *argv[])
{
    bool sair = false;
    iniciar_jogo();
    while(!sair)
    {
                if(ganhou == 0) desenhar_jogo(); else vencedor();
                int tecla = getch();
                switch(tecla)
                {
                             case 0x1b:sair = true; break;
                             case (byte)'1': if(casa[0]!=0)break; casa[0]=vez; vez ^= 3; break;
                             case (byte)'2': if(casa[1]!=0)break; casa[1]=vez; vez ^= 3; break;
                             case (byte)'3': if(casa[2]!=0)break; casa[2]=vez; vez ^= 3; break;
                             case (byte)'4': if(casa[3]!=0)break; casa[3]=vez; vez ^= 3; break;
                             case (byte)'5': if(casa[4]!=0)break; casa[4]=vez; vez ^= 3; break;
                             case (byte)'6': if(casa[5]!=0)break; casa[5]=vez; vez ^= 3; break;
                             case (byte)'7': if(casa[6]!=0)break; casa[6]=vez; vez ^= 3; break;
                             case (byte)'8': if(casa[7]!=0)break; casa[7]=vez; vez ^= 3; break;
                             case (byte)'9': if(casa[8]!=0)break; casa[8]=vez; vez ^= 3; break;
                             case 13:iniciar_jogo(); break;
                             }
                verificar();
                }
}
