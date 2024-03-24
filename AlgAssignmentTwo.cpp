// AlgAssignmentTwo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;
#include <iostream>
#include <vector>
#include <string>

int arrayToSort[14] = {11, 1, 30, 2, 51, 6, 29, 7, 67, 15, 118, 4, 89, 23};

class ArrayManager {
private:
    int length = 14;
public:
    bool CheckSorted() {
        for (int i = 0; i < length - 1; i++) {
            if (arrayToSort[i] > arrayToSort[i + 1]) return false;
        }

        return true;
    }

    void ResetArray(int arr[14]) {
        for (int i = 0; i < length; i++) {
            arrayToSort[i] = arr[i];
        }
    }

    void PrintArray() {
        for (int i = 0; i < length; i++)
        {
            cout << arrayToSort[i];
            if (i != length - 1) cout << ", ";
        }

        cout << "\n";
    }
    void SwapElementsAt(int first, int second)
    {
        if (first >= length || second >= length) return; // exit method if out of range exception
        if (first < 0 || second < 0) return; // exit if negative

        int i = arrayToSort[first];
        arrayToSort[first] = arrayToSort[second];
        arrayToSort[second] = i;
    }

    void MoveElementToTarget(int index, int target) {
        cout << "Moving element " << arrayToSort[index] << " to " << target << "\n";
        if (index == target) return;
        if (index < 0) return;

        int element = arrayToSort[index];

        // move the indexed element forwards to target
        if (index < target) {
            for (int i = index; i < target && i < length - 1; i++) {
                arrayToSort[i] = arrayToSort[i + 1];
            }
        }
        // move the indexed element backwards to target
        else {
            for (int i = index; i > target && i >= 0; i--) {
                arrayToSort[i] = arrayToSort[i - 1];
            }
        }

        arrayToSort[target] = element;
    }

    void ShiftElementsForRead(int start, int end, int read) { // for moving elements backwards basically
        int i = end;
        while (i >= start && arrayToSort[i] > read) {
            arrayToSort[i + 1] = arrayToSort[i];
            i--;
        }
        cout << "Moving element " << read << " to " << i + 1 << " || ";
        arrayToSort[i + 1] = read;
    }

    void CopyVectorToArray(vector<int> vec, int start) {
        int i = start;
        for (auto read = vec.begin(); read != vec.end(); ++read) {
            arrayToSort[i] = *read;
            i++;
        }

        PrintArray();
    }

    int GetLength() { return length; }
};

class BubbleSort {
private:
    bool swap = false;
    int now = 0;
    ArrayManager arr;
public:
    BubbleSort(ArrayManager _arr) : arr(_arr) {};

    void BubbleSortArray() {
        cout << "Starting Bubble Sort Algorithm. \n";

        do {
            swap = false;
            for (int i = 0; i < arr.GetLength() - 1; i++) {
                if (arrayToSort[i] > arrayToSort[i + 1]) {
                    arr.SwapElementsAt(i, i + 1);
                    swap = true;
                    cout << "Swapped elements " << i << " and " << i + 1 << " || ";
                }
                else {
                    cout << "Checked elements " << i << " and " << i + 1 << " || ";
                }
                arr.PrintArray();
            }
        } while (swap);

        cout << "Finished Bubble Sort Algorithm. \n \n";
    } 
};

class SelectionSort {
private:
    ArrayManager arr;
public:
    SelectionSort(ArrayManager _arr) : arr(_arr) {};

    void SelectSortArray() {
        cout << "Starting Selection Sort Algorithm. \n";

        for (int i = 0; i < arr.GetLength(); i++) {
            int smallest = i;

            for (int j = i; j < arr.GetLength(); j++)
            {
                if (arrayToSort[j] < arrayToSort[smallest]) smallest = j;
            }

            if (arrayToSort[smallest] != arrayToSort[i]) {
                arr.SwapElementsAt(smallest, i);
                cout << "Moving " << arrayToSort[smallest] << " to spot " << i << " || ";
            }
            else cout << "Leaving " << arrayToSort[i] << " at spot " << i << " || ";
            arr.PrintArray();
        }

        cout << "Finished Selection Sort Algorithm. \n \n";
    }
};

class InsertionSort {
private:
    ArrayManager arr;
    int read = 0;
public:
    InsertionSort(ArrayManager _arr) : arr(_arr) {};

    void InsertSortArray() {
        cout << "Started Insertion Sort Algorithm. \n";

        for (int i = 1; i < arr.GetLength(); i++) {
            arr.ShiftElementsForRead(0, i - 1, arrayToSort[i]);
            arr.PrintArray();
        }

        cout << "Finished Insertion Sort Algorithm. \n \n";
    }
};

class MergeSort {
private:
    ArrayManager arr;

    void swapCheck(int& first, int& second) {
        if (first > second) { // swap
            int temp = second;
            second = first;
            first = temp;
        }
    }

    void FillArray(vector<int>& fill, int start, int end) {
        for (int i = 0; i <= (end - start); i++) {
            fill.push_back(arrayToSort[start + i]);
        }
    }

