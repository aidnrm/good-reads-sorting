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
    clock_t  start;
    double duration;
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

    int vectorSize = 100;
    vector<bookData> bookDataVec;
    loadFromFile("../books.csv", bookDataVec);

    // Record the number of reads and writes needed to sort a vector of size 100, 200, 300, 400, 500, 600, 700, 800, 900, and 1000
    int quickReads = 0;
    int quickWrites = 0;

    for(vectorSize; vectorSize <= 1000; vectorSize+=100) {
        // Create a bookData vector and load books info
        vector<bookData> bookDataVec;
        loadFromFile("../books.csv", bookDataVec);
        bookDataVec.resize(vectorSize);

        bubbleSort(bookDataVec);
        selectionSort(bookDataVec);
        selectionSortStable(bookDataVec);

        quickSortUnstable(bookDataVec, quickReads, quickWrites);
        ofstream quickSortFile;
        quickSortFile.open("quickSortFile.csv", std::ios_base::app);

        for(int i = 100; i < vectorSize; i+= 100){
                quickSortFile << quickReads << "," << quickWrites << endl;
            }
            quickSortFile.close();
        }
        heapSort(bookDataVec);


    return 0;
}
