#include <bits/stdc++.h>
using namespace std;

bool checkSortedWithoutRecursion(vector<int> arr){
  for(int i=(int)arr.size()-1; i>=1; i--){
    if(arr[i] >= arr[i-1]){
      continue;
        }else return false;
    } return true;
}

int main() {
 vector<int> arr = {-1, 0, 3, 5, 23};
 bool result = checkSortedWithoutRecursion(arr);
 cout << "Is array sorted?: " << boolalpha << result;  
}