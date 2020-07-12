import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;


public class Accounting implements Serializable {
	private Map<String, AccountingProduct> accList;
	private int[] salesByMonth;
	private float[] billingByMonth;
	private float total;
	private int sales;
	private int totalProductsBought;
	
	private class AccountingProduct extends ArrayList<Tuple<SalesInfo, SalesInfo>> {
		float total;
		int sales;
		
		public AccountingProduct() {
			this.total = 0f;
			this.sales = 0;
			
			for (int i = 0; i < 12; i++) {
				this.add(new Tuple<>(new SalesInfo(), new SalesInfo()));
			}
		}
		
		public void addNSale(int month, int quantity, float value) {
			this.total += value * quantity;
			this.sales++;
			
			this.get(month).getFirst().addSale(quantity, value);
		}
		
		public void addPSale(int month, int quantity, float value) {
			this.total += value * quantity;
			this.sales++;
			
			this.get(month).getSecond().addSale(quantity, value);
		}
		
		public float getTotal() {
			return this.total;
		}
		
		public float getNTotal(int month) {
			return this.get(month).getFirst().getTotal();
		}
		
		public float getPTotal(int month) {
			return this.get(month).getSecond().getTotal();
		}
		
		public int getSales() {
			return this.sales;
		}
		
		public int getNSales(int month) {
			return this.get(month).getFirst().getSales();
		}
		
		public int getPSales(int month) {
			return this.get(month).getSecond().getSales();
		}
	}
	
	public Accounting() {
		this.accList = new TreeMap<>();
		this.total = 0f;
		this.sales = 0;
		this.totalProductsBought = 0;
		this.salesByMonth = new int[12];
		this.billingByMonth = new float[12];
		
		Arrays.fill(salesByMonth, 0);
		Arrays.fill(billingByMonth, 0);
	}
	
	public float getBilling() {
		int t = 0;
		
		for (float i : this.billingByMonth) {
			t += i;
		}
		
		return t;
	}
	
	public float getBilling(int month) {
		return this.billingByMonth[month];
	}
	
	public float getProductBilling(String prod) {
		return this.accList.get(prod).getTotal();
	}
	
	public float getProductBilling(String prod, int month) {
		return this.accList.get(prod).getNTotal(month) + this.accList.get(prod).getPTotal(month);
	}
	
	public float getProductNBilling(String prod, int month) {
		return this.accList.get(prod).getNTotal(month);
	}
	
	public float getProductPBilling(String prod, int month) {
		return this.accList.get(prod).getPTotal(month);
	}
	
	public int getProductSales(String prod) {
		return this.accList.get(prod).getSales();
	}
	
	public int getProductSales(String prod, int month) {
		return this.accList.get(prod).getNSales(month) + this.accList.get(prod).getNSales(month);
	}
	
	public int getProductNSales(String prod, int month) {
		return this.accList.get(prod).getNSales(month);
	}
	
	public int getProductPSales(String prod, int month) {
		return this.accList.get(prod).getPSales(month);
	}
	
	public int getTotalProductsBought() {
		return this.totalProductsBought;
	}
	
	public int getSales() {
		int t = 0;
		
		for (int i : this.salesByMonth) {
			t += i;
		}
		
		return t;
	}
	
	public int getSales(int month) {
		return this.salesByMonth[month];
	}
	
	public int size() {
		return this.accList.size();
	}
	
	private void addProduct(String code) {
		this.accList.put(code, new AccountingProduct());
	}
	
	public void populate(Iterable<String> set) {
		for (String s : set) {
			this.addProduct(s);
		}
	}
	
	private void updateData(String code, int month, int quantity, float value) {
		float t = value * quantity;
		this.total += t;
		this.sales++;
		this.salesByMonth[month]++;
		this.billingByMonth[month] += t;
		
		if (this.accList.get(code).getSales() == 0)
			this.totalProductsBought++;
	}
	
	public void addNSale(String code, int month, int quantity, float value) {
		this.updateData(code, month, quantity, value);
		
		this.accList.get(code).addNSale(month, quantity, value);
	}
	
	public void addPSale(String code, int month, int quantity, float value) {
		this.updateData(code, month, quantity, value);
		
		this.accList.get(code).addPSale(month, quantity, value);
	}
	
	public List<String> getProductsBought(int times) {
		List<String> l = new ArrayList<String>();
		
		for (Map.Entry<String, AccountingProduct> e : this.accList.entrySet()) {
			if (e.getValue().getSales() == times) {
				l.add(e.getKey());
				System.out.println(e.getKey());
			}
		}
		
		return l;
	}
	
	public List<String> getBestSelling(int n) {
		Set<Tuple<String, Integer>> s = new TreeSet<>(new Comparator<Tuple<String, Integer>>() {
			@Override
			public int compare(Tuple<String, Integer> e1, Tuple<String, Integer> e2) {
				if (e1.getSecond() > e2.getSecond())
					return 1;
				else if (e1.getSecond() < e2.getSecond())
					return -1;
				else
					return e1.getFirst().compareTo(e2.getFirst());
			}
		});
		
		for (Map.Entry<String, AccountingProduct> e : this.accList.entrySet()) {
			s.add(new Tuple(e.getKey(), e.getValue().getSales()));
		}
		
		List<String> l = new ArrayList<>();
		
		int counter = 0;
		
		for (Tuple<String, Integer> t : s) {
			if (counter == n)
				return l;
			
			l.add(t.getFirst());
		}
		
		return l;
	}
}
