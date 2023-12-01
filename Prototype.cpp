// Can add minimum attempts for login
#include <iostream>
#include <fstream> // For File Handling
#include <string>
#include <chrono> // For Delays in Terminal
#include <thread> // For Delays in Terminal
#include <ctime>
using namespace std;

//! Define ANSI escape codes for colours
#define YELLOW_TEXT "\033[33m"
#define RESET_TEXT "\033[0m"

//! Structure Definitions
struct user_info
{
    string ID;
    string PASSWORD;
    struct user_info *next;
};
typedef user_info user_info_node;
struct book
{
    string name;
    string id;
    time_t renewal_date; // New field to store the renewal date
    struct book *next;
};
typedef struct book book_details;

//! Head Nodes 
user_info_node *teachers = NULL;
user_info_node *students = NULL;
book_details *books = NULL;

//! Files
const string TEACHERS_FILE = "/Users/manjilnepal/Library/Mobile Documents/com~apple~CloudDocs/Documents/My Codes/DSA II/DSA Project/teachers.txt";
const string BOOKS_FILE = "/Users/manjilnepal/Library/Mobile Documents/com~apple~CloudDocs/Documents/My Codes/DSA II/DSA Project/books.txt";
const string STUDENTS_FILE = "/Users/manjilnepal/Library/Mobile Documents/com~apple~CloudDocs/Documents/My Codes/DSA II/DSA Project/students.txt";


// Function to get the current date
time_t get_current_date()
{
    return chrono::system_clock::to_time_t(chrono::system_clock::now());
}
// Function to add days to a given date
time_t add_days(time_t date, int days)
{
    return date + days * 24 * 60 * 60; // Convert days to seconds
}

