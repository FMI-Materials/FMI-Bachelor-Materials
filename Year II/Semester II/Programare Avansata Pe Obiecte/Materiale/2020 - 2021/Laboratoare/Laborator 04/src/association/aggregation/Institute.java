package association.aggregation;

import java.util.List;

public class Institute {

    String instituteName;
    private List<Department> departamentList;

    public Institute(String instituteName, List<Department> departamentList) {
        this.instituteName = instituteName;
        this.departamentList = departamentList;
    }

    public int getTotalNumberOfStudentsInInstitute() {
        int numberOfStudents = 0;

        List<Student> students;

        for(Department d : departamentList) {
            students = d.getStudentList();
            numberOfStudents += students.size();
        }

        return numberOfStudents;
    }
}
