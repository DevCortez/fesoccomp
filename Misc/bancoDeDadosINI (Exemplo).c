#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

const char arquivo[] = "database.ini";

struct _vhs
{
   char titulo[100]; //Maximo de 100 caracteres, não são permitidos espaços
   int ano;          //Ano de lançamento
   double valor;     //Preço 
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
             sprintf é uma função que, ao inves de escrever no terminal o texto formatado,
             ele guarda numa variavel o que ele iria escrever. Neste caso, a string
             buffer recebe a string formatada de "titulo_%d". A sintaxe é identica
             ao printf normal, só que o primeiro argumento é a string que irá
             receber a string formatada.
             */
             GetPrivateProfileString(buffer,"titulo",NULL,vhs[x].titulo,100,arquivo);
             /*
             GetPrivateProfileString(LPCSTR , LPCSTR , NULL , LPCSTR , INT , LPCSTR)
             GetPrivateProfileString vai retornar uma string contida num arquivo INI
             O primeiro argumento é a chave identificadora no arquivo.
             O segundo argumento é a variavel que você quer obter o valor.
             O terceiro argumento é nulo, para mais informações consulte o MSDN
             O quarto valor é a variavel que irá receber a string
             O quinto argumento é o tamanho da string do quarto argumento
             O sexto argumento é o nome do arquivo INI que estamos trabalhando
             */
             char buffer_2[10];
             GetPrivateProfileString(buffer,"valor",NULL,buffer_2,10,arquivo);
             vhs[x].valor = atof(buffer_2);
             /*
             As funções para manipular arquivos INI não são capazes de ler valores
             FLOAT/DOUBLE nativamente, para isso, nós lemos uma STRING e convertemos
             para DOUBLE usando a função atof
             double atof( LPCSTR )
             o unico argumento desta função, é a string que será convertida, o
             retorno dela é um DOUBLE
             */
             vhs[x].ano = GetPrivateProfileInt(buffer,"ano",0,arquivo);
             /*
             Assim como GetPrivateProfileString, GetPrivateProfileInt retorna
             um valor contido no arquivo INI, a unica diferença é que esta
             função retorna um INT
             uint GetPrivateProfileInt( LPCSTR , LPCSTR , INT , LPCSTR)
             O primeiro argumento é a chave identificadora no arquivo
             O segundo argumento é a variavel a ser lida
             O terceiro argumento é o valor de retorno caso a função não encontre a variavel
             O quarto argumento é o arquivo INI que estamos trabalhando
             
             UINT = Unsigned INT (Inteiro sem sinal ou seja, não existe negativo)
             nota: No site da microsoft diz que o retorno é UINT, mas eu acredito
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
