/*
2. Add Two Numbers

You are given two non - empty linked lists representing two non - negative integers. 
The digits are stored in reverse order and each of their nodes contain a single digit.

Add the two numbers, and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:
	Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output : 7 -> 0 -> 8
	Explanation : 342 + 465 = 807
*/

#include <iostream>

// Definition for singly-linked list
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};


// function prototypes
ListNode* createNode(int x);
void deleteNode(ListNode* pNode);
void deleteList(ListNode* pHead);
void printList(ListNode* pHead);
ListNode* addToFront(ListNode* pHead, ListNode* pNode);
bool isEqual(ListNode* l1, ListNode* l2);

// test case(s)
bool testExample();
bool testUnequalLength();

// function to implement:
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* pSum = nullptr;	// return this
	ListNode** ppNode = &pSum;

	int carry = 0;
	while (l1 != nullptr || l2 != nullptr || carry > 0) {
		int sum = (l1 != nullptr) ? l1->val : 0;
		sum += (l2 != nullptr) ? l2->val : 0;
		sum += carry;

		if (sum > 9) {
			sum -= 10;
			carry = 1;
		}
		else {
			carry = 0;
		}

		*ppNode = new ListNode(sum);
		ppNode = &(*ppNode)->next;

		if (l1 != nullptr) {
			l1 = l1->next;
		}

		if (l2 != nullptr) {
			l2 = l2->next;
		}
	}

	return pSum;
}


int main() {
	std::cout << "testExample() : " << (testExample() ? "PASS" : "FAIL") << std::endl;
	std::cout << "testUnequalLength() : " << (testUnequalLength() ? "PASS" : "FAIL") << std::endl;

	return 0;
}


ListNode* createNode(int x) {
	return new ListNode(x);
}


void deleteNode(ListNode* pNode) {
	delete pNode;
	pNode = nullptr;
}


void deleteList(ListNode* pHead) {
	ListNode* pCurr = pHead;
	while (pCurr != nullptr) {
		pHead = pHead->next;
		deleteNode(pCurr);
		pCurr = pHead;
	}
}


void printList(ListNode* pHead) {
	while (pHead != nullptr) {
		std::cout << pHead->val << " -> ";
		pHead = pHead->next;
	}

	std::cout << "nullptr" << std::endl;
}


ListNode* addToFront(ListNode* pHead, ListNode* pNode) {
	pNode->next = pHead;
	return pNode;
}


bool isEqual(ListNode* l1, ListNode* l2) {
	while (l1 != nullptr && l2 != nullptr) {
		if (l1->val != l2->val) {
			return false;
		}

		l1 = l1->next;
		l2 = l2->next;
	}

	// we've reached the end of at least one of the lists
	// if the other list hasn't ended, then the lists aren't equal
	return (l1 == nullptr && l2 == nullptr);
}


// driver sample
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output : 7 -> 0 -> 8
// Explanation : 342 + 465 = 807
bool testExample() {
	// 342
	ListNode* p1 = createNode(3);
	p1 = addToFront(p1, createNode(4));
	p1 = addToFront(p1, createNode(2));

	// 465
	ListNode* p2 = createNode(4);
	p2 = addToFront(p2, createNode(6));
	p2 = addToFront(p2, createNode(5));

	// 342 + 465 = 807
	ListNode* pAns = createNode(8);
	pAns = addToFront(pAns, createNode(0));
	pAns = addToFront(pAns, createNode(7));

	ListNode* pSum = addTwoNumbers(p1, p2);

	bool bPass = isEqual(pAns, pSum);

	// cleanup
	deleteList(p1);
	deleteList(p2);
	deleteList(pSum);

	return bPass;
}


// Input: 
// Output: 
// Explanation : 7324 + 94273 = 101597
bool testUnequalLength() {
	// 7324
	ListNode* p1 = createNode(7);
	p1 = addToFront(p1, createNode(3));
	p1 = addToFront(p1, createNode(2));
	p1 = addToFront(p1, createNode(4));

	// 94273
	ListNode* p2 = createNode(9);
	p2 = addToFront(p2, createNode(4));
	p2 = addToFront(p2, createNode(2));
	p2 = addToFront(p2, createNode(7));
	p2 = addToFront(p2, createNode(3));

	// 7324 + 94273 = 101597
	ListNode* pAns = createNode(1);
	pAns = addToFront(pAns, createNode(0));
	pAns = addToFront(pAns, createNode(1));
	pAns = addToFront(pAns, createNode(5));
	pAns = addToFront(pAns, createNode(9));
	pAns = addToFront(pAns, createNode(7));

	ListNode* pSum1 = addTwoNumbers(p1, p2);
	ListNode* pSum2 = addTwoNumbers(p2, p1);

	bool bPass = isEqual(pAns, pSum1) && isEqual(pAns, pSum2);

	// cleanup
	deleteList(p1);
	deleteList(p2);
	deleteList(pSum1);
	deleteList(pSum2);

	return bPass;
}