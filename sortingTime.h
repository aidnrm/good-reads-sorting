//
// Created by amccm on 11/5/2021.
//

#ifndef PROJECT_4_SORTINGTIME_H
#define PROJECT_4_SORTINGTIME_H
// Start timer to record how long it takes to sort.
auto BubbleSortTimeBegin = chrono::high_resolution_clock::now();
// Put vector of bookData into bubble sort.
bubbleSort(bookDataVec);
// Stop timer and calculate total time.
auto BubbleSortTimeEnd = chrono::high_resolution_clock::now();
auto BubbleSortDuration = BubbleSortTimeEnd - BubbleSortTimeBegin;

auto SelectionSortTimeBegin = chrono::high_resolution_clock::now();
// Put vector of bookData into selection sort.
selectionSort(bookDataVec);
auto SelectionSortTimeEnd = chrono::high_resolution_clock::now();
auto SelectionSortDuration = SelectionSortTimeEnd - SelectionSortTimeBegin;

auto SelectionSortStableTimeBegin = chrono::high_resolution_clock::now();
// Put vector of bookData into selection sort.
selectionSortGetTitle(bookDataVec);
auto SelectionSortStableTimeEnd = chrono::high_resolution_clock::now();
auto SelectionSortStableDuration = SelectionSortStableTimeEnd - SelectionSortStableTimeBegin;

auto QuickSortTimeBegin = chrono::high_resolution_clock::now();
// Put vector of bookData into unstable quick sort.
quickSortUnstable(bookDataVec);
auto QuickSortTimeEnd = chrono::high_resolution_clock::now();
auto QuickSortDuration = QuickSortTimeEnd - QuickSortTimeBegin;

auto HeapSortTimeBegin = chrono::high_resolution_clock::now();
// Put vector of bookData into heap sort.
heapSort(bookDataVec);
auto HeapSortTimeEnd = chrono::high_resolution_clock::now();
auto HeapSortDuration = HeapSortTimeEnd - HeapSortTimeBegin;


// Print the time it took to sort each algorithm.
// Bubble Sort time.
auto i_millis = chrono::duration_cast<chrono::milliseconds>(BubbleSortDuration);
auto f_secs = chrono::duration_cast<chrono::duration<float>>(BubbleSortDuration);
cout << "Bubble Sort time elapsed: ", i_millis.count() << '/n';
cout << f_secs.count() << endl;
// Selection Sort time.
auto i_millis1 = chrono::duration_cast<chrono::milliseconds>(SelectionSortDuration);
auto f_secs1 = chrono::duration_cast<chrono::duration<float>>(SelectionSortDuration);
cout << "Selection Sort time elapsed: ", i_millis1.count() << '/n';
cout << f_secs1.count() << endl;

// Selection Sort Stable time.
auto i_millis11 = chrono::duration_cast<chrono::milliseconds>(SelectionSortStableDuration);
auto f_secs111 = chrono::duration_cast<chrono::duration<float>>(SelectionSortStableDuration);
cout << "Stable Selection Sort time elapsed: ", i_millis1.count() << '/n';
cout << f_secs111.count() << endl;
// Quick Sort time.
auto i_millis2 = chrono::duration_cast<chrono::milliseconds>(QuickSortDuration);
auto f_secs2 = chrono::duration_cast<chrono::duration<float>>(QuickSortDuration);
cout << "Unstable Quick Sort time elapsed: ", i_millis2.count() << '/n';
cout << f_secs2.count() << endl;
// Heap Sort time.
auto i_millis3 = chrono::duration_cast<chrono::milliseconds>(HeapSortDuration);
auto f_secs3 = chrono::duration_cast<chrono::duration<float>>(HeapSortDuration);
cout << "Heap Sort time elapsed: ", i_millis3.count() << '/n';
cout << f_secs3.count() << endl;
#endif //PROJECT_4_SORTINGTIME_H
