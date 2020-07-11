class ProxyTextFile implements TextFile {
	private String fileName;
	private TextFile textFile;

	public ProxyTextFile(String fileName) {
		this.fileName = fileName;
	}

	@Override
	public String fetch() {
		if (textFile == null) {
			textFile = new SecretTextFile(fileName);
		}
		return "[proxy] " + textFile.fetch();
	}
}
