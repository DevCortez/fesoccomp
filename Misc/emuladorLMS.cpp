#include <cstdlib>
#include <iostream>

struct _memoria {
       int opcode;
       int arg;
       };
struct _ambiente {
       _memoria memoria[100];
       int eip;
       int pilha;
       }; 

using namespace std;

    void leitura (struct _memoria memoria[100]){
         int i,opcode,arg;
         printf("digite o código e após digite um numero negativo para encerrar função\n");
         for (i=0;i<100;i++){                     
             scanf("%2d%2d",&opcode,&arg);
             if (opcode<0)
                 break;
             memoria[i].opcode=opcode;
             memoria[i].arg=arg;   
         }// fim do for
    }//fim da leitura

    int executar (struct _ambiente *ambiente){
         int opcode = ambiente->memoria[ambiente->eip].opcode;
         int arg = ambiente->memoria[ambiente->eip].arg;
         
         switch (opcode){
                case 10: scanf ("%d", &ambiente->memoria[arg].arg);
                     break;
                case 11: printf ("%d\n", ambiente->memoria[arg].arg);
                     break;
                case 20: ambiente->pilha = ambiente->memoria[arg].arg;
                     break;
                case 21: ambiente->memoria[arg].arg = ambiente->pilha;
                     break;
                case 30: ambiente->pilha += ambiente->memoria[arg].arg;
                     break;
                case 31: ambiente->pilha -= ambiente->memoria[arg].arg;
                     break;
                case 32: ambiente->pilha *= ambiente->memoria[arg].arg;
                     break;
                case 40: ambiente->eip = arg;
                     break;
                case 41: if (ambiente->pilha<0)
                            ambiente->eip = arg;
                         break;
                case 42: if (ambiente->pilha==0)
                            ambiente->eip = arg;
                         break;
                case 43: return 0;
         }
         if ((opcode!=40) || (opcode!=41) || (opcode!=42))
                         ambiente->eip++;
                         return 1;
    }


int main(int argc, char *argv[])
{
    _ambiente ambiente;
    leitura(ambiente.memoria);
    ambiente.eip = 0;
    ambiente.pilha = 0;
    system("CLS");
    while(executar(&ambiente)==1){}
    system("PAUSE");
}
