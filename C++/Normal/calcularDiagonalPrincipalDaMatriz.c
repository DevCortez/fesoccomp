#define write(x,y...) printf(#x,##y);
#define cls system("CLS");
#define pause system("PAUSE");
#define read(x,y,z,w...) { printf(#z,##w); scanf(#x,&y); }

int main()
{
    int tamanho;
    read( %d, tamanho,Digite o tamanho da matriz\n );
    cls;
    int (*matriz)[] = malloc( tamanho * tamanho ), x, y;
    for(x = 0; x < tamanho; x++)
        for(y = 0; y < tamanho; y++)
            read( %d, (*matriz)[y + x * tamanho], Digite o valor para a linha %d coluna %d:, x+1, y+1);
    int total = 0;
    for(x = 0; x < tamanho; x++)
        total += (*matriz)[x + x * tamanho];
    write(Total: %d\n, total);
}
