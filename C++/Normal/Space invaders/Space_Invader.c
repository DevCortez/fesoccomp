#include <windows.h>

#define FPS 30
#define VEL_JOGO 1.2
#define VEL_TIRO 0.6
#define VEL_INIMIGO 0.1
#define INTERVALO_TIRO 250
#define LINHAS 20
#define COLUNAS 80
#define ICONE_JOGADOR 197
#define ICONE_TIRO 167
#define ICONE_PAREDE 205
#define ICONE_INIMIGO 206
#define DIFICULDADE 1


int sair = 0;

struct entidade
{
    float x, y, energia;
};

struct entidade jogador;

struct entidade tiro[ 100 ];
int tiro_c;
int last;

struct entidade tiro_inimigo[ 100 ];
int tiro_inimigo_c;

struct entidade parede[ 100 ];
int parede_c;

struct entidade inimigo[ 100 ];
int inimigo_c;
int direction;

void key_handler()
{
    if(GetAsyncKeyState(VK_LEFT))
        jogador.x = (jogador.x - VEL_JOGO) < 0 ? 0 : (jogador.x - VEL_JOGO);
    if(GetAsyncKeyState(VK_RIGHT))
        jogador.x = (jogador.x + VEL_JOGO) > (COLUNAS - 2) ? COLUNAS - 2 : (jogador.x + VEL_JOGO);

    if(GetAsyncKeyState(VK_SPACE))
    {
        if((GetTickCount() - last) > INTERVALO_TIRO)
        {
            //printf("\n%X\n" ,( last));
            tiro[ tiro_c ].y = LINHAS - 1;
            tiro[ tiro_c ].x = jogador.x;
            tiro_c++;
            last = GetTickCount();
        }
    }
}

void inicializar()
{
    jogador.y = LINHAS - 1;
    jogador.x = (int)(COLUNAS / 2);
    tiro_c = 0;
    parede_c = 0;
    int x, y;
    for(y = 5; y < COLUNAS - 14; y += 15)
        for(x = 0; x < 10; x++)
        {
            parede[ parede_c ].y = LINHAS - 5;
            parede[ parede_c ].x = x + y;
            parede_c++;
        }
    inimigo_c = 0;
    for(y = 0; y < 4; y++)
        for(x = 0; x < (int)(COLUNAS / 2); x+=5)
        {
            inimigo[ inimigo_c ].y = y * 2;
            inimigo[ inimigo_c ].x = x;
            inimigo_c++;
        }
    direction = 1;
    tiro_inimigo_c = 0;
    srand(GetTickCount());
}

