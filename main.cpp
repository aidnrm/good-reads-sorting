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
#include <algorithm>
#include <cstdio> // used for the timer
#include <ctime> // used for the timer
using namespace std;
using std::to_string;
int main() {
    int reads = 0; // count the number of reads in each sorting algo
    int writes = 0; // count the number of writes in each sorting algo
    int quickReads = 0;
    int quickWrites = 0;
    int title = 0; // used to put the row title at top of csv
    int vectorSize = 100; // initial vector size for sorting
    // TODO: The curves of the graphs should mimic the time complexity of the sorting algorithm.
        //TODO: Quiz 5 sorting tradeoff, radix, hashing.
    // Create files to store the number of reads and writes.
    ofstream bubbleSortFile;
    bubbleSortFile.open("bubbleSortFile.csv");
    ofstream bubbleSortTwoSortFile;
    bubbleSortTwoSortFile.open("bubbleSortTwoSort.csv");
    ofstream selectionSortFile;
    selectionSortFile.open("selectionSortFile.csv");
    ofstream quickSortFile;
    quickSortFile.open("quickSortFile.csv");
    ofstream heapSortFile;
    heapSortFile.open("heapSortFile.csv");
    // Create a bookData vector and load books info
    vector<bookData> bookDataVec;
    loadFromFile("../books.csv", bookDataVec);
    random_shuffle(bookDataVec.begin(), bookDataVec.end());
    // Record the number of reads and writes needed to sort a vector of size 100, 200, 300, 400, 500, 600, 700, 800, 900, and 1000
    for(vectorSize; vectorSize <= 1000; vectorSize+=100) {

        bookDataVec.resize(vectorSize);
        // Record the reads and writes of bubble sort to csv
        bubbleSort(bookDataVec, reads, writes);
        while(title < 1){
            bubbleSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortFile << vectorSize << "," << reads << "," << writes << endl;

        // Record the reads and writes of two sort bubble sort to csv
        bubbleSortGetTitle(bookDataVec, reads, writes);
        while(title < 2){
            bubbleSortTwoSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortTwoSortFile << vectorSize << "," << reads << "," << writes << endl;

        // Record the reads and writes of selection sort to csv
        selectionSort(bookDataVec, reads, writes);
        while(title < 3){
            selectionSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        selectionSortFile << vectorSize << "," << reads << "," << writes << endl;

        // Record the reads and writes of quick sort to csv
        quickSortUnstable(bookDataVec, quickReads, quickWrites);
        while(title < 4){
            quickSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        quickSortFile << vectorSize << "," <<  quickReads << "," << quickWrites << endl;

        // Record the reads and writes of heap sort to csv
        heapSort(bookDataVec, reads, writes);
        while(title < 5){
            heapSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        heapSortFile << vectorSize << "," << reads << "," << writes << endl;
    }
    bubbleSortFile.close();
    bubbleSortTwoSortFile.close();
    selectionSortFile.close();
    quickSortFile.close();
    heapSortFile.close();

    /*
     * Extra credit: "Performing the same experiment,
     * except double the size of the data set each time
     * (instead of having it grow linearly)."
     */

    int readDouble = 0; // count the number of reads in each sorting algo
    int writeDouble = 0; // count the number of writes in each sorting algo
    int quickReadDouble = 0;
    int quickWriteDouble = 0;
    int titleDouble = 0; // used to put the row title at top of csv
    // Create files to store the number of reads and writes.
    ofstream bubbleSortFileDouble;
    bubbleSortFileDouble.open("bubbleSortFileDouble.csv");
    ofstream bubbleSortTwoSortFileDouble;
    bubbleSortTwoSortFileDouble.open("bubbleSortTwoSortFileDouble.csv");
    ofstream selectionSortFileDouble;
    selectionSortFileDouble.open("selectionSortFileDouble.csv");
    ofstream quickSortFileDouble;
    quickSortFileDouble.open("quickSortFileDouble.csv");
    ofstream heapSortFileDouble;
    heapSortFileDouble.open("heapSortFileDouble.csv");
    // Record the number of reads and writes needed to sort a vector that doubles in size.  Vector doubles 10 times.
    for(int vectorSizeDouble = 2; vectorSizeDouble <= 1500; vectorSizeDouble+=vectorSizeDouble) {
        bookDataVec.resize(vectorSizeDouble);
        // Record the reads and writes of the bubble sort double to csv
        bubbleSort(bookDataVec, readDouble, writeDouble);
        while(titleDouble < 1){
            bubbleSortFileDouble << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        bubbleSortFileDouble << vectorSizeDouble << "," << readDouble << "," << writeDouble << endl;
        // Record the reads and writes bubble sort double on a different field to csv
        bubbleSortGetTitle(bookDataVec, readDouble, writeDouble);
        while(titleDouble < 2){
            bubbleSortTwoSortFileDouble << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        bubbleSortTwoSortFileDouble << vectorSizeDouble << "," << readDouble << "," << writeDouble << endl;

        // Record the reads and writes of selection sort to csv
        selectionSort(bookDataVec, readDouble, writeDouble);
        while(titleDouble < 3){
            selectionSortFileDouble << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        selectionSortFileDouble << vectorSizeDouble << "," << readDouble << "," << writeDouble << endl;

        // Record the reads and writes of quick sort to csv
        quickSortUnstable(bookDataVec, quickReadDouble, quickWriteDouble);
        while(titleDouble < 4){
            quickSortFileDouble << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        quickSortFileDouble << vectorSizeDouble << "," << quickReadDouble << "," << quickReadDouble << endl;
        // Record the reads and writes of heap sort to csv
        heapSort(bookDataVec, readDouble, writeDouble);
        while(titleDouble < 5){
            heapSortFileDouble << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        heapSortFileDouble << vectorSizeDouble << "," << readDouble << "," << writeDouble << endl;
    }
    bubbleSortFileDouble.close();
    selectionSortFileDouble.close();
    bubbleSortTwoSortFile.close();
    quickSortFileDouble.close();
    heapSortFileDouble.close();
    return 0;
}
