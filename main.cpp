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
    // Ints for counting the reads and writes of each sorting algorithm.
    int reads = 0;
    int writes = 0;
    // Use different ints for recursive sorting algorithm.
    int quickReads = 0;
    int quickWrites = 0;
    // Title int used to put the title at top of each csv.
    int title = 0;
    // initial vector size for sorting
    int vectorSize = 1000;
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
    // Shuffle vector for better data, since my comparable obj is ordered from least to greatest.
    random_shuffle(bookDataVec.begin(), bookDataVec.end());
    // Record the number of reads and writes needed to sort a vector of size 100, 200, 300, 400, 500, 600, 700, 800, 900, and 1000
    // TODO: Change for loop to go from 1000 to 100.
    for(vectorSize; vectorSize >= 100; vectorSize-=100) {
        bookDataVec.resize(vectorSize);
        // Record the reads and writes of bubble sort to csv.
        bubbleSort(bookDataVec, reads, writes);
        while(title < 1){
            bubbleSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortFile << vectorSize << "," << reads << "," << writes << endl;
        // Record the reads and writes of bubble sort using a different comparable obj.
        bubbleSortGetTitle(bookDataVec, reads, writes);
        while(title < 2){
            bubbleSortTwoSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortTwoSortFile << vectorSize << "," << reads << "," << writes << endl;
        // Record the reads and writes of selection sort to csv.
        selectionSort(bookDataVec, reads, writes);
        while(title < 3){
            selectionSortFile << "Vector Size" << "," << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        selectionSortFile << vectorSize << "," << reads << "," << writes << endl;
        // Record the reads and writes of quick sort to csv.
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
    // Close all files.
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
    // Ints for counting the reads and writes of each sorting algorithm.
    int readDouble = 0;
    int writeDouble = 0;
    // Use different ints for recursive sorting algorithm.
    int quickReadDouble = 0;
    int quickWriteDouble = 0;
    // Title int used to put the title at top of each csv.
    int titleDouble = 0;
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

        // Record the reads and writes of a selection sort
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
    // Close all files.
    bubbleSortFileDouble.close();
    selectionSortFileDouble.close();
    bubbleSortTwoSortFile.close();
    quickSortFileDouble.close();
    heapSortFileDouble.close();
    return 0;
}
