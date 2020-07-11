
public class HelloWorld2 {
	public static void main(String[] args) {
		System.out.println("Hello World!");

		ProxyTextFile ptf = new ProxyTextFile("file 1");
		System.out.println("fetched : " + ptf.fetch());
	}
}
