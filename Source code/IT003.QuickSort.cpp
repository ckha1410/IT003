#include <bits/stdc++.h>
using namespace std;

int Partition(float arr[], int low, int high)
{
    int pivot = arr[low];
    int pivotIndex = low;
    int storeIndex = pivotIndex + 1;
    for (int i = pivotIndex + 1; i <= high; i++)
    {
        if (arr[i] < pivot)
        {
            swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }
    swap(arr[low], arr[storeIndex-1]);
    return storeIndex - 1;
}

void quickSort(float arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

  freopen("input1.txt", "r", stdin);
  freopen("output1.txt", "w", stdout);

  int n = 1000000;
  static float arr[1000000];

  for (int i = 0; i < n; i++) cin >> arr[i];

  clock_t Start, End;
  double duration;

  Start = clock();
  // Function call
  quickSort(arr, 0, n - 1);
  // Function end
  End = clock();

  duration = (double)(End - Start)/CLOCKS_PER_SEC;
  cout << duration;

  return 0;
}
