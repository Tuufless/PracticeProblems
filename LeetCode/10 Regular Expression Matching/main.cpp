/*
10. Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

Note:
s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.

Example 1:
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:
Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:
Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".

Example 5:
Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

#include <string>
#include <iostream>
#include <vector>

std::vector<std::vector<bool>> memo;

// s = text, p = pattern (see if text matches the pattern)
bool isMatch(std::string s, std::string p)
{
	memo.resize(s.length() + 1);
	for (int i = 0; i < memo.size(); ++i)
	{
		memo[i].resize(p.length() + 1);
	}

	memo[0][0] = true;

	for (size_t i = 0; i < p.length(); ++i) {
		if (p.at(i) == '*' && memo[0][i - 1]) {
			memo[0][i + 1] = true;
		}
	}

	for (size_t i = 0; i < s.length(); ++i) {
		for (size_t j = 0; j < p.length(); ++j) {
			if (p.at(j) == '.' || p.at(j) == s.at(i)) {
				memo[i + 1][j + 1] = memo[i][j];
			}
			else if (p.at(j) == '*') {
				if (p.at(j - 1) != s.at(i) && p.at(j - 1) != '.') {
					memo[i + 1][j + 1] = memo[i + 1][j - 1];
				}
				else {
					memo[i + 1][j + 1] = (memo[i + 1][j] || memo[i][j + 1] || memo[i + 1][j - 1]);
				}
			}
		}
	}

	bool result = memo[s.length()][p.length()];

	memo.clear();

	return result;
}


int main()
{
	auto check = [](std::string s, std::string p, bool output)
	{
		std::cout << "Test \"" << s << "\" against \"" << p << "\" : "
				  << (isMatch(s, p) == output ? "PASS" : "FAIL") << std::endl;
	};

	check("aa", "a", false);
	check("aa", "a*", true);
	check("ab", ".*", true);
	check("aab", "c*a*b*", true);
	check("mississippi", "mis*is*p*.", false);
	check("mississippi", "mis*is*ip*.", true);
	check("ab", ".*c", false);
	check("abby", ".*y", true);
	check("abigail", ".*g.*", true);
	check("caaaaccabcacbaac", "b*.*..*bba.*bc*a*bc", false);

	check("habitat", ".*t.*t", true);
	check("habitat", ".*..*t", true);
	check("technicality", "t.*c.*..*..*", true);
	check("technicality", "t.*..*c.*..*", true);
	check("technicality", "..*c.*..*t.*", true);
	check("technicality", "..*..*c.*t.*", true);
	return 0;
}