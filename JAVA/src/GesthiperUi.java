import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;


public class GesthiperUi {
	private static final String OBJECT_FILE = "hipermercado.obj"; 
	private static Gesthiper gh;
	private static List<MenuOption> menu;
	private static boolean exit = false;
	private static Scanner reader = new Scanner(System.in);
	private static String[] months = new String[] {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	
	static {
		menu = new ArrayList<>();
		menu.add((new MenuOption("Query 1") { public void run() {query1();} }));
		menu.add((new MenuOption("Query 2") { public void run() {query2();} }));
		menu.add((new MenuOption("Query 3") { public void run() {query3();} }));
		menu.add((new MenuOption("Query 4") { public void run() {query4();} }));
		menu.add((new MenuOption("Query 5") { public void run() {query5();} }));
		menu.add((new MenuOption("Query 6") { public void run() {query6();} }));
		menu.add((new MenuOption("Query 7") { public void run() {query7();} }));
		menu.add((new MenuOption("Query 8") { public void run() {query8();} }));
		menu.add((new MenuOption("Query 9") { public void run() {query9();} }));
		menu.add((new MenuOption("Query 10") { public void run() {query10();} }));
		menu.add((new MenuOption("Stats1") { public void run() {stats1();} }));
		menu.add((new MenuOption("Stats2") { public void run() {stats2();} }));
		menu.add((new MenuOption("save") { public void run() {save();} }));
		menu.add((new MenuOption("exit") { public void run() {exit();} }));
	}
	
	private static abstract class MenuOption {
		public String title;
		public abstract void run();
		
		public MenuOption(String title) { this.title = title; }
	}
	
	public static void showMenu() {
		for (int i = 0; i < menu.size(); i++) {
			System.out.println(i + "\t" + menu.get(i).title);
		}
	}
	
	public static void gesthiperTitle() {
		System.out.println("*********************************");
		System.out.println("*                               *");
		System.out.println("*           GESTHIPER           *");
		System.out.println("*                               *");
		System.out.println("*********************************");
		
	}
	public static void showTitle(String s) {
		String title = " ----- " + s + " ----- \n";
		System.out.println(title);
	}
	
	public static void query1() {
		showTitle("QUERY 1");
		List<String> prods = gh.getProductsNeverBought();
		
		for (String prod : prods) {
			System.out.println(prod);
		}
		
		System.out.println();
		System.out.println("TOTAL: " + prods.size());
	}
	
	public static void query2() {
		showTitle("QUERY 2");
		List<String> clients = gh.getClientsWithoutRecords();
		
		for (String c : clients) {
			System.out.println(c);
		}
		
		System.out.println();
		System.out.println("TOTAL: " + clients.size());
	}
	
	public static void query3() {
		showTitle("QUERY 3");
		
		System.out.println("MONTH : ");
		int m = reader.nextInt() - 1;
		reader.nextLine();
		
		int sales = gh.getSalesByMonth()[m];
		int clients = gh.getClientsByMonth()[m];
		
		System.out.println("SALES: " + sales);
		System.out.println("CLIENTS: " + clients);
	}
	
	public static void query4() {
		showTitle("QUERY 4");
		
		System.out.println("CLIENT : ");
		String c = reader.nextLine();
		
		int[] sales = gh.getClientSalesByMonth(c);
		int[] prods = gh.getClientProductsByMonth(c);
		float[] billing = gh.getClientBillingByMonth(c);
		float totalBilling = 0;
		
		System.out.println("MONTH | SALES | PRODUCTS | BILLING");
		
		for (int i = 0; i < 12; i++) {
			System.out.println(months[i] + " " + sales[i] + " " + prods[i] + " " + billing[i]);
			totalBilling += billing[i];
		}
		
		System.out.println("TOTAL BILLING: " + totalBilling);
	}
	
	public static void query5() {
		showTitle("QUERY 5");
		
		System.out.println("PRODUCT : ");
		String c = reader.nextLine();
		
		int[] clients = gh.getClientsWhoBoughtByMonth(c);
		int[] sales = gh.getProductSalesByMonth(c);
		float[] billing = gh.getProductBillingByMonth(c);
		float totalBilling = 0;
		
		System.out.println("MONTH | SALES | CLIENTS | BILLING");
		
		for (int i = 0; i < 12; i++) {
			System.out.println(months[i] + " " + sales[i] + " " + clients[i] + " " + billing[i]);
			totalBilling += billing[i];
		}
		
		System.out.println("TOTAL BILLING: " + totalBilling);
	}
	
	public static void query6() {
		showTitle("QUERY 6");
		
		System.out.println("PRODUCT : ");
		String c = reader.nextLine();
		
		int[] nsales = gh.getProductNSalesByMonth(c);
		int[] psales = gh.getProductPSalesByMonth(c);
		float[] nbilling = gh.getProductNBillingByMonth(c);
		float[] pbilling = gh.getProductPBillingByMonth(c);
		
		System.out.println("MONTH | N SALES | N BILLING | P SALES | P BILLING");
		
		for (int i = 0; i < 12; i++) {
			System.out.println(months[i] + " " + nsales[i] + " " + nbilling[i] + " " + psales[i] + " " + pbilling[i]);
		}
	}
	
	public static void query7() {
		showTitle("QUERY 7");
		
		System.out.println("CLIENT : ");
		String c = reader.nextLine();
		
		Set<Map.Entry<String, Integer>> prods = gh.getClientDiffProds(c);
		
		for (Map.Entry<String, Integer> p : prods) {
			System.out.println(p.getKey() + " " + p.getValue());
		}
	}
	
	public static void query8() {
		showTitle("QUERY 8");
		
		System.out.println("N : ");
		int i = reader.nextInt();
		reader.nextLine();
		
		Set<Map.Entry<String, Integer>> prods = gh.getBestSelling(i);
		
		for (Map.Entry<String, Integer> p : prods) {
			System.out.println(p.getKey() + " " + p.getValue());
		}
	}
	
	public static void query9() {
		showTitle("QUERY 9");
		
		System.out.println("N : ");
		int i = reader.nextInt();
		reader.nextLine();
		int counter = 0;
		
		Set<Map.Entry<String, Integer>> clients = gh.getClientsDiversity();
		
		for (Map.Entry<String, Integer> p : clients) {
			if (counter >= i)
				break;
			
			System.out.println(p.getKey() + " " + p.getValue());
			
			counter++;
		}
	}
	
	public static void query10() {
		showTitle("QUERY 10");
		
		System.out.println("PRODUCT: ");
		String prod = reader.nextLine();
		System.out.println("N: ");
		int n = reader.nextInt();
		reader.nextLine();
		
		Set<Map.Entry<String, Integer>> clients = gh.getClientsWhoBought(prod);
		Map<String, Float> m = new HashMap<>();
		
		int counter = 0;
		
		for (Map.Entry<String, Integer> e : clients) {
			m.put(e.getKey(), gh.getClientProductBilling(e.getKey(), prod));
		}
		
		Set<Map.Entry<String, Float>> f = new TreeSet<>(new KeyComparatorFloat());
		f.addAll(m.entrySet());
		
		for (Map.Entry<String, Float> e : f) {
			System.out.println(e.getKey() + " " + e.getValue());
		}
	}
	
	public static void stats1() {
		showTitle("STATS 1");
		
		System.out.println("CLIENTS FILE: " + gh.getClientsFile());
		System.out.println("PRODUCTS FILE: " + gh.getProductsFile());
		System.out.println("SALES FILE: " + gh.getSalesFile());
		System.out.println("PRODUCTS: " + gh.getTotalProducts());
		System.out.println("\tBOUGHT: " + gh.getTotalProductsBought());
		System.out.println("\tNEVER BOUGHT:" + gh.getTotalProductsNeverBought());
		System.out.println("CLIENTS: " + gh.getTotalClients());
		System.out.println("\tBUYERS: " + gh.getTotalClientsWithRecord());
		System.out.println("\tNON-BUYERS: " + gh.getTotalClientsWithoutRecord());
		System.out.println("0 VALUE SALES: " + gh.getTotalZeroValuedSales());
		System.out.println("TOTAL BILLING: " + gh.getAnnualBilling());
	}
	
	public static void stats2() {
		showTitle("STATS 2");
		
		int[] sales = gh.getSalesByMonth();
		float[] billing = gh.getBillingByMonth();
		int[] cl = gh.getClientsByMonth();
		
		System.out.println("SALES | BILLING | CLIENTS");
		for (int i = 0; i < 12; i++) {
			System.out.println("\t" + months[i] + ": " + sales[i] + " " + billing[i] + " " + cl[i]);
		}
		
		System.out.println("INVALID SALES: " + gh.getInvalidSales());
	}
	
	public static void save() {
		try {
			gh.save(OBJECT_FILE);
		}
		catch (Exception e) {
			System.out.println("ERROR");
		}
	}
	
	public static void exit() {
		exit = true;
	}
	
	public static void interpreter() {
		while (!exit) {
			gesthiperTitle();
			System.out.println();
			showMenu();
			int option = reader.nextInt();
			reader.nextLine();
			menu.get(option).run();
			System.out.println("PRESS ENTER TO CONTINUE");
			reader.nextLine();
		}
	}
	
	public static Gesthiper askFiles() throws IOException {
		System.out.print("CLIENTS FILE: ");
		String cf = reader.nextLine();
		
		System.out.print("PRODUCTS FILE: ");
		String pf = reader.nextLine();
		
		System.out.print("SALES FILE: ");
		String sf = reader.nextLine();
		
		return new Gesthiper(cf, pf, sf);
	}
	
	public static void main(String[] args) {
		gh = null;
		
		try {
			gh = Gesthiper.createFromFile(OBJECT_FILE);
		}
		catch (Exception e) {
			System.out.println("NO OBJECT FILE");
			while (gh == null) {
				try {
					gh = askFiles();
				}
				catch (Exception f) {

				}
			}
		}
		
		interpreter();
	}
}