void wait(int x)
{
    x += GetTickCount();
    while(GetTickCount() < x)
        Sleep(1);
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenhar()
{
    char buffer[ LINHAS ][ COLUNAS ];
    memset( buffer, ' ', LINHAS * COLUNAS );

    int _a;

    for( _a = 0; _a < LINHAS; _a++ )
        buffer[ _a ][ COLUNAS - 1 ] = 0;

    //Coloca entidades no buffer
    buffer[ (int)jogador.y ][ (int)jogador.x ] = ICONE_JOGADOR;

    for(_a = 0; _a < tiro_c; _a++)
        buffer[ (int)tiro[ _a ].y ][ (int)tiro[ _a ].x ] = ICONE_TIRO;

    for(_a = 0; _a < tiro_inimigo_c; _a++)
        buffer[ (int)tiro_inimigo[ _a ].y ][ (int)tiro_inimigo[ _a ].x ] = ICONE_TIRO;

    for(_a = 0; _a < parede_c; _a++)
        buffer[ (int)parede[ _a ].y ][ (int)parede[ _a ].x ] = ICONE_PAREDE;

    for(_a = 0; _a < inimigo_c; _a++)
        buffer[ (int)inimigo[ _a ].y ][ (int)inimigo[ _a ].x ] = ICONE_INIMIGO;

    gotoxy( 0, 0 );
    for( _a = 0; _a < LINHAS; _a++ )
        printf( "%s\n", buffer[ _a ] );
}

void processar_jogo()
{
    int a, b;

    if(direction)
    {
        for(a = 0; a < inimigo_c; a++)
            if( (int)(inimigo[ a ].x += VEL_INIMIGO) >= COLUNAS - 3 )
            {
                direction ^= 1;
                for(b = 0; b < inimigo_c; b++)
                    inimigo[ b ].y += 1;
                break;
            }
            else
            if(rand() % 1000 <= DIFICULDADE)
            {
                tiro_inimigo[ tiro_inimigo_c ].y = inimigo[ a ].y + 1;
                tiro_inimigo[ tiro_inimigo_c ].x = inimigo[ a ].x;
                tiro_inimigo_c++;
            }
    }
    else
        for(a = 0; a < inimigo_c; a++)
            if( (int)(inimigo[ a ].x -= VEL_INIMIGO) == 0 )
            {
                direction ^= 1;
                for(b = 0; b < inimigo_c; b++)
                    inimigo[ b ].y += 1;
                break;
            }
            else
            if(rand() % 1000 <= DIFICULDADE)
            {
                tiro_inimigo[ tiro_inimigo_c ].y = inimigo[ a ].y + 1;
                tiro_inimigo[ tiro_inimigo_c ].x = inimigo[ a ].x;
                tiro_inimigo_c++;
            }




    for(a = 0; a < tiro_c; a++)
        tiro[ a ].y -= VEL_TIRO;

    for(a = 0; a < tiro_inimigo_c; a++)
        tiro_inimigo[ a ].y += VEL_TIRO;

    for(a = 0; a < tiro_c; a++)
        if(tiro[ a ].y < 0)
        {
            tiro[ a ].y = tiro[ tiro_c -1 ].y;
            tiro[ a ].x = tiro[ tiro_c -1 ].x;
            tiro_c--;
        }

    for(a = 0; a < tiro_inimigo_c; a++)
        if(tiro_inimigo[ a ].y > LINHAS )
        {
            tiro_inimigo[ a ].y = tiro_inimigo[ tiro_inimigo_c -1 ].y;
            tiro_inimigo[ a ].x = tiro_inimigo[ tiro_inimigo_c -1 ].x;
            tiro_inimigo_c--;
        }

    for(a = 0; a < tiro_c; a++)
        for(b = 0; b < parede_c; b++)
                if(((int)tiro[ a ].y == (int)parede[ b ].y) && ((int)tiro[ a ].x == (int)parede[ b ].x))
                {
                    (int)tiro[ a ].y = (int)tiro[ tiro_c -1 ].y;
                    (int)tiro[ a ].x = (int)tiro[ tiro_c -1 ].x;
                    tiro_c--;
                    (int)parede[ b ].y = (int)parede[ parede_c -1 ].y;
                    (int)parede[ b ].x = (int)parede[ parede_c -1 ].x;
                    parede_c--;
                }

    for(a = 0; a < tiro_inimigo_c; a++)
        for(b = 0; b < parede_c; b++)
                if(((int)tiro_inimigo[ a ].y == (int)parede[ b ].y) && ((int)tiro_inimigo[ a ].x == (int)parede[ b ].x))
                {
                    (int)tiro_inimigo[ a ].y = (int)tiro_inimigo[ tiro_inimigo_c -1 ].y;
                    (int)tiro_inimigo[ a ].x = (int)tiro_inimigo[ tiro_inimigo_c -1 ].x;
                    tiro_inimigo_c--;
                    (int)parede[ b ].y = (int)parede[ parede_c -1 ].y;
                    (int)parede[ b ].x = (int)parede[ parede_c -1 ].x;
                    parede_c--;
                }

    for(a = 0; a < tiro_c; a++)
        for(b = 0; b < inimigo_c; b++)
                if(((int)tiro[ a ].y == (int)inimigo[ b ].y) && ((int)tiro[ a ].x == (int)inimigo[ b ].x))
                {
                    (int)tiro[ a ].y = (int)tiro[ tiro_c -1 ].y;
                    (int)tiro[ a ].x = (int)tiro[ tiro_c -1 ].x;
                    tiro_c--;
                    (int)inimigo[ b ].y = (int)inimigo[ inimigo_c -1 ].y;
                    (int)inimigo[ b ].x = (int)inimigo[ inimigo_c -1 ].x;
                    inimigo_c--;
                }

    for(a = 0; a < tiro_inimigo_c; a++)
        if(((int)tiro_inimigo[ a ].y == (int)jogador.y) && ((int)tiro_inimigo[ a ].x == (int)jogador.x))
        {
            system("CLS");
            printf("Jogo perdido :)\n");
            system("PAUSE");
            sair = 1;
        }


}

void jogar()
{
    inicializar();
    while(!sair)
    {
        key_handler();
        processar_jogo();
        desenhar();
        wait( 1000 / FPS );
    }
}

int main()
{
    jogar();
}
