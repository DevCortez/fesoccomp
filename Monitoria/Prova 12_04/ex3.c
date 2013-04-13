int main()
{
	float altura, raio;
	scanf("%f", &altura);
	scanf("%f", &raio);
	float pi = 3.14;
	float area = ( pi * raio * raio ) + ( 2 * pi * raio * altura );
	//Cada lata pinta 15m²
	int lata = area / 15;
	//Caso tenha fração, é necessario aumentar a quantidade de latas para suprir a necessidade
	while( lata * 15 < area )
		lata++;
	int total = lata * 50;
	printf("Custo: %d\nQuantidade: %d\n", total, lata);
}
