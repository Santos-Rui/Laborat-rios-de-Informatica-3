import java.util.TreeSet;


public class Catalog extends TreeSet<String> {
	
	public Catalog() {
		super();
	}
	
	public int count(String s) {
		char c = (char)(s.charAt(s.length() - 1) + 1);
		String next = s.substring(0, s.length() - 1) + c;
		
		return super.subSet(s, true, next, false).size();
	}
}
