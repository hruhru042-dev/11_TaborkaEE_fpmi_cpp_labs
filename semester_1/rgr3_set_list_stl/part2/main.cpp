#include <iostream>
#include <list>
#include <string>
#include <algorithm>
struct Author {
    std::string surname;
    std::string name;
    std::string patronymic;
    bool operator<(const Author& other) const {
        return surname < other.surname;
    }
};
struct Book {
    int udc;
    std::string title;
    int year;
    std::list<Author> authors;
    bool operator<(const Book& other) const {
        return title < other.title;
    }
};
class Library {
private:
    std::list<Book> books;
public:
    void addBook(const Book& b) {
        books.push_back(b);
        books.sort();
    }
    void deleteBook(const std::string& title) {
        books.remove_if([&](const Book& b) { return b.title == title; });
    }
    void searchByTitle(const std::string& title) const {
        std::list<Book>::const_iterator it = std::find_if(books.begin(), books.end(),
            [&](const Book& b) { return b.title == title; });
        if (it != books.end()) {
            std::cout << "Book found: " << it->title << " (" << it->year << ")\n";
        }
        else {
            std::cout << "Book not found\n";
        }
    }
    void searchByAuthor(const std::string& surname) const {
        for (std::list<Book>::const_iterator b = books.begin(); b != books.end(); ++b) {
            std::list<Author>::const_iterator it = std::find_if(b->authors.begin(), b->authors.end(),
                [&](const Author& a) { return a.surname == surname; });
            if (it != b->authors.end()) {
                std::cout << "Author " << surname << " is in book: " << b->title << "\n";
            }
        }
    }
    void addAuthor(const std::string& title, const Author& a) {
        std::list<Book>::iterator it = std::find_if(books.begin(), books.end(),
            [&](const Book& b) { return b.title == title; });
        if (it != books.end()) {
            it->authors.push_back(a);
            it->authors.sort();
        }
    }
    void deleteAuthor(const std::string& title, const std::string& surname) {
        std::list<Book>::iterator it = std::find_if(books.begin(), books.end(),
            [&](const Book& b) { return b.title == title; });
        if (it != books.end()) {
            it->authors.remove_if([&](const Author& a) { return a.surname == surname; });
        }
    }
    void print() const {
        for (std::list<Book>::const_iterator b = books.begin(); b != books.end(); ++b) {
            std::cout << b->title << " (" << b->year << "), UDC: " << b->udc << "\n";
            for (std::list<Author>::const_iterator a = b->authors.begin(); a != b->authors.end(); ++a) {
                std::cout << "   " << a->surname << " " << a->name << " " << a->patronymic << "\n";
            }
        }
    }
};
int main() {
    Library lib;
    Book b1{ 123, "Algorithms", 2020 };
    b1.authors.push_back({ "Ivanov", "Ivan", "Ivanovich" });
    b1.authors.push_back({ "Petrov", "Petr", "Petrovich" });
    b1.authors.sort();
    Book b2{ 456, "Data Structures", 2019 };
    b2.authors.push_back({ "Sidorov", "Sidor", "Sidorovich" });
    b2.authors.sort();
    lib.addBook(b1);
    lib.addBook(b2);
    lib.print();
    lib.searchByTitle("Algorithms");
    lib.searchByAuthor("Petrov");
    lib.addAuthor("Data Structures", { "Kozlov", "Abaka", "Evgenievich" });
    lib.deleteAuthor("Algorithms", "Ivanov");
    std::cout << "\nAfter changes:\n";
    lib.print();
    return 0;
}

