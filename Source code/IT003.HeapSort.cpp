#include <iostream>
using namespace std;

void heapify(double arr[], int N, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && arr[l] > arr[largest])
        largest = l;

    if (r < N && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);

    heapify(arr, N, largest);
    }
}

void heapSort(double arr[], int N)
{

    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
    for (int i = N - 1; i > 0; i--) {
        swap(arr[0], arr[i]);

    heapify(arr, i, 0);
    }
}

int main()
{

    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    int N = 1000000;
    static double arr[1000000];
    for (int i = 0; i < N; i++) cin >> arr[i];

    clock_t Start, End;
    double duration;

    Start = clock();
    // Function call
    heapSort(arr, N);
    //Function end
    End = clock();

    duration = (double)(End - Start)/CLOCKS_PER_SEC;
    cout << duration;

    return 0;
}
