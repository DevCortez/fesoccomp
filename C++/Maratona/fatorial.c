int fatorial(int x)
{
    if(x<=1)
        return x;
    else
        return x * fatorial( x - 1 );
}

int main()
{
    printf("%d",fatorial(4));
}
