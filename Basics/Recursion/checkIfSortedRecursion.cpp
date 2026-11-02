#include <bits/stdc++.h>
using namespace std;

bool checkSortedWithRecursion(vector<int> arr, int num){

    if(num == (int)arr.size()-1){ 
	    return true;
    }
    if(arr[num] > arr[num +1]){
        return false;
    }else {
      return checkSortedWithRecursion(arr, num+1);
    }

}

int main() 
{
  vector<int> arr = {1, 5, 7, 8, 33};
  bool result = checkSortedWithRecursion(arr, 0);
  cout << "Is array sorted?:" << boolalpha << result;
}