//! Functions Block
void add_new_user(user_info_node *&head, string ID, string PASSWORD)
{
    user_info_node *temp = new user_info_node;
    temp->ID = ID;
    temp->PASSWORD = PASSWORD;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        return;
    }
    user_info_node *ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
}
void saveTeachersToFile(user_info_node *head)
{
    ofstream outFile(TEACHERS_FILE);
    if (outFile.is_open())
    {
        user_info_node *ptr = head;
        while (ptr != NULL)
        {
            outFile << ptr->ID << " " << ptr->PASSWORD << endl;
            ptr = ptr->next;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing: " << TEACHERS_FILE << endl;
    }
}
void saveStudentsToFile(user_info_node *head)
{
    ofstream outFile(STUDENTS_FILE);
    if (outFile.is_open())
    {
        user_info_node *ptr = head;
        while (ptr != NULL)
        {
            outFile << ptr->ID << " " << ptr->PASSWORD << endl;
            ptr = ptr->next;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing: " << STUDENTS_FILE << endl;
    }
}
void loadTeachersFromFile(user_info_node *&head)
{
    ifstream inFile(TEACHERS_FILE);
    if (inFile.is_open())
    {
        string ID, PASSWORD;
        while (inFile >> ID >> PASSWORD)
        {
            add_new_user(head, ID, PASSWORD);
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading: " << TEACHERS_FILE << endl;
    }
}
void loadStudentsFromFile(user_info_node *&head)
{
    ifstream inFile(STUDENTS_FILE);
    if (inFile.is_open())
    {
        string ID, PASSWORD;
        while (inFile >> ID >> PASSWORD)
        {
            add_new_user(head, ID, PASSWORD);
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading: " << STUDENTS_FILE << endl;
    }
}
void add_new_book(book_details *&head, string name, string id)
{
    book_details *temp = new book_details;
    temp->name = name;
    temp->id = id;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
        return;
    }
    book_details *ptr = head;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
}
void saveBooksToFile(book_details *head)
{
    ofstream outFile(BOOKS_FILE);
    if (outFile.is_open())
    {
        book_details *ptr = head;
        while (ptr != NULL)
        {
            outFile << ptr->name << " " << ptr->id << endl;
            ptr = ptr->next;
        }
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing: " << BOOKS_FILE << endl;
    }
}
void loadBooksFromFile(book_details *&head)
{
    ifstream inFile(BOOKS_FILE);
    if (inFile.is_open())
    {
        string name, id;
        while (inFile >> name >> id)
        {
            add_new_book(head, name, id);
        }
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading: " << BOOKS_FILE << endl;
    }
}
void update_book(book_details *&head, string id)
{
    if (head == NULL)
    {
        cout << "No Books Available to Update\n";
        return;
    }
    book_details *ptr = head;
    string a, b;
    while (ptr != NULL)
    {
        if (ptr->id == id)
        {
            cout << "Enter the new ID: ";
            cin >> a;
            cout << "Enter the new Name: ";
            cin >> b;
            ptr->id = a;
            ptr->name = b;
            cout << "Book Updated Successfully\n";
            return;
        }
        ptr = ptr->next;
    }
    cout << "No Books found with the given ID\n";
}
void delete_book(book_details *&head, const string& name, const string& id)
{
    if (head == NULL)
    {
        cout << "\n\t\t\t\t\tNo Book Available to Delete\n";
        return;
    }

    // Check if the first node matches both name and ID
    if (head->name == name && head->id == id)
    {
        book_details *temp = head;
        head = head->next;
        delete temp;
        cout << "\n\t\t\t\t\tBook Deleted Successfully!\n";
        return;
    }

    book_details *ptr = head;
    while (ptr->next != NULL && (ptr->next->name != name || ptr->next->id != id))
    {
        ptr = ptr->next;
    }

    if (ptr->next == NULL)
    {
        cout << "\n\t\t\t\t\tNo Book found with the given name and ID\n";
    }
    else
    {
        book_details *temp = ptr->next;
        ptr->next = temp->next;
        delete temp;
        cout << "\n\t\t\t\t\tBook Deleted Successfully!\n";
    }
}
void print_all_books(book_details *head)
{
    if (head == NULL)
        cout << YELLOW_TEXT << "\n\t\t\t\t\tNo Books to Show\n" << RESET_TEXT;
    else
    {
        book_details *ptr = head;
        cout << YELLOW_TEXT << "\n\t\t\t\t---------- Books Available in the Library ----------\n" << RESET_TEXT;
        while (ptr != NULL)
        {
            cout << YELLOW_TEXT << "\n\t\t\t\t\tBook Name: " << ptr->name << endl;
            cout << "\t\t\t\t\tID: " << ptr->id << RESET_TEXT << endl;
            ptr = ptr->next;
        }
        cout << YELLOW_TEXT << "\n\t\t\t\t---------- ****************************** ----------\n" << RESET_TEXT;
    }
    cout << endl;
}
bool is_matching(user_info_node *teachers, user_info_node *students, string ID, string PASSWORD)
{
    user_info_node *ptr = teachers;
    while (ptr != NULL)
    {
        if (ptr->ID == ID && ptr->PASSWORD == PASSWORD)
            return true;
        ptr = ptr->next;
    }

    ptr = students;
    while (ptr != NULL)
    {
        if (ptr->ID == ID && ptr->PASSWORD == PASSWORD)
            return true;
        ptr = ptr->next;
    }

    return false;
}
void search(book_details *head, const string &name, const string &id)
{
    if (head == NULL)
    {
        cout << "\n\t\t\t\tNo Books Available to Search\n";
        return;
    }

    bool found = false;
    book_details *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->name == name && ptr->id == id)
        {
            cout << "\n\t\t\t\tBook is Available!!\n";
            cout << "\n\t\t\t\tBook Name: " << ptr->name << endl;
            cout << "\t\t\t\tID: " << ptr->id << endl;
            found = true;
            break;
        }
        ptr = ptr->next;
    }

    if (!found)
    {
        cout << "\n\t\t\t\tNo Book found with the given name and ID\n";
    }
}
void renew_book(book_details *&head, string id)
{
    if (head == NULL)
    {
        cout << "No Books Available to Renew\n";
        return;
    }
    book_details *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->id == id)
        {
            // Renew the book for 14 days from today
            ptr->renewal_date = add_days(get_current_date(), 14);
            cout << "\n\t\t\t\tBook Renewed Successfully. Next renewal date: " << ctime(&ptr->renewal_date);
            return;
        }
        ptr = ptr->next;
    }
    cout << "\n\t\t\t\tNo Books found with the given ID\n";
}


