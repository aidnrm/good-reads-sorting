/*
 * Aiden McCormack
 * CS 124 Section A
 */
#include <iostream>
#include "QuickSort.h"
#include "bookData.h"
#include <vector>
#include <random>
#include <string>
#include <cstdio> // used for the timer
#include <ctime> // used for the timer
using namespace std;
using std::to_string;
int main() {
    int reads = 0; // count the number of reads in each sorting algo
    int writes = 0; // count the number of writes in each sorting algo
    int title = 0; // used to put the row title at top of csv
    int vectorSize = 100; // initial vector size for sorting
    vector<bookData> bookDataVec; // create a bookData vector
    loadFromFile("../books.csv", bookDataVec); // load info into vector of bookData type
    clock_t  start; // used for timing the two sort
    double duration; // used for timing the two sort

    // Two-sort
    vector<bookData> twoSortBookData;
    loadFromFile("../books.csv", twoSortBookData);
    twoSortBookData.resize(1000); // change the vectors size from 3500 to 1000
    start = clock(); // start clock
    selectionSortTwoSort(twoSortBookData); // unstable selection sort
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Duration of unstable selection sort " << duration << " seconds" << '\n'; // record the duration of the sort

    start = clock(); // start clock
    selectionSortStableTwoSort(twoSortBookData); // stable selection sort on different field.
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Duration of stable selection sort " << duration << " seconds" << '\n'; // record the duration of the sort


    // Record the number of reads and writes needed to sort a vector of size 100, 200, 300, 400, 500, 600, 700, 800, 900, and 1000
    for(vectorSize; vectorSize <= 1000; vectorSize+=100) {
        // Create a bookData vector and load books info
        vector<bookData> bookDataVec;
        loadFromFile("../books.csv", bookDataVec);
        bookDataVec.resize(vectorSize);

        bubbleSort(bookDataVec, reads, writes);
        ofstream bubbleSortFile;
        bubbleSortFile.open("bubbleSortFile.csv", ios_base::app);
        while(title < 1){
            bubbleSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortFile << reads << "," << writes << endl;
        bubbleSortFile.close();

        selectionSort(bookDataVec, reads, writes);
        ofstream selectionSortFile;
        selectionSortFile.open("selectionSortFile.csv", ios_base::app);
        while(title < 2){
            selectionSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        selectionSortFile << reads << "," << writes << endl;
        selectionSortFile.close();


        selectionSortStable(bookDataVec, reads, writes);
        ofstream selectionSortStableFile;
        selectionSortStableFile.open("selectionSortStableFile.csv", ios_base::app);
        while(title < 2){
            selectionSortStableFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        selectionSortStableFile << reads << "," << writes << endl;
        selectionSortStableFile.close();
        quickSortUnstable(bookDataVec, reads, writes);
        ofstream quickSortFile;
        quickSortFile.open("quickSortFile.csv", ios_base::app);
        while(title < 3){
            quickSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        quickSortFile << reads << "," << writes << endl;
        quickSortFile.close();
        heapSort(bookDataVec, reads, writes);
        ofstream heapSortFile;
        heapSortFile.open("heapSortFile.csv", ios_base::app);
        while(title < 4){
            heapSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        heapSortFile << reads << "," << writes << endl;
        heapSortFile.close();
        }
    return 0;
}
