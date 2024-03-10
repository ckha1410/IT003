#include <bits/stdc++.h>
using namespace std;

int main() {

  freopen("input1.txt", "r", stdin);
  freopen("output1.txt", "w", stdout);

  int n = 1000000;
  static double arr[1000000];

  for (int i = 0; i < n; i++) cin >> arr[i];

  clock_t Start, End;
  double duration;

  Start = clock();
  // Function call
  sort(arr, arr + n);
  //Function end
  End = clock();

  duration = (double)(End - Start)/CLOCKS_PER_SEC;
  cout << duration;

  return 0;
}
