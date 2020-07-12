import java.io.Serializable;


public class Tuple<T1, T2> implements Serializable {
	private T1 first;
	private T2 second;
	
	public Tuple(T1 first, T2 second) {
		this.first = first;
		this.second = second;
	}
	
	public Tuple() {
		this.first = null;
		this.second = null;
	}
	
	public T1 getFirst() {
		return this.first;
	}
	
	public T2 getSecond() {
		return this.second;
	}
	
	public void setFirst(T1 first) {
		this.first = first;
	}
	
	public void setSecond(T2 second) {
		this.second = second;
	}
}
