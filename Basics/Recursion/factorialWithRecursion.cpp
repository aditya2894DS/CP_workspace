#include <bits/stdc++.h>
using namespace std;

bool checkSortedWithRecursion(vector<int> arr, int i){
  if(i==1){
    return true;
  }
  return (arr[i-1] < arr[i-2]) ? false : checkSortedWithRecursion(arr, i-1);
}

int main() {
 vector<int> arr = {1, 2, 2, 5, 6};
 bool result = checkSortedWithRecursion(arr, arr.size());
 cout << "Is array sorted?: " << boolalpha << result;  
}