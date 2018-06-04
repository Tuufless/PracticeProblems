/*
6. Zigzag conversion

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I
*/

#include <string>

bool testExample();

std::string convert(const std::string& s, int numRows) {
	std::string result;

	int n = numRows;

	for (size_t r = 0; r < numRows; ++r) {
		size_t i = r;

		if (i < s.length()) {
			result.push_back(s.at(i));
		}

		while (i < s.length()) {
			int diff = 2 * (n - r - 1);
			if (diff > 0) {
				i += diff;
				if (i < s.length()) {
					result.push_back(s.at(i));
				}
				else {
					break;
				}
			}

			diff = 2 * r;
			if (diff > 0) {
				i += diff;
				if (i < s.length()) {
					result.push_back(s.at(i));
				}
				else {
					break;
				}
			}
		}
	}

	return result;
}

int main() {
	testExample();
	return 0;
}

bool testExample() {
	bool b1 = convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR";
	bool b2 = convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI";

	return b1 && b2;
}