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
    int bubbleReads = 0; // count the number of reads in each sorting algo
    int bubbleWrites = 0; // count the number of writes in each sorting algo
    int bubbleSortTwoSortReads = 0;
    int bubbleSortTwoSortWrites = 0;
    int selectionReads = 0;
    int selectionWrites = 0;

    int quickReads = 0;
    int quickWrites = 0;
    int heapReads = 0;
    int heapWrites = 0;
    int title = 0; // used to put the row title at top of csv
    int vectorSize = 100; // initial vector size for sorting
    vector<bookData> bookDataVec; // create a bookData vector
    loadFromFile("../books.csv", bookDataVec); // load info into vector of bookData type
    clock_t  start; // used for timing the two sort
    double duration; // used for timing the two sort
/*
    // Two-sort
    vector<bookData> twoSortBookData;
    loadFromFile("../books.csv", twoSortBookData);
    twoSortBookData.resize(1000); // change the vectors size from 3500 to 1000
    start = clock(); // start clock
    bubbleSort(twoSortBookData); // unstable selection sort
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Duration of unstable selection sort " << duration << " seconds" << '\n'; // record the duration of the sort

    start = clock(); // start clock
    selectionSortStableTwoSort(twoSortBookData); // stable selection sort on different field.
    duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    cout << "Duration of stable selection sort " << duration << " seconds" << '\n'; // record the duration of the sort
*/
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
    // Record the number of reads and writes needed to sort a vector of size 100, 200, 300, 400, 500, 600, 700, 800, 900, and 1000
    for(vectorSize; vectorSize <= 1000; vectorSize+=100) {
        // Create a bookData vector and load books info
        vector<bookData> bookDataVec;
        loadFromFile("../books.csv", bookDataVec);
        bookDataVec.resize(vectorSize);
        // Record the reads and writes of bubble sort to csv
        bubbleSort(bookDataVec, bubbleReads, bubbleWrites);
        while(title < 1){
            bubbleSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortFile << bubbleReads << "," << bubbleWrites << endl;

        // Record the reads and writes of two sort bubble sort to csv
        bubbleSortGetTitle(bookDataVec, bubbleSortTwoSortReads, bubbleSortTwoSortWrites);
        while(title < 3){
            bubbleSortTwoSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        bubbleSortTwoSortFile << bubbleSortTwoSortReads << "," << bubbleSortTwoSortWrites << endl;

        // Record the reads and writes of selection sort to csv
        selectionSort(bookDataVec, selectionReads, selectionWrites);
        while(title < 2){
            selectionSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        selectionSortFile << selectionReads << "," << selectionWrites << endl;

        // Record the reads and writes of quick sort to csv
        quickSortUnstable(bookDataVec, quickReads, quickWrites);
        while(title < 4){
            quickSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        quickSortFile << quickReads << "," << quickWrites << endl;

        // Record the reads and writes of heap sort to csv
        heapSort(bookDataVec, heapReads, heapWrites);
        while(title < 5){
            heapSortFile << "Reads" << "," << "Writes" << endl;
            ++title;
        }
        heapSortFile << heapReads << "," << heapWrites << endl;
    }
    bubbleSortFile.close();
    selectionSortFile.close();
    bubbleSortTwoSortFile.close();
    quickSortFile.close();
    heapSortFile.close();

    /*
     * Extra credit: "Performing the same experiment,
     * except double the size of the data set each time
     * (instead of having it grow linearly)."
     */

    int bubbleReadDouble = 0; // count the number of reads in each sorting algo
    int bubbleWriteDouble = 0; // count the number of writes in each sorting algo
    int selectionReadDouble = 0;
    int selectionWriteDouble = 0;
    int stableSelectionReadDouble = 0;
    int stableSelectionWriteDouble = 0;
    int quickReadDouble = 0;
    int quickWriteDouble = 0;
    int heapReadDouble = 0;
    int heapWriteDouble = 0;
    int titleDouble = 0; // used to put the row title at top of csv
    // Create files to store the number of reads and writes.
    ofstream bubbleSortFileDouble;
    bubbleSortFileDouble.open("bubbleSortFileDouble.csv");
    ofstream selectionSortFileDouble;
    selectionSortFileDouble.open("selectionSortFileDouble.csv");
    ofstream selectionSortStableFileDouble;
    selectionSortStableFileDouble.open("selectionSortStableFileDouble.csv");
    ofstream quickSortFileDouble;
    quickSortFileDouble.open("quickSortFileDouble.csv");
    ofstream heapSortFileDouble;
    heapSortFileDouble.open("heapSortFileDouble.csv");
    // Record the number of reads and writes needed to sort a vector that doubles in size.  starting at two and going to 100.
    for(int vectorSizeDouble = 2; vectorSizeDouble <= 100; vectorSizeDouble+=vectorSizeDouble) {
        // Create a bookData vector and load books info
        vector<bookData> bookDataVec;
        loadFromFile("../books.csv", bookDataVec);
        bookDataVec.resize(vectorSizeDouble);

        // Record the reads and writes of bubble sort to csv
        bubbleSort(bookDataVec, bubbleReadDouble, bubbleWriteDouble);
        while(titleDouble < 1){
            bubbleSortFileDouble << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        bubbleSortFile << bubbleReadDouble << "," << bubbleWriteDouble << endl;
        // Record the reads and writes of stable selection sort to csv
        bubbleSortGetTitle(bookDataVec, bubbleSortTwoSortReads, bubbleSortTwoSortWrites);
        while(titleDouble < 3){
            bubbleSortTwoSortFile << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        // Record the reads and writes of selection sort to csv
        selectionSort(bookDataVec, selectionReadDouble, selectionWriteDouble);
        while(titleDouble < 2){
            selectionSortFileDouble << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        selectionSortFileDouble << selectionReadDouble << "," << selectionWriteDouble << endl;

        selectionSortStableFileDouble << stableSelectionReadDouble << "," << stableSelectionWriteDouble << endl;
        // Record the reads and writes of quick sort to csv
        quickSortUnstable(bookDataVec, quickReadDouble, quickWriteDouble);
        while(titleDouble < 4){
            quickSortFileDouble << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        quickSortFileDouble << quickReadDouble << "," << quickWriteDouble << endl;
        // Record the reads and writes of heap sort to csv
        heapSort(bookDataVec, heapReadDouble, heapWriteDouble);
        while(titleDouble < 5){
            heapSortFileDouble << "Reads" << "," << "Writes" << endl;
            ++titleDouble;
        }
        heapSortFileDouble << heapReadDouble << "," << heapWriteDouble << endl;
    }
    bubbleSortFileDouble.close();
    selectionSortFileDouble.close();
    selectionSortStableFileDouble.close();
    quickSortFileDouble.close();
    heapSortFileDouble.close();
    return 0;
}
