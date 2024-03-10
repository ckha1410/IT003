#include <bits/stdc++.h>
using namespace std;

void Merge(double arr[], int const l, int const mid, int const r)
{
    int const subArrOne = mid - l + 1;
    int const subArrTwo = r - mid;

    auto *leftArr = new double[subArrOne],
         *rightArr = new double[subArrTwo];

    for (auto i = 0; i < subArrOne; i++)
        leftArr[i] = arr[l + i];
    for (auto j = 0; j < subArrTwo; j++)
        rightArr[j] = arr[mid + 1 + j];

    auto indexOfSubArrOne = 0, indexOfSubArrTwo = 0;
    int indexOfMergedArr = l;

    while (indexOfSubArrOne < subArrOne && indexOfSubArrTwo < subArrTwo)
    {
        if (leftArr[indexOfSubArrOne] <= rightArr[indexOfSubArrTwo])
        {
            arr[indexOfMergedArr] = leftArr[indexOfSubArrOne];
            indexOfSubArrOne++;
        }
        else
        {
            arr[indexOfMergedArr] = rightArr[indexOfSubArrTwo];
            indexOfSubArrTwo++;
        }
        indexOfMergedArr++;
    }

    while (indexOfSubArrOne < subArrOne)
    {
        arr[indexOfMergedArr] = leftArr[indexOfSubArrOne];
        indexOfSubArrOne++;
        indexOfMergedArr++;
    }

    while (indexOfSubArrTwo < subArrTwo)
    {
        arr[indexOfMergedArr] = rightArr[indexOfSubArrTwo];
        indexOfSubArrTwo++;
        indexOfMergedArr++;
    }
    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(double arr[], int const Begin, int const End)
{
    if (Begin >= End)
        return;

    int mid = Begin + (End - Begin) / 2;
    mergeSort(arr, Begin, mid);
    mergeSort(arr, mid + 1, End);
    Merge(arr, Begin, mid, End);
}


int main()
{
    freopen("input3.txt", "r", stdin);
    freopen("output3.txt", "w", stdout);

    int N = 1000000;
    static double arr[1000000];
    for (int i = 0; i < N; i++) cin >> arr[i];

    clock_t Start, End;
    double duration;

    Start = clock();
    // Function call
    mergeSort(arr, 0, N - 1);
    //Function end
    End = clock();

    duration = (double)(End - Start)/CLOCKS_PER_SEC;
    cout << duration;

    return 0;
}
