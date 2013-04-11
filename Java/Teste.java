import javax.swing.JOptionPane;

public class Teste
{
	public static void main(String[] Args)
	{
		Agenda a = new Agenda();
		a.add( "chassi", "modelo", 1990, 0 );
		a.add( "chassi1", "modelo1", 2000, 0 );
		a.add( "chassi2", "modelo2", 2010, 0 );

		Carro teste = a.find( 2010 );

		JOptionPane.showMessageDialog(null, teste.chassi);
	}
}