    void PrintVector(vector<int> print) {
        for (auto i = print.begin(); i != print.end(); ++i) {
            if (i != print.begin()) { cout << ", "; }
            cout << *i;
        }
        cout << "\n";
    }

    vector<int> Merge(vector<int> left, vector<int> right) {
        vector<int> result;

        int lRead = 0;
        int rRead = 0;

        cout << "Left array: ";
        PrintVector(left);
        cout << "Right array: ";
        PrintVector(right);

        while (lRead < left.size() && rRead < right.size())
        {
            if (left.at(lRead) < right.at(rRead)) {
                result.push_back(left.at(lRead));
                lRead++;
            }
            else {
                result.push_back(right.at(rRead));
                rRead++;
            }

            PrintVector(result);
        }

        for (auto i = left.begin() + lRead; i != left.end(); ++i) {
            result.push_back(*i);
            PrintVector(result);
        }

        for (auto i = right.begin() + rRead; i != right.end(); ++i) {
            result.push_back(*i);
            PrintVector(result);
        }

        return result;
    }
protected:
    void MergeSortArray(int left, int right) {
        if (left == right) return;
        swapCheck(left, right);

        cout << "New merge at index " << left << " ~ " << right << "\n";

        int mid = left + (right - left) / 2;
        MergeSortArray(left, mid);
        MergeSortArray(mid + 1, right);
        MergeSortArray(left, mid, right);

        cout << "Completed merge at index " << left << " ~ " << right << "\n";
    }

    void MergeSortArray(int left, int mid, int right) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        vector<int> leftArray; FillArray(leftArray, left, mid);
        vector<int> rightArray; FillArray(rightArray, mid + 1, right);

        cout << "Performing merge on elements " << left << " ~ " << right << ": \n";
        arr.CopyVectorToArray(Merge(leftArray, rightArray), left);
    }
public:
    MergeSort(ArrayManager _arr) : arr(_arr) {};

    void MergeSortArray() {
        cout << "Starting Merge Sort Algorithm. \n";
        int left = 0;
        int right = arr.GetLength() - 1;

        MergeSortArray(left, right);
        cout << "Finished Merge Sort Algorithm. \n \n";
    }
};

class QuickSort {
private:
    ArrayManager arr;
public:
    QuickSort(ArrayManager _arr) : arr(_arr) {};

    void QuickSortArrayOneLoop() {
        cout << "Starting One Iteration Quick Sort Algorithm. \n";
        QuickSortArrayOneLoop(0, arr.GetLength());
        cout << "Finished One Iteration Quick Sort Algorithm. \n \n";
    }

    void QuickSortArrayOneLoop(int start, int end)
    {
        if (start >= end) return;

        cout << "Running iteration with pivot " << arrayToSort[start] << "\n";

        int pivot = arrayToSort[start];
        int currentIndex = start;

        for (int i = start; i < end; i++) {
            if (arrayToSort[i] > pivot) {
                arr.MoveElementToTarget(i, currentIndex + 1);

                if (i < currentIndex) currentIndex--;
            }
            else {
                arr.MoveElementToTarget(i, currentIndex);

                if (i > currentIndex) currentIndex++;
            }

            arr.PrintArray();
        }

        cout << "Iteration complete. \n";
    }

    void QuickSortArray() {
        cout << "Starting Quick Sort Algorithm. \n";
        QuickSortArray(0, arr.GetLength());
        cout << "Finished Quick Sort Algorithm. \n \n";
    }

    void QuickSortArray(int start, int end)
    {
        if (start >= end) return;

        cout << "Running iteration with pivot " << arrayToSort[start] << "\n";

        int pivot = arrayToSort[start];
        int currentIndex = start;

        for (int i = start; i < end; i++) {
            if (arrayToSort[i] > pivot) {
                arr.MoveElementToTarget(i, currentIndex + 1);

                if (i < currentIndex) currentIndex--;
            }
            else {
                arr.MoveElementToTarget(i, currentIndex);

                if (i > currentIndex) currentIndex++;
            }

            arr.PrintArray();
        }

        cout << "Iteration complete. \n";
        QuickSortArray(0, currentIndex);
        QuickSortArray(currentIndex + 1, end);
    }
};

int main()
{
    int array[14] = {11, 1, 30, 2, 51, 6, 29, 7, 67, 15, 118, 4, 89, 23};

    ArrayManager arr;

    BubbleSort bs(arr);
    // bs.BubbleSortArray();
    arr.ResetArray(array);

    SelectionSort ss(arr);
    // ss.SelectSortArray();
    arr.ResetArray(array);

    InsertionSort is(arr);
    // is.InsertSortArray();
    arr.ResetArray(array);

    MergeSort ms(arr);
    ms.MergeSortArray();
    arr.ResetArray(array);

    QuickSort qs(arr);
    qs.QuickSortArrayOneLoop();
    arr.ResetArray(array);

    // qs.QuickSortArray();
    arr.ResetArray(array);

    return 0;
}

