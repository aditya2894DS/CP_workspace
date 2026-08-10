/**************
Site: Leetcode
Name: Palindrome
Level: Easy
Date: 7/8/26
**************/

#include "palindrome.h"
#include <string>

using namespace std;

bool isPalindrome(const string& s){
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++;
        j--;
    }
    return true;
}

