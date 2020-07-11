public class HelloWorld1 {
	public static void main(String[] args) {
		System.out.println("Hello World!");

		SecretTextFile stf = new SecretTextFile("file 1");
		System.out.println("fetched : " + stf.fetch());
	}
}
