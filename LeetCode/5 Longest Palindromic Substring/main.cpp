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

#include <iostream>
#include <string>
#include <algorithm>

static const int NUM_TESTS = 4;
std::string testInput[NUM_TESTS] = { "babad", "cbbd", "bb", "aaaa" };
std::string testOutput[NUM_TESTS] = { "bab", "bb", "bb", "aaaa" };

std::string longestPalindrome(std::string s) {
	std::string longestPalindrome = "";

	// i = center point in palindrome
	for (int i = 0; i < s.length(); ++i) {
		int startIndex = i - 1;		// character just before the palindrome
		int endIndex = i + 1;		// character just after the palindrome

		while (endIndex < s.length() && s.at(i) == s.at(endIndex)) {
			++endIndex;
		}
		
		while (startIndex >= 0 && endIndex < s.length()) {
			if (s.at(startIndex) == s.at(endIndex)) {
				startIndex--;
				endIndex++;
			}
			else {
				break;
			}
		}

		if (endIndex - startIndex - 1 > longestPalindrome.length()) {
			longestPalindrome = s.substr(startIndex + 1, endIndex - startIndex - 1);
		}
	}

	return longestPalindrome;
}


int main()
{
	for (int i = 0; i < NUM_TESTS; ++i) {
		std::string s = testInput[i];
		std::string output = longestPalindrome(s);
		std::cout << "longestPalindrome(" << s << ") = " << output << ". ";

		if (output == testOutput[i]) {
			std::cout << "PASS" << std::endl;
		}
		else {
			std::cout << "FAIL (Expected output = " << testOutput[i] << ")" << std::endl;
		}
	}

	return 0;
}

