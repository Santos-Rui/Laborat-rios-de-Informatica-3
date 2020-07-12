import java.util.Comparator;
import java.util.Map;


public class KeyComparatorFloat implements Comparator<Map.Entry<String, Float>> {
	@Override
	public int compare(Map.Entry<String, Float> e1, Map.Entry<String, Float> e2) {
		if (e1.getValue() < e2.getValue())
			return 1;
		else if (e1.getValue() > e2.getValue())
			return -1;
		else
			return e1.getKey().compareTo(e2.getKey());
	}
}