/*
5. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the max length of s is 1000

Example 1:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:
Input: "cbbd"
Output: "bb"
*/

#include <string>

bool testExample();

std::string longestPalindrome(std::string s) {
	return "";
}


int main()
{
	testExample();
}


bool testExample() {
	bool test1 = (longestPalindrome("babad") == "bab" || longestPalindrome("babad") == "aba");
	bool test2 = longestPalindrome("cbbd") == "bb";

	return test1 && test2;
}