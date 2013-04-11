public class Carro extends Automovel
{
	protected int ano;
	protected double valor;

	public Carro(String chassi, String modelo, int ano, double valor)
	{
		super( chassi, modelo );
		this.ano = ano;
		this.valor = valor;
	}
}