#include <cmath>
#include "bookData.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename Comparable>
void printVec(const vector<Comparable> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << endl;
}

// Helper function for heapSort
inline int leftChild(int i) {
    return 2 * i + 1;
}

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
template <typename Comparable>
void percolateDown(vector<Comparable> &items, int i, int n, int child, Comparable tmp) {
    for(tmp = items[i]; leftChild(i) < n; i = child) {
        child = leftChild(i);
        // choose the child with the larger value
        if (child != n - 1 && items[child] < items[child + 1]) {
            ++child;
        }
        // if the parent is less than the child, swap them
        if (tmp < items[child]) {
            items[i] = items[child];
        } else {
            // parent is >= both children. nothing more to do.
            break;
        }
    }
    items[i] = tmp;
}

template <typename Comparable>
vector<Comparable> heapSort(vector<Comparable> items, int &heapReads, int &heapWrites) {

    int i, j, child = 0;
    Comparable temp, tmp;

    for (i = items.size() / 2 - 1; i >= 0; --i) {
        percolateDown(items, i, items.size(), child, tmp);
    }
    // keep deleting the max

    for (j = items.size() - 1; j > 0; --j) {
        heapReads = heapReads + 3; // reads items at index 0, items at index j and temp
        heapWrites = heapWrites + 3; // writes to temp, items at index 0 and items at index j.
        // swap the maximum out
        temp = items[0];
        items[0] = items[j];
        items[j] = temp;

        // make it into a heap again
        percolateDown(items, 0, j, child, tmp);
    }
    return items;

}

template<typename Comparable>
void bubbleSort(vector<Comparable> vec, int &bubbleReads, int &bubbleWrites) {
    bool haveSwapped = true;

    int maxIndex = vec.size(), i;
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            // Compare items at indices i and i+1 and swap if necessary
            bubbleReads = bubbleReads + 2; // reads both comparable objects in if statement.
            if (vec[i] > vec[i+1]) {
                bubbleReads = bubbleReads + 3; // read vec[i], vec[i+1], temp
                bubbleWrites = bubbleWrites + 3; // write temp, vec[i], vec[i+1]
                temp = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = temp;
                // Update haveSwapped
                haveSwapped = true;
            }
        }
        --maxIndex;
    }
}

template<typename Comparable>
void selectionSort(vector<Comparable> vec, int &selectionSortReads, int &selectionSortWrites) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            selectionSortReads = selectionSortReads + 2; // reads the vec[i] and vec[minIndex].
            if (vec[i] < vec[minIndex]) {
                minIndex = i;
            }
        }
        selectionSortReads = selectionSortReads + 3; // reads vec[swapIndex], vec[minIndex], temp
        selectionSortWrites = selectionSortWrites + 3; // reads temp, vec[swapIndex], vec[minIndex]
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        vec[swapIndex] = vec[minIndex];
        vec[minIndex] = temp;
    }
}

// stable selection sort
template<typename Comparable>
void selectionSortStable(vector<Comparable> vec, int &stableSelectionSortReads, int &stableSelectionSortWrites) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            stableSelectionSortReads = 2 + stableSelectionSortReads; // reads vec[i] and vec[minIndex]
            if (vec[i].getTitle() < vec[minIndex].getTitle()) { // Compares the getTitle field instead of bookID.
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        stableSelectionSortReads = 3 + stableSelectionSortReads; // read vec[swapIndex], vec[minIndex], temp.
        stableSelectionSortWrites = 3 + stableSelectionSortWrites; // write temp, vec[swapIndex], vec[minIndex].
        temp = vec[swapIndex];
        vec[swapIndex] = vec[minIndex];
        vec[minIndex] = temp;
    }
}

template<typename Comparable>
int quickSortUnstableRec(vector<Comparable> &vec, int startIndex, int endIndex, int &quickReads, int &quickWrites) {
    if (endIndex <= startIndex) {
        // There is only one element left. Nothing to do.
        return true;
    }
    ++quickWrites; // write to the partition
    ++quickReads; // read the vec starting index
    Comparable partition = vec[startIndex];
    Comparable temp;
    int i;
    int largerElementIndex = startIndex + 1;
    for (i = startIndex; i <= endIndex; ++i) {
        quickReads = quickReads + 2; // reads the vec[i] and the partition.
        if (vec[i] < partition) {
            // Swap the element with the one at largerElementIndex to keep smaller elements grouped
            quickReads = 3 + quickReads; // reads the vec[i], vec[largerElementIndex], temp
            quickWrites = 3 + quickWrites; // write to the temp, vec[i], vec[largerElementIndex].
            temp = vec[i];
            vec[i] = vec[largerElementIndex];
            vec[largerElementIndex] = temp;
            // Update largerElementIndex
            ++largerElementIndex;
        }
    }
    quickReads = 2 + quickReads; // reads the vec[largerElementIndex - 1] and partition
    quickWrites = 2 + quickWrites; // writes to the vec[startIndex] and vec[largerElementIndex - 1]
    vec[startIndex] = vec[largerElementIndex - 1];
    vec[largerElementIndex - 1] = partition;

    // Recursive call for less-than-partition side
    quickSortUnstableRec(vec, startIndex, largerElementIndex - 2, quickReads, quickWrites);
    // Recursive call for greater-than-or-equal-to-partition side
    quickSortUnstableRec(vec, largerElementIndex, endIndex, quickReads, quickWrites);
    return quickReads, quickWrites;
}

template<typename Comparable>
void quickSortUnstable(vector<Comparable> vec, int &quickReads, int &quickWrite) {
    quickSortUnstableRec(vec, 0, vec.size() - 1, quickReads, quickWrite);
}

// Selection sort for two sort comparison.
template<typename Comparable>
void selectionSortTwoSort(vector<Comparable> vec) {

    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i] < vec[minIndex]) {
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        vec[swapIndex] = vec[minIndex];
        vec[minIndex] = temp;
    }
}

// Stable selection sort for getTitle field.
template<typename Comparable>
void selectionSortStableTwoSort(vector<Comparable> vec) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i].getTitle() < vec[minIndex].getTitle()) { // Compares the getTitle field instead of bookID.
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        vec[swapIndex] = vec[minIndex];
        vec[minIndex] = temp;
    }
}