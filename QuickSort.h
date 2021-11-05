#include <cmath>
#include "bookData.h"
#include <iostream>

#include <vector>
using namespace std;

void readsAndWrites(int reads, int writes){
    cout << "Number of reads: ";
    cout << reads << endl;
    cout << "Number of writes: ";
    cout << writes << endl;
}
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
    Comparable temp, tmp; //TODO: Does this count as a read?
    // build the heap (with max value at root)
    ++heapReads; // reading information from items
    ++heapWrites; // writing information to i
    for (i = items.size() / 2 - 1; i >= 0; --i) { // TODO: Does the item size count as a read?
        heapReads = 3 + heapReads; // //TODO: Does this count as a read?
        percolateDown(items, i, items.size(), child, tmp);
    }
    ++heapReads; // read items
    printVec(items); //TODO: Does this count as a read?
    // keep deleting the max
    ++heapReads; // reading items.size()
    ++heapWrites; // writing information to j
    for (j = items.size() - 1; j > 0; --j) {
        heapReads = heapReads + 3; // reads items at index 0, items at index j and temp
        heapWrites = heapWrites + 3; // writes to temp, items at index 0 and items at index j.
        // swap the maximum out
        temp = items[0];
        items[0] = items[j];
        items[j] = temp;

        // make it into a heap again
        heapReads = heapReads + 3; // TODO: Does this count as a read?
        percolateDown(items, 0, j, child, tmp);
        ++heapReads; // TODO: Does this count as a read?
        printVec(items);

    }
    readsAndWrites(heapReads, heapWrites);
    return items;

}

template<typename Comparable>
void bubbleSort(vector<Comparable> vec) {
    int bubbleReads = 0;
    int bubbleWrites = 0;
    bool haveSwapped = true;

    ++bubbleReads; // TODO: Does the vec.size() count as a read?
    ++bubbleWrites; // writes to max index
    int maxIndex = vec.size(), i;
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
        // TODO: Read?
        printVec(vec);

        // Update maxIndex
        ++bubbleReads; // reads maxIndex
        ++bubbleWrites; // writes the new maxIndex
        --maxIndex;
    }
}

template<typename Comparable>
void selectionSort(vector<Comparable> vec) {
    int selectionSortReads = 0;
    int selectionSortWrites = 0;
    int swapIndex, i, minIndex;
    Comparable temp;
    ++selectionSortReads; // reads vec.size()
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        ++selectionSortReads; // reads vec.size()
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
        printVec(vec); //TODO: Does this count?

    }
}

// stable selection sort
template<typename Comparable>
void selectionSortGetTitle(vector<Comparable> vec) {
    int stableSelectionSortReads = 0;
    int stableSelectionSortWrites = 0;
    int swapIndex, i, minIndex;
    Comparable temp; // TODO: Does this temp count?
    ++stableSelectionSortReads; // reads vec.size()
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        ++stableSelectionSortReads; // reads the vec.size()
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
        printVec(vec); // TODO: AM I reading into the printVec function?
    }
}




template<typename Comparable>
void quickSortUnstableRec(vector<Comparable> &vec, int startIndex, int endIndex) {
    int quickSortRead = 0;
    int quickSortWrite = 0;
    if (endIndex <= startIndex) {
        // There is only one element left. Nothing to do.
        return;
    }
    ++quickSortWrite; // write to the partition
    ++quickSortRead; // read the vec starting index
    Comparable partition = vec[startIndex];
    Comparable temp; // TODO: Does this update the read?
    int i;
    int largerElementIndex = startIndex + 1;
    for (i = startIndex; i <= endIndex; ++i) {
        quickSortRead = quickSortRead + 2; // reads the vec[i] and the partition.
        if (vec[i] < partition) {
            // Swap the element with the one at largerElementIndex to keep smaller elements grouped
            quickSortRead = 3 + quickSortRead; // reads the vec[i], vec[largerElementIndex], temp
            quickSortWrite = 3 + quickSortWrite; // write to the temp, vec[i], vec[largerElementIndex].
            temp = vec[i];
            vec[i] = vec[largerElementIndex];
            vec[largerElementIndex] = temp;
            // Update largerElementIndex
            ++largerElementIndex;
        }
    }
    quickSortRead = 2 + quickSortRead; // reads the vec[largerElementIndex - 1] and partition
    quickSortWrite = 2 + quickSortWrite; // writes to the vec[startIndex] and vec[largerElementIndex - 1]
    vec[startIndex] = vec[largerElementIndex - 1];
    vec[largerElementIndex - 1] = partition;

    printVec(vec); // TODO: Update the read?

    // TODO: Update the read for the recursive calls?
    // Recursive call for less-than-partition side
    quickSortUnstableRec(vec, startIndex, largerElementIndex - 2);
    // Recursive call for greater-than-or-equal-to-partition side
    quickSortUnstableRec(vec, largerElementIndex, endIndex);
}

template<typename Comparable>
void quickSortUnstable(vector<Comparable> vec) {
    quickSortUnstableRec(vec, 0, vec.size() - 1);
}