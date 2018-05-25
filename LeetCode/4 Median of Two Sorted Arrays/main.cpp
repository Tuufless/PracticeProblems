/*
4. Median of Two Sorted Arrays

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity
should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

#include <vector>
#include <algorithm>

// function prototypes
bool testExample();

// function to implement:
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
	/*
	if we cut the sorted array into two halves of equal lengths, then the median
	is the average of the two numbers immediately next to the cut

	e.g: [2 3 / 5 7] -> (3 + 5) / 2 = 4
	e.g: [2 3 4 5 7] -> [2 3 (4/4) 5 7] -> (4 + 4)/2 = 4

	for convenience, let L be the number to the left of the cut, and R be the
	number to the right. We then observe the index of L and R, relative to N,
	the length of the array:

	 N	1	2	3	4	5	6	7	8	9	10	11	12
	 L	0	0	1	1	2	2	3	3	4	4	5	5
	 R	0	1	1	2	2	3	3	4	4	5	5	6

	It's not hard to conclude that L = (N - 1)/2 and R = N/2.

	Thus, the median can then be represented as
	(L + R)/2 = (A[(N - 1)/2] + A[N / 2])/2

	To prepare for the two array situation, let's add a few 'imaginary' positions
	(the #s) in between numbers, and treat numbers as positions as well
	
	array			: [# 2 # 3 # 5 # 7 #]	N = 4
	position index	:  0 1 2 3 4 5 6 7 8	N_Position = 9
	
	array			: [# 2 # 3 # 4 # 5 # 7 # ]	N = 5
	position index	:  0 1 2 3 4 5 6 7 8 9 10	N_Position = 11

	Hence, we can see that N_Position = 2N + 1, regardless of whether
	N is odd or even. Therefore, the middle cut should always be made on the Nth
	position.

	Since L = (N - 1) / 2, and R = N/2, we can infer that
	L = (CutPosition - 1)/2, R = CutPosition/2

	Now for the two-array case:
	A1 = [# 1 # 2 # 3 # 4 # 5 #]		N1 = 5,	N1_Positions = 11
	A2 = [# 1 # 1 # 1 # 1 #]			N2 = 4, N2_Positions = 9

	Similar to the one-array problem, we need to find a cut that divides the two
	arrays each into two halves such that

	"Any number in the two 'left halves'" <= "Any number in the two 'right halves'"

	We make the following observations:
	1. There are 2N1 + 2N2 + 2 positions altogether. Therefore, there must be exactly
	   N1 + N2 positions on each side of the cut, and 2 positions directly on the cut.

	2. Therefore, when we cut at position C2 = K in A2, then the cut position in A1
	   must be C1 = N1 + N2 - K. For instance, if C2 = 2, then we must have 
	   C1 = 4 + 5 - C2 = 7

	A1 = [# 1 # 2 # 3 # (4/4) # 5 #]		(cut at C1 = 7)
	A2 = [# 1 / 1 # 1 # 1 #]				(cut at C2 = 2)

	when the cuts are made, we now have two Ls and two Rs. In this case, they are
	L1 = A1[(C1 - 1)/2] = A1[3] = 4;		R1 = A1[C1/2] = A1[3] = 4
	L2 = A2[(C2 - 1)/2] = A2[0] = 1;		R2 = A2[C2/2] = A2[1] = 1

	Now, how do we decide if this cut is the cut we want? Because L1, L2 are the
	greatest numbers on the left halves, and similarly, R1, R2 are the smallest
	numbers on the right halves, we only need

	L1 <= R1 && L1 <= R2 && L2 <= R1 && L2 <= R2

	to make sure that any number in the lower half <= any number in the upper half

	L1 <= R1 and L2 <= R2 are naturally guaranteed, since A1 and A2 are both sorted.
	so we only need to check that L1 <= R2 and L2 <= R1.

	Now, we can use simple binary search to find the result:
	IF L1 > R2, then there are too many large numbers on the left half of A1, so, we
	must move C1 to the left (i.e: move C2 to the right)/
	IF L2 > R1, then there are too many large numbers of the left half of A2, so, we
	must move C2 to the left.
	OTHERWISE, this cut is the right one.

	In this case, L1 > R2, so there are too many large numbers on the left half of A1.

	After we find the cut, the median can be computed as (max(L1, L2) + min(R1, R2))/2

	Two side notes:
	Since C1 and C2 can be mutually determined from each other, we can just move one
	of them first, then calculate the other accordingly. However, it is much more practical
	to move C2 (the one on the shorter array) first.

	The reason is that, on the shorter array, the positions that are too far left or right
	are simply impossible for a legitimate cut. For instance [1],[2 3 4 5 6 7 8]. Clearly,
	the cut between 2 and 3 is impossible, because the shorter array does not have enough
	elements to balance out the [3 4 5 6 7 8] part if you make the cut this way.

	Therefore, for the longer array to be used as the basis for the first cut, a range
	check must be performed. It would be just easier to do it on the shorter array, which
	requires no checks whatsoever. Also, moving only on the shorter array gives a run-time
	complexity of O(log(min(N1, N2)).

	The only edge case is when a cut falls on the 0th (first) or the 2Nth (last) position.
	For instance, if C2 = 2N2, then R2 = A2[2N2/2] = A2[N2], which exceeds the boundary of
	the array. To solve this problem, we can imagine that both A1 and A2 actually have two
	extra elements, INT_MIN at A[-1] and INT_MAX A[N]. These additions don't change the result, but
	make the implementation easier: if any L falls out of the left boundary of the array, then
	L = INT_MIN. Similarly, if any R falls out of the right boundary of the array, then R = INT_MAX.
	*/

	int N1 = nums1.size();
	int N2 = nums2.size();

	if (N1 < N2) {
		return findMedianSortedArrays(nums2, nums1);
	}

	int low = 0;
	int high = 2 * N2;

	while (low < high) {
		int mid2 = (low + high) / 2;	// try cut2
		int mid1 = N1 + N2 - mid2;		// calculate cut1 from cut2

		double L1 = (mid1 == 0) ? INT_MIN : nums1[(mid1 - 1) / 2];
		double L2 = (mid2 == 0) ? INT_MIN : nums2[(mid2 - 1) / 2];
		double R1 = (mid1 == 2 * N1) ? INT_MAX : nums1[mid1 / 2];
		double R2 = (mid2 == 2 * N2) ? INT_MAX : nums2[mid2 / 2];

		if (L1 > R2) {
			low = mid2 + 1;
		}
		else if (L2 > R1) {
			high = mid2 - 1;
		}
		else {
			return (std::max(L1, L2) + std::min(R1, R2)) / 2.0;
		}
	}

	return 0.0;
}


int main()
{
	testExample();
	return 0;
}

bool testExample() {
	std::vector<int> nums1 = { 1, 3 };
	std::vector<int> nums2 = { 2 };

	double median = findMedianSortedArrays(nums1, nums2);

	std::vector<int> nums3 = { 1, 2 };
	std::vector<int> nums4 = { 3, 4 };

	double median2 = findMedianSortedArrays(nums3, nums4);

	return median == 2.0 && median2 == 2.5;
}