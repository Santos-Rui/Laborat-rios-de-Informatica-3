import java.util.Comparator;
import java.util.Map;


public class KeyComparator implements Comparator<Map.Entry<String, Integer>> {
	@Override
	public int compare(Map.Entry<String, Integer> e1, Map.Entry<String, Integer> e2) {
		if (e1.getValue() < e2.getValue())
			return 1;
		else if (e1.getValue() > e2.getValue())
			return -1;
		else
			return e1.getKey().compareTo(e2.getKey());
	}
}
