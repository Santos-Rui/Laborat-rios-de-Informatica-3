import java.io.Serializable;


public class SalesInfo implements Serializable {
	private int sales;
	private float total;
	
	public SalesInfo() {
		sales = 0;
		total = 0.0f;
	}
	
	public SalesInfo(int sales, float total) {
		this.sales = sales;
		this.total = total;
	}
	
	public SalesInfo(SalesInfo si) {
		this.sales = si.sales;
		this.total = si.total;
	}
	
	public int getSales() {
		return this.sales;
	}
	
	public float getTotal() {
		return this.total;
	}
	
	public void addSale(float value) {
		this.sales++;
		this.total += value;
	}
	
	public void addSale(int quantity, float value) {
		this.sales += quantity;
		this.total += value * quantity;
	}
}
