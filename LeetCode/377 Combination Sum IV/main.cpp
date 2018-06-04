/*
Given an integer array with all positive numbers and no duplicates, find the number of 
possible combinations that add up to a positive integer target.

Example:
nums = [1, 2, 3]
target = 4

The possible combination ways are :
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.*/

#include <vector>
#include <iostream>

bool testExample();

int combinationSum4(std::vector<int>& nums, int target) {
	std::vector<int> dp(target + 1);

	// initialize- for each number in nums, there is at least
	// one combination that adds to that number (itself)
	for (int& num : nums) {
		if (num <= target) {
			dp[num] = 1;
		}
	}

	// f(target) = f(target - nums[0]) + f(target - nums[1]) + ... + f(target - nums[-1])
	for (int i = 0; i <= target; ++i) {
		for (int& num : nums) {
			if (num <= i) {
				dp[i] += dp[i - num];
			}
		}
	}

	return dp[target];
}

int main() {
	testExample();
	return 0;
}


bool testExample() {
	std::vector<int> nums = { 1, 2, 3 };
	int target = 4;
	return combinationSum4(nums, target) == 7;
}