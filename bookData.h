//
// Created by amccm on 9/2/2021.
//

#ifndef PROJECT_1_BOOKDATA_H
#define PROJECT_1_BOOKDATA_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using std::ifstream;
using std::ostream;
using std::setw;
using std::string;
using std::vector;

/**
 * Class representing entries into the Goodreads dataset.
 *
 * Fields (field for each column in in the Goodreads dataset):
 *      bookID: Identification number for each book
 *      title: Tbe books name
 *      author: Names of the people who wrote the book.  Multiple authors displayed with '-'
 *      averageRating: Average rating the book received when all ratings are combined
 *      isbn: Another unique number to ID a book
 *      isbn13: A 13 digit isbn to identify a book instead of a standard isbn
 */
class bookData {

private:
    string title, author, averageRating, isbn, isbn13;
    int  bookID;

public:
    // Constructors
    bookData(){bookID = 0;
        title = "";
        author = "";
        averageRating = "";
        isbn = "";
        isbn13 = "";}

    bookData(int bookID,
             string title,
             string author,
             string averageRating,
             string isbn,
             string isbn13){
        this->bookID = bookID;
        this->title = title;
        this->author = author;
        this->averageRating = averageRating;
        this->isbn=isbn;
        this->isbn13=isbn13;
    }

    // Getters and Setters
    string getAverageRating() const {
        return averageRating;
    }

    void setAverageRating(string averageRating) {
        this->averageRating = averageRating;
    }

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &title) {
        this->title = title;
    }

    const string &getAuthor() const {
        return author;
    }

    void setAuthor(const string &author) {
        this->author = author;
    }



    const string &getIsbn() const {
        return isbn;
    }

    void setIsbn(const string &isbn) {
        this->isbn = isbn;
    }

    const string &getIsbn13() const {
        return isbn13;
    }

    void setIsbn13(const string &isbn13) {
        this->isbn13 = isbn13;
    }

    int getBookId() const {
        return bookID;
    }

    void setBookId(int bookId) {
        bookID = bookId;
    }

    bool getBookTitleComparable(bookData leftBookTitle, bookData rightBookTitle){
        if (leftBookTitle > rightBookTitle)
        {
            return leftBookTitle.getTitle() < rightBookTitle.getTitle();
        }

        if(leftBookTitle < rightBookTitle)
        {
            return leftBookTitle.getTitle() < rightBookTitle.getTitle();
        }

        if(leftBookTitle <= rightBookTitle)
        {
            return leftBookTitle.getTitle() <= rightBookTitle.getTitle();
        }
        if(leftBookTitle >= rightBookTitle)
        {
            return leftBookTitle.getTitle() >= rightBookTitle.getTitle();
        }
        if(leftBookTitle == rightBookTitle)
        {
            return true;
        }
        return false;

    }
    /*
     * Overloaded Operators
     * friend declaration allows me to access private fields from classes
     * ostream is the output stream, '&' used to make it a reference to output stream
     * Takes all the data from bookData and assigns it to the output operator
     */
    friend ostream& operator << (ostream& outs, bookData bkObj){
        outs << left  << setw(6) << bkObj.getBookId()
             << setw(130) << bkObj.getTitle()
             << setw(130) << bkObj.getAuthor()
             << setw(40) << bkObj.getAverageRating()
             << setw(25) << bkObj.getIsbn()
             << setw(25) << bkObj.getIsbn13();
        return outs;
    }

    // Overload operators for <, >, <=, >= and ==.
    friend bool operator>=(bookData greaterEqual, bookData lessEqual){
        return greaterEqual.getBookId() >= lessEqual.getBookId();

    }
    friend bool operator <=(bookData lessEqual, bookData greaterEqual){
        return lessEqual.getBookId() <= greaterEqual.getBookId();
    }
    friend bool operator>(bookData greater, bookData less){
        return greater.getBookId() > less.getBookId();
    }
    friend bool operator<(bookData less, bookData greater){
        return less.getBookId() < greater.getBookId();
    }
    bool operator == (bookData& other){
        if(getBookId() == other.getBookId()){
            return true;
        }
        return false;
    };

};

/**
 * function retrieves data from file and puts it into vector
 * @param filename a string that takes the csv files name
 * @param book reads data into vector for the book dataset
 * Ampersand (&) used to pass the parameter by reference instead of making copy
 * Run in debug mode for better formatting.
 */
bool loadFromFile(string filename, vector<bookData>& book) {
    ifstream fIn;
    fIn.open(filename);


    string header;
    if (fIn) {
        // reads first line, the header line and throw it away
        getline(fIn, header);
    }

    // Declare the variables I want to read in
    string title, author, isbn, isbn13, averageRating;
    int bookID;
    char comma; // send the commas from file to this character
    string endOfLine; // used at the end of line so loop goes to next row.

    // while loop that reads in data
    // loop ends when the function reaches the EOF
    while (fIn && fIn.peek() != EOF) {
        // Initialize variables to trip values.
        // Values that will not appear in data.
        string title = "Error";
        string author = "Error";
        string isbn = "Error";
        string isbn13 = "Error";
        string averageRating;
        int bookID = -1;


        fIn >> bookID;
        fIn >> comma;
        getline(fIn, title, ',');
        getline(fIn, author, ',');
        getline(fIn, averageRating, ',');
        getline(fIn, isbn, ',');
        getline(fIn, isbn13);

        // pushes the elements into the book vector
        book.push_back(bookData(bookID, title, author, averageRating, isbn, isbn13));
    }

    fIn.close();
    return true;
}

/**
 * Loops through the bookData vector and returns the average letters per title.
 * Uses a reference to the vector instead of the pointer.
 * @param objs
 */
void averageLettersPerTitle(vector<bookData>& objs){
    string titleString; // variable will be used to hold title info
    int sum = 0; // will hold the int for total number of letters in all titles
    int numBooks = 0; // holds number of books in vector
    int averageLetterTitle = 0; // holds the average letters per title for all data

    // The iterator for this loop is the data value.
    for (bookData& data : objs){
        titleString = data.getTitle(); // Gets the title fields from vector.

        for(int i = 0; i < titleString.length(); ++i){ // While i is less than the titleString length
            if (titleString.at(i) && titleString.at(i)!= ' '){ // if there is a character in the  title string and is not null
                sum+= i; // add the character i to the sum
                numBooks = data.getBookId(); // assign the bookID to numbooks.
            }
        }
    }
    // Divide the sum by the number of books to get the average. Print the average.
    averageLetterTitle = sum/numBooks;
    cout << "Average number of characters for ";
    cout << numBooks;
    cout << " book titles is ";
    cout << averageLetterTitle;
    cout << endl; ;


}

#endif //PROJECT_1_BOOKDATA_H