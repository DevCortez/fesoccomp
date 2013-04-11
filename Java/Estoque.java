public class Estoque extends Produto
{
	private int quantidade;

	public void setQuantidade(int x){ quantidade = x; }
	public int getQuantidade(){ return quantidade; }

	public Estoque(int codigo, int quantidade)
	{
		super( codigo );
		this.quantidade = quantidade;
	}
}