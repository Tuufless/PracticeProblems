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
#include <algorithm>

bool testExample();
bool otherTests();

std::string longestPalindrome(std::string s) {
	std::string longestPalindrome = "";

	// i = center point in palindrome
	for (int i = 0; i < s.length(); ++i) {
		int startIndex = i - 1;		// character just before the palindrome
		int endIndex = i + 1;		// character just after the palindrome

		// need to establish if the palindrome has an odd or even number of characters
		while (startIndex >= 0 && endIndex < s.length()) {
			if (s.at(startIndex) == s.at(endIndex)) {
				startIndex--;
				endIndex++;
			}
			else if (endIndex - startIndex == 2) {
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
	testExample();
	otherTests();
}


bool testExample() {
	bool test1 = (longestPalindrome("babad") == "bab" || longestPalindrome("babad") == "aba");
	bool test2 = longestPalindrome("cbbd") == "bb";

	return test1 && test2;
}

bool otherTests() {
	bool bSuccess = longestPalindrome("dyuhfggfhu") == "uhfggfhu";
	return bSuccess;
}