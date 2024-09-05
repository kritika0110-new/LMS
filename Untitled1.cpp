#include <iostream>
#include <cstring>

using namespace std;

// Define structure for a book
struct Book {
    char name[100];
    char author[100];
    int pages;
    double price;
    int copies; // Added copies field
    int issued; // Added issued field to track issued copies
    Book* next;
};

// Define structure for user details
struct UserDetails {
    char name[100];
    char email[100];
    char phone[15];
};

// Function to create a new book
Book* createBook(const char name[], const char author[], int pages, double price, int copies) {
    Book* newBook = new Book;
    strcpy(newBook->name, name);
    strcpy(newBook->author, author);
    newBook->pages = pages;
    newBook->price = price;
    newBook->copies = copies; // Initialize copies
    newBook->issued = 0; // Initialize issued copies
    newBook->next = nullptr;
    return newBook;
}

// Function to insert a new book at the end of the list
void insertBook(Book*& head, const char name[], const char author[], int pages, double price, int copies) {
    Book* newBook = createBook(name, author, pages, price, copies);
    if (!head) {
        head = newBook;
    } else {
        Book* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newBook;
    }
    cout << "Book inserted successfully." << endl;
}

// Function to display all books
void displayBooks(Book* head) {
    if (!head) {
        cout << "No books available in the library." << endl;
        return;
    }
    cout << "All books in the library:" << endl;
    Book* current = head;
    while (current) {
        cout << "Name: " << current->name << endl;
        cout << "Author: " << current->author << endl;
        cout << "Pages: " << current->pages << endl;
        cout << "Price: " << current->price << endl;
        cout << "Copies available: " << current->copies << endl;
        cout << "--------------------------" << endl;
        current = current->next;
    }
}

// Function to add a book to the cart (for students)
void addBookToCart(Book* cart[], Book* book, int& cartSize) {
    cart[cartSize] = book;
    cartSize++;
    cout << "Book added to cart successfully." << endl;
}

// Function to search for a book by author
void searchByAuthor(Book* head, const char author[]) {
    if (!head) {
        cout << "No books available in the library." << endl;
        return;
    }
    cout << "Books by author " << author << ":" << endl;
    Book* current = head;
    bool found = false;
    while (current) {
        if (strcmp(current->author, author) == 0) {
            cout << "Name: " << current->name << endl;
            cout << "Author: " << current->author << endl;
            cout << "Pages: " << current->pages << endl;
            cout << "Price: " << current->price << endl;
            cout << "Copies available: " << current->copies << endl;
            cout << "--------------------------" << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "No books found by author " << author << "." << endl;
    }
}

// Function to issue a book to a student
void issueBook(Book* head, const char bookName[], int& cartSize) {
    Book* current = head;
    while (current) {
        if (strcmp(current->name, bookName) == 0) {
            if (current->copies - current->issued > 0) {
                UserDetails userDetails;
                cout << "Enter your name: ";
                cin.ignore();
                cin.getline(userDetails.name, sizeof(userDetails.name));
                cout << "Enter your email: ";
                cin.getline(userDetails.email, sizeof(userDetails.email));
                cout << "Enter your phone number: ";
                cin.getline(userDetails.phone, sizeof(userDetails.phone));

                current->issued++;
                cartSize++;

                cout << "Book issued successfully." << endl;
                cout << "Issued to: " << userDetails.name << endl;
                cout << "Email: " << userDetails.email << endl;
                cout << "Phone: " << userDetails.phone << endl;
                return;
            } else {
                cout << "Sorry, no copies of this book are currently available." << endl;
                return;
            }
        }
        current = current->next;
    }
    cout << "The book is not available in the library." << endl;
}

// Function to view issued books (for librarian)
void viewIssuedBooks(Book* head) {
    if (!head) {
        cout << "No books available in the library." << endl;
        return;
    }
    cout << "Issued books:" << endl;
    Book* current = head;
    bool found = false;
    while (current) {
        if (current->issued > 0) {
            cout << "Name: " << current->name << endl;
            cout << "Author: " << current->author << endl;
            cout << "Copies issued: " << current->issued << endl;
            cout << "Copies left: " << current->copies - current->issued << endl;
            cout << "--------------------------" << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "No books have been issued yet." << endl;
    }
}

// Function to search for a book by name
Book* searchBookByName(Book* head, const char name[]) {
    Book* current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int main() {
    int userType;
    cout << "Press 1 for Librarian or 0 for Student: ";
    cin >> userType;

    Book* head = nullptr;
    Book* cart[100]; // Maximum 100 books in cart
    int cartSize = 0; // Number of books currently in cart
    int choice, pages, copies;
    double price;
    char name[100], author[100];
    bool isLibrarian = userType == 1;

    while (true) {
        cout << "\nE-Library Management System" << endl;
        cout << "1. ";
        if (isLibrarian) {
            cout << "Add Book" << endl;
        } else {
            cout << "Add Book to Cart" << endl;
        }
        cout << "2. Display Books by Author" << endl;
        if (isLibrarian) {
            cout << "3. View Issued Books" << endl;
        } else {
            cout << "3. Issue Book" << endl;
        }
        cout << "4. Switch Mode (Librarian/Student)" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (isLibrarian) {
                    cout << "Enter Book Name: ";
                    cin.ignore();
                    cin.getline(name, sizeof(name));
                    cout << "Enter Author Name: ";
                    cin.getline(author, sizeof(author));
                    cout << "Enter Pages: ";
                    cin >> pages;
                    cout << "Enter Price: ";
                    cin >> price;
                    cout << "Enter number of copies: ";
                    cin >> copies;
                    insertBook(head, name, author, pages, price, copies);
                } else {
                    cout << "Enter Book Name to add to cart: ";
                    cin >> name;
                    // Search for the book by name and add it to the cart
                    Book* bookToAdd = searchBookByName(head, name);
                    if (bookToAdd != nullptr) {
                        addBookToCart(cart, bookToAdd, cartSize);
                    } else {
                        cout << "Book not found in the library." << endl;
                    }
                }
                break;
            case 2:
                cout << "Enter Author Name: ";
                cin >> author;
                searchByAuthor(head, author);
                break;
            case 3:
                if (isLibrarian) {
                    viewIssuedBooks(head);
                } else {
                    cout << "Enter Book Name to issue: ";
                    cin >> name;
                    issueBook(head, name, cartSize);
                }
                break;
            case 4:
                isLibrarian = !isLibrarian;
                if (isLibrarian) {
                    cout << "Switched to Librarian mode." << endl;
                } else {
                    cout << "Switched to Student mode." << endl;
                }
                break;
            case 5:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }
    return 0;
}
