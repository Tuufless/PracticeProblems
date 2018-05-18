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

// test case(s)
void testExample();

// function to implement:
ListNode* addTwoNumbers(ListNode* l1, ListNode* p2) {
	ListNode* pSum = nullptr;

	// implement addition here

	return pSum;
}


int main() {
	testExample();

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


void testExample() {
	// driver sample
	ListNode* p1 = createNode(3);
	p1 = addToFront(p1, createNode(4));
	p1 = addToFront(p1, createNode(2));

	ListNode* p2 = createNode(4);
	p2 = addToFront(p2, createNode(6));
	p2 = addToFront(p2, createNode(5));

	printList(p1);
	printList(p2);

	ListNode* pSum = addTwoNumbers(p1, p2);
	printList(pSum);

	// cleanup
	deleteList(p1);
	deleteList(p2);
	deleteList(pSum);
}