/*
3. Longest Substring Without Repeats

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which is length 3.
Given "bbbbb", the answer is "b", which is length 1.
Given "pwwkew", the answer is "wke", which is length 3. Note that the answer must be
a substring- "pwke" is a subsequence, and not a substring.
*/

#include <iostream>
#include <string>

// test cases(s)
bool testExample();

// function to implement:
int lengthOfLongestSubstring(std::string s) {
	return 0;
}

int main() {
	std::cout << "testExample() : " << (testExample() ? "PASS" : "FAIL") << std::endl;

	return 0;
}


bool testExample() {
	int test1 = lengthOfLongestSubstring("abcabcbb");
	int test2 = lengthOfLongestSubstring("bbbbb");
	int test3 = lengthOfLongestSubstring("pwwkew");

	return (test1 == 3) && (test2 == 1) && (test3 == 3);
}