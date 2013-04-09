#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const char arquivo[] = "database.ini";

struct _vhs
{
   char titulo[100]; //Maximo de 100 caracteres, n�o s�o permitidos espa�os
   int ano;          //Ano de lan�amento
   double valor;     //Pre�o 
};

void ler_database(struct _vhs vhs[],int tamanho)  
{
     if(tamanho==0)return;
     int x;
     for(x=0;x<tamanho;x++)
        {
             char buffer[12];
             sprintf(buffer,"titulo_%d",x);
             /*
             sprintf(LPCSTR , LPCSTR , ...)
             sprintf � uma fun��o que, ao inves de escrever no terminal o texto formatado,
             ele guarda numa variavel o que ele iria escrever. Neste caso, a string
             buffer recebe a string formatada de "titulo_%d". A sintaxe � identica
             ao printf normal, s� que o primeiro argumento � a string que ir�
             receber a string formatada.
             */
             GetPrivateProfileString(buffer,"titulo",NULL,vhs[x].titulo,100,arquivo);
             /*
             GetPrivateProfileString(LPCSTR , LPCSTR , NULL , LPCSTR , INT , LPCSTR)
             GetPrivateProfileString vai retornar uma string contida num arquivo INI
             O primeiro argumento � a chave identificadora no arquivo.
             O segundo argumento � a variavel que voc� quer obter o valor.
             O terceiro argumento � nulo, para mais informa��es consulte o MSDN
             O quarto valor � a variavel que ir� receber a string
             O quinto argumento � o tamanho da string do quarto argumento
             O sexto argumento � o nome do arquivo INI que estamos trabalhando
             */
             char buffer_2[10];
             GetPrivateProfileString(buffer,"valor",NULL,buffer_2,10,arquivo);
             vhs[x].valor = atof(buffer_2);
             /*
             As fun��es para manipular arquivos INI n�o s�o capazes de ler valores
             FLOAT/DOUBLE nativamente, para isso, n�s lemos uma STRING e convertemos
             para DOUBLE usando a fun��o atof
             double atof( LPCSTR )
             o unico argumento desta fun��o, � a string que ser� convertida, o
             retorno dela � um DOUBLE
             */
             vhs[x].ano = GetPrivateProfileInt(buffer,"ano",0,arquivo);
             /*
             Assim como GetPrivateProfileString, GetPrivateProfileInt retorna
             um valor contido no arquivo INI, a unica diferen�a � que esta
             fun��o retorna um INT
             uint GetPrivateProfileInt( LPCSTR , LPCSTR , INT , LPCSTR)
             O primeiro argumento � a chave identificadora no arquivo
             O segundo argumento � a variavel a ser lida
             O terceiro argumento � o valor de retorno caso a fun��o n�o encontre a variavel
             O quarto argumento � o arquivo INI que estamos trabalhando
             
             UINT = Unsigned INT (Inteiro sem sinal ou seja, n�o existe negativo)
             nota: No site da microsoft diz que o retorno � UINT, mas eu acredito
             que va sim ler valores negativos no INI            
             */
             }
 }

int main()
{
    int tamanho = GetPrivateProfileInt("VHS","quantidade",0,arquivo);
    struct _vhs vhs[tamanho];
    ler_database(vhs,tamanho);
    int x;
    for(x = 0;x<tamanho;x++)
    printf("%s\n%d\n%.2f\n\n",vhs[x].titulo,vhs[x].ano,vhs[x].valor);
    system("PAUSE");
 }
