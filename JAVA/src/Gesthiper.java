import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.SortedSet;
import java.util.TreeSet;


public class Gesthiper implements Serializable {
	private static final long serialVersionUID = -3380100365397670493L;
	private String clientsFile;
	private String productsFile;
	private String salesFile;
	private Catalog clientCatalog;
	private Catalog productCatalog;
	private Accounting accounting;
	private SalesRecord record;
	private int invalidSales;
	
	public Gesthiper(String clientsFile, String productsFile, String salesFile) throws IOException {
		this();
		
		this.clientsFile = clientsFile;
		this.productsFile = productsFile;
		this.salesFile = salesFile;
		
		this.readClientsFile(clientsFile);
		this.readProductsFile(productsFile);
		this.accounting.populate(this.productCatalog);
		this.record.populate(this.clientCatalog);
		this.readSalesFile(salesFile);
	}
	
	public Gesthiper() {
		this.clientCatalog = new Catalog();
		this.productCatalog = new Catalog();
		this.accounting = new Accounting();
		this.record = new SalesRecord();
	}
	
	public static Gesthiper createFromFile(String file) throws FileNotFoundException, IOException, ClassNotFoundException {
		FileInputStream fis = new FileInputStream(file);
		ObjectInputStream ois = new ObjectInputStream (fis);
		
		Object obj = ois.readObject();
		ois.close();
		
		if (obj instanceof Gesthiper) {
			return (Gesthiper)obj;
		}
	
		return null;
	}
	
