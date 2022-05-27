#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//---BOOK---
struct book
{
    int id;
    string name;
    int quntity;
    int totalBorrowed;
    book()
    {
        id = -1;
        name = "";
        quntity = totalBorrowed = 0;
    }

    void read()
    {
        cout << "Enter Book ID, Name, Quntity: ";
        cin >> id >> name >> quntity;
    }
    bool borrowCopy()
    {
        if (quntity - totalBorrowed == 0)
            return false;
        ++totalBorrowed;
        return true;
    }
    bool returnCopy()
    {
        if (totalBorrowed == 0)
            return false;
        --totalBorrowed;
        return true;
    }
    bool hasPrefix(string prefix)
    {
        if (prefix.size() > name.size())
            return false;

        for (int i = 0; i < (int)prefix.size(); i++)
        {
            if (name[i] != prefix[i])
                return false;
        }
        return true;
    }
    void print()
    {
        cout << "Book id:" << id << " | name:" << name << " | quntity:" << quntity
             << " | totalBorrowed:" << totalBorrowed << endl;
    }
};
bool cmpById(book a, book b)
{
    return a.id < b.id;
}
bool cmpByName(book a, book b)
{
    return a.name < b.name;
}

//---USER---
struct user
{
    string name;
    int id;
    set<int> borrowedBooksIds;
    user()
    {
        name = "";
        id = -1;
    }

    void read()
    {
        cout << "Enter User Name, ID: ";
        cin >> name >> id;
    }
    void borrowBook(int bookId)
    {
        borrowedBooksIds.insert(bookId);
    }
    void returnBook(int bookId)
    {
        // dr mostafa use find() function instead
        if (borrowedBooksIds.count(bookId))
            borrowedBooksIds.erase(bookId);
        else
            cout << "This User Never Borrow This Book\n";
    }
    bool isBorrowed(int bookId)
    {
        // dr mostafa use find() function instead
        if (!borrowedBooksIds.count(bookId))
            return false;
        return true;
    }
    void print()
    {
        cout << "User Name: " << name << " | Id: " << id << " | BorrowedBooks: ";
        for (int book : borrowedBooksIds)
        {
            cout << book << " ";
        }
        cout << endl;
    }
};

struct librarySystem
{
    vector<book> books;
    vector<user> users;

    // Driving Functions
    bool run()
    {
        while (true)
        {
            int choice = menu();

            switch (choice)
            {
            case 1:
                addBook();
                break;
            case 2:
                searchBooksByPrefix();
                break;
            case 3:
                printWhoBorrowedBook();
                break;
            case 4:
                printBooksById();
                break;
            case 5:
                printBooksByName();
                break;
            case 6:
                addUser();
                break;
            case 7:
                userBorrowBook();
                break;
            case 8:
                userReturnBook();
                break;
            case 9:
                printUsers();
                break;
            default:
                return 0;
                break;
            }
        }
    }
    int menu()
    {
        int choice;
        while (true)
        {
            cout << "\nMenu:";
            cout << "\n---MANAGE BOOKS---\n";
            cout << "1) add book\n";
            cout << "2) search book by prefix\n";
            cout << "3) print who borrowed book by name\n";
            cout << "4) print Books Sorted by id\n";
            cout << "5) print Books Sorted by name\n";
            cout << "\n---MANAGE USERS---\n";
            cout << "6) add user\n";
            cout << "7) user borrow book\n";
            cout << "8) user return book\n";
            cout << "9) print users\n";
            cout << "10) exit\n";
            cout << "\nEnter choice [1:10]: ";
            cin >> choice;
            cout << "\n\n";

            if (choice >= 1 && choice <= 10)
                return choice;
            else
                cout << "Invalid input, try again.\n";
        }
    }

    // helpful Functions
    int getUserIdxByName(string name)
    {
        for (int i = 0; i < (int)users.size(); i++)
        {
            if (users[i].name == name)
                return i;
        }
        return -1;
    }
    int getBookIdxByName(string name)
    {
        for (int i = 0; i < (int)books.size(); i++)
        {
            if (books[i].name == name)
                return i;
        }
        return -1;
    }
    bool readUserAndBookName(int &userIdx, int &bookIdx, int trails = 3)
    {
        string userName, bookName;

        while (trails--)
        {
            cout << "Enter UserName and BookName: \n";
            cin >> userName >> bookName;
            // check if userName and bookName are valid
            userIdx = getUserIdxByName(userName);
            if (userIdx == -1)
            {
                cout << "Invalid UserName, Try again..\n";
                continue;
            }
            bookIdx = getBookIdxByName(bookName);
            if (bookIdx == -1)
            {
                cout << "Invalid BookName, Try again..\n";
                continue;
            }

            return true;
        }
        cout << "You did several trials! Try later.";
        return false;
    }

    // book Functions
    void addBook()
    {
        book newBook;
        newBook.read();
        books.push_back(newBook);
    }
    void searchBooksByPrefix()
    {
        string prefix;
        bool exist = false;
        cout << "Enter Book name prefix: ";
        cin >> prefix;

        for (book b : books)
        {
            if (b.hasPrefix(prefix))
            {
                cout << b.name << "\n";
                exist = true;
            }
        }

        if (!exist)
            cout << "There is No books with this prefix\n";
    }
    void printWhoBorrowedBook()
    {
        string bookName;
        cout << "Enter BookName: ";
        cin >> bookName;

        int bookIdx = getBookIdxByName(bookName);
        // check if bookName is valid and there are borrowed copies of this book
        if (bookIdx == -1)
        {
            cout << "Invalid BookName\n";
            return;
        }
        if (books[bookIdx].totalBorrowed == 0)
        {
            cout << "There are No borrowed Copies from this Book\n";
        }
        // print names of users who borrowed this book by bookId
        int bookId = books[bookIdx].id;
        for (user u : users)
        {
            if (u.isBorrowed(bookId))
            {
                cout << u.name << "\n";
            }
        }
    }
    void printBooksById()
    {
        sort(books.begin(), books.end(), cmpById);
        for (book b : books)
        {
            b.print();
        }
    }
    void printBooksByName()
    {
        sort(books.begin(), books.end(), cmpByName);
        for (book b : books)
        {
            b.print();
        }
    }
    // user Functions
    void addUser()
    {
        user newUser;
        newUser.read();
        users.push_back(newUser);
    }
    void userBorrowBook()
    {
        int userIdx, bookIdx;
        // if user enter valid userName and bookName exit
        if (!readUserAndBookName(userIdx, bookIdx))
            return;

        // get bookId to add it in User Borrowed Books
        int bookId = books[bookIdx].id;

        if (!books[bookIdx].borrowCopy())
            cout << "No more copies available right now\n";
        else
            users[userIdx].borrowBook(bookId);
    }
    void userReturnBook()
    {
        int userIdx, bookIdx;
        if (!readUserAndBookName(userIdx, bookIdx))
            return;

        int bookId = books[bookIdx].id;

        if (!books[bookIdx].returnCopy())
            cout << "There are No borrowed Copies from this Book\n";
        else
            users[userIdx].returnBook(bookId);
    }
    void printUsers()
    {
        for (user u : users)
        {
            u.print();
        }
    }
};

int main()
{
    librarySystem library;
    library.run();
}
