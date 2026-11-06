

#include <bits/stdc++.h>
using namespace std;

bool checkIfSortedRecursion(vector<int> arr, int currentIndex)
{

    if (currentIndex >= (int)arr.size() - 1)
        return true;
    if (arr[currentIndex] > arr[currentIndex + 1])
        return false;
    else
        return checkIfSortedRecursion(arr, currentIndex + 1);
}

int main()
{
    // Write C++ code here
    vector<int> arr = {1, 5, 7, 34, 33};
    cout << boolalpha << checkIfSortedRecursion(arr, 0);
    return 0;
}
