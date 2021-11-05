/*
 * Aiden McCormack
 * CS 124 Section A
 */
#include <iostream>
#include "QuickSort.h"
#include "bookData.h"
#include <vector>
#include <random>
#include <chrono> // Used for timer
using namespace std;
int main() {
    int vectSize = 10; // vector size
    vector<bookData> bookDataVec;
    loadFromFile("../books.csv", bookDataVec);
    bookDataVec.resize(vectSize);
    heapSort(bookDataVec);
    // TODO: Each of the five sorting algorithms should be given identical unsorted vectors to begin with
    // Record the number of reads and writes needed to sort a vector of size 100, 200, 300, 400, 500, 600, 700, 800, 900, and 1000
   /* for(vectSize; vectSize < 1000; vectSize+=10) {
        // Create a bookData vector and load books info
        vector<bookData> bookDataVec;
        loadFromFile("../books.csv", bookDataVec);
        bookDataVec.resize(vectSize);
        // Put vector of bookData into bubble sort.
        bubbleSort(bookDataVec);
        // Put vector of bookData into selection sort.
        selectionSort(bookDataVec);
        // Put vector of bookData into selection sort.
        selectionSortGetTitle(bookDataVec);
        // Put vector of bookData into unstable quick sort.
        quickSortUnstable(bookDataVec);
        // Put vector of bookData into heap sort.
        heapSort(bookDataVec);
    }*/
    return 0;
}
