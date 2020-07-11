
enum GRADE {
	Staff, Manager, VicePresident
}

interface Employee {
	String getName();
	GRADE getGrade();
	String getInformation(Employee viewer);
}

class NormalEmployee implements Employee {
	private String name;
	private GRADE grade;

	public NormalEmployee(String name, GRADE grade) {
		this.name = name;
		this.grade = grade;
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public GRADE getGrade() {
		return grade;
	}

	@Override
	public String getInformation(Employee viewer) {
		return "Display " + getGrade().name() + " '" + getName() + "' personnel information.";
	}
}
