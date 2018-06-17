/*
Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. 
Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as 
possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no 
effect on the behavior of this function. If the first sequence of non-whitespace characters in str is not a valid integral 
number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion 
is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

Only the space character ' ' is considered as whitespace character.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: 
[−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) 
is returned.

Example 1:
Input: "42"
Output: 42

Example 2:
Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
Then take as many numerical digits as possible, which gets 42.

Example 3:
Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

Example 4:
Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical
digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:
Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
Thefore INT_MIN (−231) is returned.
*/

#include <iostream>
#include <limits.h>	// INT_MAX(), INT_MIN()
#include <string>

bool test1();
bool test2();
bool test3();
bool test4();
bool test5();
bool test6();

int myAtoi(std::string str) {
	// remove whitespace
	size_t stringStart = str.find_first_not_of(' ');
	if (stringStart == std::string::npos) {
		return 0;
	}

	str = str.substr(stringStart);
	bool bPositive = true;
	if (str[0] == '-') {
		bPositive = false;
		str = str.substr(1);
	}
	else if (str[0] == '+') {
		str = str.substr(1);
	}

	int val = 0;
	for (std::string::iterator iter = str.begin(); iter != str.end(); ++iter) {
		if (!isdigit(*iter)) {
			break;
		}

		if (bPositive && val > INT_MAX / 10) {
			return INT_MAX;
		}
		else if (!bPositive && -val < INT_MIN / 10) {
			return INT_MIN;
		}
		
		val *= 10;

		int digit = *iter - '0';
		if (bPositive && INT_MAX - val < digit) {
			return INT_MAX;
		}
		else if (!bPositive && INT_MIN + val > -digit) {
			return INT_MIN;
		}

		val += digit;
	}

	return (bPositive ? 1 : -1) * val;
}

int main() {
	std::cout << "test1() : " << (test1() ? "PASS" : "FAIL") << std::endl;
	std::cout << "test2() : " << (test2() ? "PASS" : "FAIL") << std::endl;
	std::cout << "test3() : " << (test3() ? "PASS" : "FAIL") << std::endl;
	std::cout << "test4() : " << (test4() ? "PASS" : "FAIL") << std::endl;
	std::cout << "test5() : " << (test5() ? "PASS" : "FAIL") << std::endl;
	std::cout << "test6() : " << (test6() ? "PASS" : "FAIL") << std::endl;
	return 0;
}

bool test1() {
	return myAtoi("42") == 42;
}

bool test2() {
	return myAtoi("   -42") == -42;
}

bool test3() {
	return myAtoi("4193 with words") == 4193;
}

bool test4() {
	return myAtoi("words and 987") == 0;
}

bool test5() {
	return myAtoi("-91283472332") == INT_MIN;
}

bool test6() {
	return myAtoi("2147483648") == INT_MAX;
}