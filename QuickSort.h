#include <cmath>
#include "bookData.h"
#include <iostream>
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
vector<Comparable> heapSort(vector<Comparable> items) {
    int heapReads = 0; // Count the number of times you use a Comparable object.
    int heapWrites = 0; // Count the number of times you assign into a Comparable object.
    int i, j, child = 0;
    Comparable temp, tmp;
    // build the heap (with max value at root)
    ++heapReads; // reading information from items
    ++heapWrites; // writing information to i
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        percolateDown(items, i, items.size(), child, tmp);
    }
    printVec(items);
    // keep deleting the max
    ++heapReads; // reading information from items
    ++heapWrites; // writing information to j
    for (j = items.size() - 1; j > 0; --j) {
        heapReads = heapReads + 3; // reads items at index 0, items at index j and temp
        heapWrites = heapWrites + 3; // writes to temp, items at index 0 and items at index j.
        // swap the maximum out
        temp = items[0];
        items[0] = items[j];
        items[j] = temp;

        // make it into a heap again
        percolateDown(items, 0, j, child, tmp);
        printVec(items);
    }
    return items;
}

template<typename Comparable>
void bubbleSort(vector<Comparable> vec) {
    int bubbleReads = 0;
    int bubbleWrites = 0;
    bool haveSwapped = true;

    ++bubbleReads; // reads the vec size
    ++bubbleWrites; // writes to max index
    int maxIndex = vec.size(), i;
    //TODO: Figure out if I read or write here.
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        ++bubbleReads; // reads the maxIndex
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
        printVec(vec);
        // Update maxIndex
        --maxIndex;
    }
}

template<typename Comparable>
void selectionSort(vector<Comparable> vec) {
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
        printVec(vec);
    }
}

// stable selection sort
template<typename Comparable>
void selectionSortGetTitle(vector<Comparable> vec) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            if (vec[i].getTitle() < vec[minIndex].getTitle()) {
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex];
        vec[swapIndex] = vec[minIndex];
        vec[minIndex] = temp;
        printVec(vec);
    }
}




template<typename Comparable>
void quickSortUnstableRec(vector<Comparable> &vec, int startIndex, int endIndex) {
    if (endIndex <= startIndex) {
        // There is only one element left. Nothing to do.
        return;
    }
    Comparable partition = vec[startIndex];
    Comparable temp;
    int i;
    int largerElementIndex = startIndex + 1;
    for (i = startIndex; i <= endIndex; ++i) {
        if (vec[i] < partition) {
            // Swap the element with the one at largerElementIndex to keep smaller elements grouped
            temp = vec[i];
            vec[i] = vec[largerElementIndex];
            vec[largerElementIndex] = temp;
            // Update largerElementIndex
            ++largerElementIndex;
        }
    }
    vec[startIndex] = vec[largerElementIndex - 1];
    vec[largerElementIndex - 1] = partition;

    printVec(vec);

    // Recursive call for less-than-partition side
    quickSortUnstableRec(vec, startIndex, largerElementIndex - 2);
    // Recursive call for greater-than-or-equal-to-partition side
    quickSortUnstableRec(vec, largerElementIndex, endIndex);
}

template<typename Comparable>
void quickSortUnstable(vector<Comparable> vec) {
    quickSortUnstableRec(vec, 0, vec.size() - 1);
}

template<typename Comparable>
void quickSortStableRec(vector<Comparable> &vec) {
    // Recursive base case
    if (vec.size() <= 1) {
        return;
    }
    // Choose a partition element
    Comparable partition = vec[0];
    vector<Comparable> smaller, equal, larger;
    // Loop through vec and populate smaller, equal, larger
    int i;
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i] < partition) {
            smaller.push_back(vec[i]);
        } else if (vec[i] == partition) {
            equal.push_back(vec[i]);
        } else {
            larger.push_back(vec[i]);
        }
    }
    // Recursive calls
    quickSortStableRec(smaller);
    quickSortStableRec(larger);
    // Copy everything back into vec
    for (i = 0; i < vec.size(); ++i) {
        if (i < smaller.size()) {
            vec[i] = smaller[i];
        } else if (i < smaller.size() + equal.size()) {
            vec[i] = equal[i - smaller.size()];
        } else {
            vec[i] = larger[i - smaller.size() - equal.size()];
        }
    }
    printVec(vec);
}

template<typename Comparable>
void quickSortStable(vector<Comparable> vec) {
    quickSortStableRec(vec);
}