int main()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    std::cout << "\033[32m\n\t\t\t\t*********************************************************";
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    std::cout << "\n\t\t\t\t*                                                       *";
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    std::cout << "\n\t\t\t\t*      Welcome to the Smart Digital Library System      *";
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    std::cout << "\n\t\t\t\t*                                                       *";
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    std::cout << "\n\t\t\t\t*                                                       *";
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    std::cout << "\n\t\t\t\t*********************************************************\033[0m";

    loadTeachersFromFile(teachers);
    loadStudentsFromFile(teachers);
    loadBooksFromFile(books);

    while (1)
    {
        char ch;
        cout << "\n\n";
        cout << "\033[34m\t\t\t\t*********************************************************\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "\t\t\t\t*                                                       *\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "\t\t\t\t*          Are you a Teacher or a Student? (T/S)        *\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "\t\t\t\t*                                                       *\n";
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "\t\t\t\t*********************************************************\033[0m\n";
        cout << "\n\t\t\t\t\t-> ";
        cin >> ch;

        if (ch == 'T') // For Teachers
        {
            char X;
            cout << "\n\n";
            cout << "\t\t\t\t\t******************************************\n";
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "\t\t\t\t\t* 1. Create a New Account                *\n";
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "\t\t\t\t\t* 2. Login                               *\n";
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "\t\t\t\t\t******************************************\n";
            cout << "\n\t\t\t\t\t-> ";
            cin >> X;
            string ID, PASSWORD;
            if (X == '1')
            {
                cout << "\n\t\t\t\t\tEnter your ID(CSXXXXX): ";
                cin >> ID;
                while(ID.length()!=7)
                {
                    cout << "\n\t\t\t\t\tInvalid ID! Please Try Again.\n";
                    cout << "\n\t\t\t\t\tEnter your ID(CSXXXXX): ";
                    cin >> ID;
                }
                cout << "\t\t\t\t\tCreate a Password: ";
                cin >> PASSWORD;
                add_new_user(teachers, ID, PASSWORD);
                saveTeachersToFile(teachers);
                cout << "\n\t\t\t\t\tCongratulations!!! Account Successfully Created\n";
            }
            else if (X == '2')
            {
                cout << "\n\t\t\t\t\tEnter your ID(CSXXXXX): ";
                cin >> ID;
                cout << "\t\t\t\t\tEnter your PASSWORD: ";
                cin >> PASSWORD;
                while (1)
                {
                    if(is_matching(teachers, students, ID, PASSWORD))
                    {
                        int choice;
                        string name, id;
                        cout << "\n";
                        cout << "\t\t\t\t*********************************************************\n";
                        cout << "\t\t\t\t*                                                       *\n";
                        cout << "\t\t\t\t*              Smart Digital Library System             *\n";
                        cout << "\t\t\t\t*                                                       *\n";
                        cout << "\t\t\t\t*********************************************************\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t*                                                       *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 1. Add New Book                                       *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 2. Update Any Book                                    *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 3. Delete Book                                        *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 4. List of All Books                                  *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 5. Exit                                               *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t*                                                       *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t*********************************************************\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\n\t\t\t\t\tEnter your choice: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\n\t\t\t\t\tEnter the name of Book: ";
                            cin >> name;
                            cout << "\t\t\t\t\tEnter the ID of Book: ";
                            cin >> id;
                            add_new_book(books, name, id);
                            saveBooksToFile(books);
                            break;

                        case 2:
                            cout << "\n\t\t\t\t\tEnter the ID of book you want to update: ";
                            cin >> id;
                            update_book(books, id);
                            saveBooksToFile(books);
                            break;
                        case 3:
                            cout << "\n\t\t\t\t\tEnter the Name of book you want to delete: ";
                            cin >> name;
                            cout << "\n\t\t\t\t\tEnter the ID of book you want to delete: ";
                            cin >> id;
                            delete_book(books, name, id);
                            saveBooksToFile(books);
                            break;
                        case 4:
                            print_all_books(books);
                            break;
                        case 5:
                            exit(1);
                        }
                    }
                    else
                    {
                        cout << "Wrong Details! Please enter again!" << endl;
                        break;
                    }
                }
            }
            else
            {
                cout << "Try Again!!!" << endl;
            }
        }
        else if (ch == 'S') // For Students
        {
            char X;
            cout << "\n\n";
            cout << "\t\t\t\t\t******************************************\n";
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "\t\t\t\t\t* 1. Create a New Account                *\n";
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "\t\t\t\t\t* 2. Login                               *\n";
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "\t\t\t\t\t******************************************\n";
            cout << "\n\t\t\t\t\t-> ";
            cin >> X;
            string ID, PASSWORD;
            if (X == '1')
            {
                cout << "\n\t\t\t\t\tEnter your ID(APXXXXXXXXXXX): ";
                cin >> ID;
                while(ID.length()!=13)
                {
                    cout << "\n\t\t\t\t\tInvalid ID! Please Try Again.\n";
                    cout << "\n\t\t\t\t\tEnter your ID(APXXXXXXXXXXX): ";
                    cin >> ID;
                }
                cout << "\t\t\t\t\tCreate a Password: ";
                cin >> PASSWORD;
                add_new_user(teachers, ID, PASSWORD);
                saveTeachersToFile(teachers);
                cout << "\n\t\t\t\t\tCongratulations!!! Account Successfully Created\n";
            }
            else if (X == '2')
            {
                cout << "\n\t\t\t\t\tEnter your ID(APXXXXXXXXXXX): ";
                cin >> ID;
                cout << "\t\t\t\t\tEnter your PASSWORD: ";
                cin >> PASSWORD;
                while (1)
                {
                    if(is_matching(teachers, students, ID, PASSWORD))
                    {
                        int choice;
                        string name, id;
                        cout << "\n";
                        cout << "\t\t\t\t*********************************************************\n";
                        cout << "\t\t\t\t*                                                       *\n";
                        cout << "\t\t\t\t*              Smart Digital Library System             *\n";
                        cout << "\t\t\t\t*                                                       *\n";
                        cout << "\t\t\t\t*********************************************************\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t*                                                       *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 1. Search for Book                                    *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 2. Renew Book                                         *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 3. List of All Books                                  *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t* 4. Exit                                               *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t*                                                       *\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\t\t\t\t*********************************************************\n";
                        this_thread::sleep_for(chrono::milliseconds(100));
                        cout << "\n\t\t\t\t\tEnter your choice: ";
                        cin >> choice;
                        switch (choice)
                        {
                        case 1:
                            cout << "\n\t\t\t\t\tEnter the name of Book: ";
                            cin >> name;
                            cout << "\t\t\t\t\tEnter the ID of Book: ";
                            cin >> id;
                            search(books, name, id);
                            break;

                        case 2:
                            cout << "\n\t\t\t\t\tEnter the ID of book you want to renew: ";
                            cin >> id;
                            renew_book(books, id);
                            break;

                        case 3:
                           print_all_books(books);
                            break;
                        case 4:

                            exit(1);
                        }
                    }
                    else
                    {
                        cout << "\n\t\t\t\t\tWrong Details! Please enter again!" << endl;
                        break;
                    }
                }
            }
            else
            {
                cout << "\n\t\t\t\t\tTry Again!!!" << endl;
            }
        }
        else
        {
            cout << "\n\t\t\t\tError!!!! Type Again!\n";
        }
    }
    return 0;
}
