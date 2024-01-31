package association.aggregation;

import java.util.List;

public class Department {

    String name;
    private List<Student> studentList;

    public Department(String name, List<Student> students) {
        this.name = name;
        this.studentList = students;
    }

    public List<Student> getStudentList() {
        return this.studentList;
    }
}
