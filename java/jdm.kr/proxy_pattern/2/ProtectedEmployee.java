class ProtectedEmployee implements Employee {
	private Employee employee;

	public ProtectedEmployee(Employee employee) {
		this.employee = employee;
	}

	@Override
	public String getInformation(Employee viewer) {
		if (this.employee.getGrade() == viewer.getGrade() && this.employee.getName().equals(viewer.getName())) {
			return this.employee.getInformation(viewer);
		}

		switch (viewer.getGrade()) {
			case VicePresident:
				if (this.employee.getGrade() == GRADE.Manager || this.employee.getGrade() == GRADE.Staff) {
					return this.employee.getInformation(viewer);
				}
			case Manager:
				if (this.employee.getGrade() == GRADE.Staff) {
					return this.employee.getInformation(viewer);
				}
			case Staff:
			default:
				throw new NotAuthorizedException();
		}
	}

	@Override
	public String getName() {
		return employee.getName();
	}

	@Override
	public GRADE getGrade() {
		return employee.getGrade();
	}
}

class NotAuthorizedException extends RuntimeException {
	private static final long serialVersionUID = -1714144282967712658L;
}

