#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class Book{
private:
    int isbn;
    string title;
    string author;
public:
    Book(){}    //def constr
    Book(const string&, const string&, int = 0);    //constr declared, body is outside

//getters: const is MUST
    int getISBN() const {return isbn;};
    string getTitle() const {return title;};
    string getAuthor() const {return author;};
//setters:
    void setISBN(int in_isbn){isbn = in_isbn;};
    void setTitile(string& in_title){title = in_title;};
    void setAuthor(string& in_author){author = in_author;};

    void print() const; //declaration of function, body is outside
};
//constructor body aka definition
Book::Book(const string& in_title, const string& in_author, int in_isbn){
    title = in_title;
    author = in_author;
    isbn = in_isbn;
}
void Book::print() const{
    cout<<"Book information"<<endl
    <<"\t Book ISBN: "<<isbn<<endl
    <<"\t Book Title: "<<title<<endl
    <<"\t Book Author: "<<author<<endl;
}




class Bookcase{
private:    //can be omitted
    Book* b_ptr;
    const int maxCap;
    int curCap;
    bool full;
public:
    Bookcase(int = 100);
    Bookcase(int, const Book*, int);
    Bookcase(const Bookcase&);  //copy constructor

    bool addBook(Book&);
    void findBook(int) const;
    void printAll() const;
    ~Bookcase();    //destructor
};
Bookcase::Bookcase(int m_capacity) : maxCap(m_capacity){    //: maxCap(m_capacity) is member initialization list, better
    curCap = 0;
    full = false;
    b_ptr = new Book[m_capacity];
}
Bookcase::Bookcase(int m_capacity, const Book* in_ptr, int in_arraySize) : maxCap(m_capacity){
    curCap = in_arraySize;
    full = false;
    b_ptr = new Book[m_capacity];
    for(int i = 0; i<curCap; i++){
        b_ptr[i] = in_ptr[i];
    }
}
Bookcase::~Bookcase(){
    delete[] b_ptr;
}
Bookcase::Bookcase(const Bookcase& in_b) :maxCap(in_b.maxCap){  //copy constructor for bookcase
    curCap = in_b.curCap;
    full = in_b.full;
    b_ptr = new Book[in_b.maxCap];
    for(int i = 0; i<curCap; i++){
        b_ptr[i] = in_b.b_ptr[i];
    }
}

bool Bookcase::addBook(Book& in_b){
    if(full){return false;};
    b_ptr[curCap] = in_b;
    curCap++;
    if(curCap == maxCap){
        full = true;
    }
    return true;
}
void Bookcase::findBook(int in_isbn) const{
    for(int i = 0; i<curCap; i++){
        if(b_ptr[i].getISBN()==in_isbn){
            b_ptr[i].print();
            return;
        }
    }
    cout<<"Book cant be found"<<endl;
}

void Bookcase::printAll() const{
    cout<<"------------------------------"<<endl;
    cout<<"Printing Bookcase..."<<endl;
    for(int i = 0; i<curCap;i++){
        b_ptr[i].print();
    }
    cout<<"------------------------------"<<endl;

}
int main(){
    Book b1("Artificial Intelligence, A Modern Approach", "Stuart Russell", 131038052);
    Book b2("Modern Operating Systems", "Andrew S. Tanenbaum", 136006639);
    Book b3("Introduction to Algorithms", "Thomas Cormen");

    Book* bookArray = new Book[3];      //array of type Book
    bookArray[0] = b1;
    bookArray[1] = b2;
    bookArray[2] = b3;

    Bookcase bc1(20, bookArray, 3);
    bc1.printAll();

    Book b4(b3);    //copy constructor is called
    b4.print();

    delete[] bookArray;

    if(bc1.addBook(b4)){        //add one more copy of b3
        cout << "The given book has been added.." << endl;
    } else {
        cout << "The capacity limit is reached.." << endl;
    }

    Bookcase bc2(bc1);      //copy constructor
    bc2.printAll();
    bc1.findBook(131038052);
    bc1.findBook(23);



    return 0;
}