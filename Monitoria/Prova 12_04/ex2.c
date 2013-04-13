int main()
{
	int leitura;
	scanf("%d", &leitura);
	int h,m,s;
	s = leitura % 60;
	m = leitura / 60 % 60;
	h = leitura / (60 * 60);
	printf("%02d:%02d:%02d\n", h, m, s);
}
