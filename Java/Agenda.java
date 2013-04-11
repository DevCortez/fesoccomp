import javax.swing.JOptionPane;

public class Agenda
{
	private Carro[] elementos = new Carro[200];
	private int size = 0;

	public void add( String a, String b, int c, double d )
	{
		elementos[ size++ ] = new Carro( a, b, c, d );
	}

	public Carro find(String chassi)
	{
		for(int x = 0; x < size; x++)
			if(elementos[x].chassi == chassi)
				return elementos[x];
		return null;
	}

	public Carro find(int ano)
	{
		for(int x = 0; x < size; x++)
			if(elementos[x].ano == ano)
				return elementos[x];
		return null;
	}
}