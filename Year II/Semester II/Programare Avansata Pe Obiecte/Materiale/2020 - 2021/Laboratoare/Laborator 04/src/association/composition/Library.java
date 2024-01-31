package association.composition;

import java.util.List;

public class Library {

    private final List<Book> books;

    Library(List<Book> books) {
        this.books = books;
    }

    public int getTotalNumberOfBooks() {
        return books.size();
    }
}
