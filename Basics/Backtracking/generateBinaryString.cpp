/* Problem: Generate all binary strings

Given an integer N, print every string of length N made of the characters 0 and 1, one per line.

Input (input.txt):
3

Output (output.txt):
000
001
010
011
100
101
110
111 */

#include <bits/stdc++.h>
using namespace std;

char A[3];
void binary(int n)
{
    if (n < 1)
    {
        cout << A << endl; // Assume array A is a global variable
        return;
    }

    A[n - 1] = '0';
    binary(n - 1);
    A[n - 1] = '1';
    binary(n - 1);
}

int main()
{
    int n;
    cin >> n;
    binary(n);

    return 0;
}
