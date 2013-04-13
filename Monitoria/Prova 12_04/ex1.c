int main()
{
    int leitura, dias;
    float total;
    scanf("%d", &leitura);
    scanf("%d", &dias);
    switch(leitura)
    {
        case 101:
        	total = dias * 14.30;
        	break;
		case 102:
        	total = dias * 15.90;
        	break;
		case 103:
        	total = dias * 18.95;
        	break;
    }
    total *= 0.905;
    printf("%f\n", total);
}
