package association.composition;

import java.util.ArrayList;
import java.util.List;

/*
        Composition:
                    -Tipul de relatie dintre clase has-a (part-of)
                    -Strong association
                    -Clasele copil nu pot exista independente de cea parinte
 */
public class TestForLibrary {

    public static void main(String[] args) {
        Book b1 = new Book("A", "Ion Ion");
        Book b2 = new Book("B", "Ion Gica");
        Book b3 = new Book("C", "Gica Popescu");

        List<Book> bookList = new ArrayList<>();
        bookList.add(b1);
        bookList.add(b2);
        bookList.add(b3);

        Library library = new Library(bookList);

        System.out.println(library.getTotalNumberOfBooks());
    }
}
