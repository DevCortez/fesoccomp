public abstract class Produto
{
	protected String nome;
	protected double preco;
	protected int codigo;

	public void setNome(String x){ nome = x; }
	public void setPreco(double x){ preco = x; }
	public void setCodigo(int x){ codigo = x; }
	public String getNome(){ return nome; }
	public double getPreco(){ return preco; }
	public int getCodigo(){ return codigo; }

	public Produto(int x){ this.codigo = x; }
}