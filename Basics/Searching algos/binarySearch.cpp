/*
    Binary Search

    Given a sorted array of n integers (in ascending order) and an integer
    target, find the index of target in the array. If target is not present,
    return -1.

    Your algorithm must run in O(log n) time.

    Input:
        The first line contains two integers n and target.
        The second line contains n space-separated integers, sorted in
        ascending order.

    Output:
        Print the index (0-based) of target, or -1 if it is not found.

    Example 1:
        Input:
            6 9
            -1 0 3 5 9 12
        Output:
            4
        Explanation: 9 exists in the array at index 4.

    Example 2:
        Input:
            6 2
            -1 0 3 5 9 12
        Output:
            -1
        Explanation: 2 does not exist in the array.

    Constraints:
        1 <= n <= 10^5
        -10^9 <= arr[i], target <= 10^9
        All elements of the array are distinct.
        The array is sorted in ascending order.
*/

#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> arr, int firstIndex, int lastIndex, int num){
	int mid = (lastIndex - firstIndex)/2;
	if(arr[mid] == num) {
		return mid;
	}
	
	if(num > arr[mid]){
		return binarySearch(arr, mid, arr.size(), num);
	}
	if(num < arr[mid]){
		return binarySearch(arr, 0, mid, num);
	}
    return -1;
}

int main()
{
	vector<int> arr = {-1, 0, 3, 5, 9, 12};

	int result = binarySearch(arr, 0, arr.size(), 9);
    cout << "Required index: " << result;

    return 0;
}