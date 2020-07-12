import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class SalesRecord implements Serializable {
	private Map<String, ProductList> sales;
	private int[] clientsByMonth;
	private int clientsWithRecord;
	private int zeroValuedSales;
	
	private class ProductList extends HashMap<String, List<SalesInfo>> {
		private int[] recordsByMonth;
		private float total;
		
		public ProductList() {
			super();
			this.recordsByMonth = new int[12];
			this.total = 0;
			Arrays.fill(recordsByMonth, 0);
		}
		
		private void addProduct(String code) {
			List<SalesInfo> l = new ArrayList<>();
			
			for (int i = 0; i < 12; i++) {
				l.add(new SalesInfo());
			}
			
			this.put(code,  l);
 		}
		
		public void addSale(String code, int month, int quantity, float value) {
			if (!this.containsKey(code)) {
				this.addProduct(code);
			}
			
			this.recordsByMonth[month]++;
			this.total += quantity * value;
			
			this.get(code).get(month).addSale(quantity, value);
		}
		
		public int getTotalRecords() {
			int n = 0;
			
			for (int i : this.recordsByMonth) {
				n += i;
			}
			
			return n;
		}
		
		public int getTotalRecords(int month) {
			return this.recordsByMonth[month];
		}
		
		public float getTotal() {
			return this.total;
		}
	}
	
	public SalesRecord() {
		this.sales = new TreeMap<>();
		this.clientsWithRecord = 0;
		this.zeroValuedSales = 0;
		this.clientsByMonth = new int[12];
	}
	
	public void populate(Iterable<String> clients) {
		for (String s : clients) {
			this.addClient(s);
		}
	}
	
	public void addClient(String code) {
		this.sales.put(code, new ProductList());
	}
	
	public void addSale(String client, String product, int month, int quantity, float value) {
		ProductList l = this.sales.get(client);
		
		if (l.size() == 0)
			this.clientsWithRecord++;
		
		if (value == 0)
			this.zeroValuedSales++;
		
		if (l.getTotalRecords(month) == 0)
			this.clientsByMonth[month]++;
		
		this.sales.get(client).addSale(product, month, quantity, value);
	}
	
	public int size() {
		return this.sales.size();
	}
	
	public int getTotalClientsWithRecord() {
		return this.clientsWithRecord;
	}
	
	public int getTotalZeroValuedSales() {
		return this.zeroValuedSales;
	}
	
	public int getTotalClients(int month) {
		return this.clientsByMonth[month];
	}
	
	public int getTotalClients(String prod, int month) {
		int i = 0;
		
		for (ProductList p : this.sales.values()) {
			if (p.containsKey(prod)) {
				if (p.get(prod).get(month).getSales() != 0)
					i++;
			}
		}
		
		return i;
	}
	
	public int getTotalClients(String prod) {
		int n = 0;
		
		for (int i = 0; i < 12; i++) {
			n += this.getTotalClients(prod, i);
		}
		
		return n;
	}
	
	public List<String> getClientsWith(int quantity) {
		List<String> l = new ArrayList<>();
		
		for (Map.Entry<String, ProductList> e : this.sales.entrySet()) {
			if (e.getValue().getTotalRecords() == quantity) {
				l.add(e.getKey());
				System.out.println(e.getKey());
			}
		}
		
		return l;
	}
	
	public int getClientSales(String client, int month) {
		ProductList p = this.sales.get(client);
		int i = 0;
		
		for (List<SalesInfo> l : p.values()) {
			i += l.get(month).getSales();
		}
		
		return i;
	}
	
	public int getClientTotalDiffProds(String client, int month) {
		ProductList p = this.sales.get(client);
		int i = 0;
		
		for (List<SalesInfo> l : p.values()) {
			if (l.get(month).getSales() != 0)
				i++;
		}
		
		return i;
	}
	
	public Map<String, Integer> getClientDiffProds(String client) {
		Map<String, Integer> m = new HashMap<String, Integer>();
		
		for (Map.Entry<String, List<SalesInfo>> e : this.sales.get(client).entrySet()) {
			int sales = 0;
			
			for (SalesInfo s : e.getValue()) {
				sales += s.getSales();
			}
			
			m.put(e.getKey(), sales);
		}
		
		return m;
	}
	
	public Map<String, Integer> getClientsDiversity() {
		Map<String, Integer> m = new HashMap<String, Integer>();
		
		for (Map.Entry<String, ProductList> e : this.sales.entrySet()) {
			m.put(e.getKey(), e.getValue().size());
		}
		
		return m;
	}
	
	public float getClientBilling(String client) {
		return this.sales.get(client).getTotal();
	}
	
	public float getClientBilling(String client, int month) {
		ProductList p = this.sales.get(client);
		float f = 0;
		
		for (List<SalesInfo> l : p.values()) {
			f += l.get(month).getTotal();
		}
		
		return f;
	}
	
	public float getClientProductBilling(String client, String prod) {
		float f = 0;
		
		for (SalesInfo s : this.sales.get(client).get(prod)) {
			f += s.getTotal();
		}
		
		return f;
	}
	
	public int getClientProductTotal(String client, String prod) {
		int i = 0;
		
		for (SalesInfo s : this.sales.get(client).get(prod)) {
			i += s.getSales();
		}
		
		return i;
	}
	public Map<String, Integer> getClientsWhoBought(String prod) {
		Map<String, Integer> l = new HashMap<>();
		
		for (Map.Entry<String, ProductList> e : this.sales.entrySet()) {
			if (e.getValue().containsKey(prod)) {
				l.put(e.getKey(), this.getClientProductTotal(e.getKey(), prod));
			}
		}
		
		return l;
	}
}
