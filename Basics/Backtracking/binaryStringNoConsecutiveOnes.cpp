/* Problem: Generate binary strings with no two consecutive 1s

Given an integer N, print every string of length N made of the characters 0 and 1
such that no two 1s are next to each other. Print the strings in increasing
(lexicographic) order, one per line.

Constraints:
1 <= N <= 20

Input (input.txt):
3

Output (output.txt):
000
001
010
100
101

Explanation:
Of the 8 binary strings of length 3, the strings 011, 110 and 111 contain "11",
so they are not printed.

Hint:
Fill the string from left to right. Before placing a '1' at position i, check
the character at position i - 1. If it is already '1', skip that branch
(prune) instead of exploring it. */

#include <bits/stdc++.h>
using namespace std;

int N;
char A[21]; // N + 1 slots: the extra one holds '\0' so cout << A works

void binary(int i)
{
    // TODO: base case - all N positions are filled, so print A and return

    // TODO: choose '0' at position i and explore

    // TODO: if placing '1' would create "11", prune; otherwise choose '1' and explore
}

int main()
{
    cin >> N;
    binary(0);

    return 0;
}
