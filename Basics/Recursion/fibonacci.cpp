#include <bits/stdc++.h>
using namespace std;

int fibonacci(int num){
	if(num == 0) return 0;
	vector<int> arr(num + 1);
	arr[0] = 0;
	arr[1] = 1;
	for(int i=2; i< num+1; i++){
		arr[i] = arr[i-1] + arr[i-2];
	}
	return arr[num];
}

// Recursive version that prints the call stack as it runs.
// Each level of indentation = one more frame on the stack.
int calls = 0;

int fibonacciTrace(int num, int depth){
	calls++;
	string indent(depth * 4, ' ');
	if(num <= 1){
		cout << indent << "fib(" << num << ") -> base case, return " << num << endl;
		return num;
	}
	cout << indent << "fib(" << num << ") pushed  [stack depth " << depth + 1 << "]" << endl;
	int left = fibonacciTrace(num - 1, depth + 1);
	int right = fibonacciTrace(num - 2, depth + 1);
	cout << indent << "fib(" << num << ") popped, return " << left << " + " << right << " = " << left + right << endl;
	return left + right;
}

int main() {

    int num;

    // cout << "Enter number:";
    cin >> num;
 	int result = fibonacci(num);
    cout << "The result is: " << result << endl;

    cout << "\nCall stack trace (recursive):" << endl;
    int traced = fibonacciTrace(num, 0);
    cout << "\nRecursive result: " << traced << ", total calls: " << calls << endl;


    return 0;
}