	public void readCatalogFile(String filename, Catalog c) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader(filename));
		String line;
		
		while((line = br.readLine()) != null) {
			c.add(line);
		}
		
		br.close();
	}
	
	public void readSalesFile(String filename) throws IOException {
			BufferedReader br = new BufferedReader( new FileReader("Compras.txt") );
			String line;
			
			while((line = br.readLine()) != null) {
				String[] s = line.split(" ");
				
				String product = s[0];
				String client = s[4];
				int quantity = Integer.parseInt(s[2]);
				float value = Float.parseFloat(s[1]);
				int month = Integer.parseInt(s[5]) - 1;

				if (!clientCatalog.contains(client) || !productCatalog.contains(product)) {
					invalidSales++;
				}
				else if (s[3].equals("N")) {
					accounting.addNSale(product, month, quantity, value);
					record.addSale(client, product, month, quantity, value);
				}
				else if (s[3].equals("P")) {
					accounting.addPSale(product, month, quantity, value);
					record.addSale(client, product, month, quantity, value);
				}
				else {
					invalidSales++;
				}
			}
			
			br.close();
	}
	
	public void readClientsFile(String filename) throws IOException {
		this.clientCatalog = new Catalog();
		
		this.readCatalogFile(filename, this.clientCatalog);
	}
	
	public void readProductsFile(String filename) throws IOException {
		this.productCatalog = new Catalog();
		
		this.readCatalogFile(filename, this.productCatalog);
	}
	
	public List<String> getProductsNeverBought() {
		return this.accounting.getProductsBought(0);
	}
	
	public int getTotalProducts() {
		return this.accounting.size();
	}
	
	public int getTotalProductsBought() {
		return this.accounting.getTotalProductsBought();
	}
	
	public int getTotalProductsNeverBought() {
		return this.getTotalProducts() - this.getTotalProductsBought();
	}
	
	public float getAnnualBilling() {
		return this.accounting.getBilling();
	}
	
	public int getTotalClients() {
		return this.record.size();
	}
	
	public int getTotalClientsWithRecord() {
		return this.record.getTotalClientsWithRecord();
	}
	
	public int getTotalClientsWithoutRecord() {
		return this.getTotalClients() - this.getTotalClientsWithRecord();
	}
	
	public int getTotalZeroValuedSales() {
		return this.record.getTotalZeroValuedSales();
	}
	
	public int[] getSalesByMonth() {
		int[] a = new int[12];
		
		for (int i = 0; i < 12; i++) {
			a[i] = this.accounting.getSales(i);
		}
		
		return a;
	}
	
	public float[] getBillingByMonth() {
		float[] a = new float[12];
		
		for (int i = 0; i < 12; i++) {
			a[i] = this.accounting.getBilling(i);
		}
		
		return a;
	}
	
	public int[] getClientsByMonth() {
		int[] a = new int[12];
		
		for (int i = 0; i < 12; i++) {
			a[i] = this.record.getTotalClients(i);
		}
		
		return a;
	}
	
	public int getInvalidSales() {
		return this.invalidSales;
	}
	
	public List<String> getClientsWithoutRecords() {
		return this.record.getClientsWith(0);
	}
	
	public SortedSet<Map.Entry<String, Integer>> getClientDiffProds(String client) {
		SortedSet<Map.Entry<String, Integer>> m = new TreeSet<>(new KeyComparator());
		
		m.addAll(this.record.getClientDiffProds(client).entrySet());
		
		return m;
	}
	
	public SortedSet<Map.Entry<String, Integer>> getBestSelling(int n) {
		List<String> l = this.accounting.getBestSelling(n);
		Map<String, Integer> m = new HashMap<String, Integer>();
		
		for (String s : l) {
			m.put(s, this.record.getTotalClients(s));
		}
		
		SortedSet<Map.Entry<String, Integer>> set = new TreeSet<>(new KeyComparator());
		set.addAll(m.entrySet());
		
		return set;
	}
	
	public SortedSet<Map.Entry<String, Integer>> getClientsDiversity() {
		Map<String, Integer> m = this.record.getClientsDiversity();
		
		SortedSet<Map.Entry<String, Integer>> set = new TreeSet<>(new KeyComparator());
		set.addAll(m.entrySet());
		
		return set;
	}
	
	public SortedSet<Map.Entry<String, Integer>> getClientsWhoBought(String prod) {
		Map<String, Integer> m = this.record.getClientsWhoBought(prod);
		
		SortedSet<Map.Entry<String, Integer>> set = new TreeSet<>(new KeyComparator());
		set.addAll(m.entrySet());
		
		return set;
	}
	
	public float getClientProductBilling(String client, String prod) {
		return this.record.getClientProductBilling(client, prod);
	}
	
	public void save(String file) throws IOException {
		FileOutputStream fos = new FileOutputStream(file);
		ObjectOutputStream oos = new ObjectOutputStream(fos);
		oos.writeObject(this);
		oos.close();
	}
	
	public String getClientsFile() {
		return this.clientsFile;
	}
	
	public String getProductsFile() {
		return this.productsFile;
	}
	
	public String getSalesFile() {
		return this.salesFile;
	}
	
	public int[] getClientSalesByMonth(String client) {
		int[] sales = new int[12];
		
		for (int i = 0; i < 12; i++) {
			sales[i] = this.record.getClientSales(client, i);
		}
		
		return sales;
	}
	
	public float[] getClientBillingByMonth(String client) {
		float[] billing = new float[12];
		
		for (int i = 0; i < 12; i++) {
			billing[i] = this.record.getClientBilling(client, i);
		}
		
		return billing;
	}
	
	public int[] getClientProductsByMonth(String client) {
		int[] prods = new int[12];
		
		for (int i = 0; i < 12; i++) {
			prods[i] = this.record.getClientTotalDiffProds(client, i);
		}
		
		return prods;
	}
	
	public int[] getClientsWhoBoughtByMonth(String prod) {
		int[] cls = new int[12];
		
		for (int i = 0; i < 12; i++) {
			cls[i] = this.record.getTotalClients(prod, i);
		}
		
		return cls;
	}
	
	public float[] getProductBillingByMonth(String prod) {
		float[] billing = new float[12];
		
		for (int i = 0; i < 12; i++) {
			billing[i] = this.accounting.getProductBilling(prod, i);
		}
		
		return billing;
	}
	
	public int[] getProductSalesByMonth(String prod) {
		int[] sales = new int[12];
		
		for (int i = 0; i < 12; i++) {
			sales[i] = this.accounting.getProductSales(prod, i);
		}
		
		return sales;
	}
	
	public int[] getProductNSalesByMonth(String prod) {
		int[] sales = new int[12];
		
		for (int i = 0; i < 12; i++) {
			sales[i] = this.accounting.getProductNSales(prod, i);
		}
		
		return sales;
	}
	
	public int[] getProductPSalesByMonth(String prod) {
		int[] sales = new int[12];
		
		for (int i = 0; i < 12; i++) {
			sales[i] = this.accounting.getProductPSales(prod, i);
		}
		
		return sales;
	}
	
	public float[] getProductNBillingByMonth(String prod) {
		float[] sales = new float[12];
		
		for (int i = 0; i < 12; i++) {
			sales[i] = this.accounting.getProductNBilling(prod, i);
		}
		
		return sales;
	}
	
	public float[] getProductPBillingByMonth(String prod) {
		float[] sales = new float[12];
		
		for (int i = 0; i < 12; i++) {
			sales[i] = this.accounting.getProductPBilling(prod, i);
		}
		
		return sales;
	}
}
