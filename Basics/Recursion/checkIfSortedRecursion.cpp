#include <bits/stdc++.h>
using namespace std;

bool checkSortedWithRecursion(vector<int> arr){
  int diff;
  for(int i=0; i+1<(int)arr.size(); i++){
    diff = arr[i+1] - arr[i];
    cout << "diff: " << diff << endl;
    if(diff < 0){
      return false;
        }
    } return true;
}

int main() {
 vector<int> arr = {-1, 0, 3, 5, 23};
 bool result = checkSortedWithRecursion(arr);
 cout << "Is array sorted?: " << boolalpha << result;  
}