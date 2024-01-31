package association.aggregation;

import java.util.ArrayList;
import java.util.List;

/*
        Aggregation: -weak association
                     - has
                     -clasele copil pot exista independente
 */
public class TestForAggregation {

    public static void main(String args[]) {

        Student s1 = new Student("Ion", 1);
        Student s2 = new Student("Maria", 2);
        Student s3 = new Student("Gigi", 3);
        Student s4 = new Student("George", 4);

        List<Student> studentListForFirstDepartment = new ArrayList<>();
        studentListForFirstDepartment.add(s1);
        studentListForFirstDepartment.add(s2);

        List<Student> studentListForSecondDepartment = new ArrayList<>();
        studentListForSecondDepartment.add(s3);
        studentListForSecondDepartment.add(s4);

        Department firstDepartment = new Department("Mate-Info", studentListForFirstDepartment);
        Department secondDepartment = new Department("Filozofie", studentListForSecondDepartment);

        List<Department> departmentList = new ArrayList<>();
        departmentList.add(firstDepartment);
        departmentList.add(secondDepartment);

        Institute institute = new Institute("Universitatea Bucuresti", departmentList);

        System.out.println("the number of the students in the insitute is ");
        System.out.println(institute.getTotalNumberOfStudentsInInstitute());
    }
}
