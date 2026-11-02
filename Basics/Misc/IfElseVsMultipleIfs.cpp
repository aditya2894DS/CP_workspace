#include <iostream>
using namespace std;

char ifElseLadder(int marks) {
    char grade;
    if (marks >= 90)      grade = 'A';
    else if (marks >= 70) grade = 'B';
    else if (marks >= 50) grade = 'C';
    else                  grade = 'F';
    return grade;
}

char multipleIfs(int marks) {
    char grade = 'F';
    if (marks >= 90) grade = 'A';
    if (marks >= 70) grade = 'B';   // also runs for 95, overwrites 'A'
    if (marks >= 50) grade = 'C';   // also runs for 95 and 78, overwrites again
    return grade;
}

int main() {
    for (int m : {95, 78, 55, 30})
        cout << m << " -> ladder: " << ifElseLadder(m)
             << ", multiple ifs: " << multipleIfs(m) << endl;
}

// The ladder stops at the first match. With multiple ifs, every matching condition runs, so the last one to match wins.