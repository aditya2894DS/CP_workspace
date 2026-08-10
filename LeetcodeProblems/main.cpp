#include <iostream>
#include "palindrome.h"

using namespace std;

int main()
{
    std::string word = "levelaaswws";
    std::cout << (isPalindrome(word) ? "Yes" : "No") << std::endl;
    return 0;
}
