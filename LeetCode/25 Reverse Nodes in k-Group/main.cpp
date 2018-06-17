/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

Example:
Given this linked list: 1->2->3->4->5
For k = 2, you should return: 2->1->4->3->5
For k = 3, you should return: 3->2->1->4->5
Note:
Only constant extra memory is allowed.
You may not alter the values in the list's nodes, only nodes itself may be changed.*/

#include <iostream>
#include <vector>

// Definition for singly-linked list
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* createNode(int x);
void deleteNode(ListNode* pNode);
void deleteList(ListNode* pHead);
void printList(ListNode* pHead);
bool isEqual(ListNode* l1, ListNode* l2);

void flip(ListNode* pCurr, ListNode* pNext, ListNode* endNode) {
	if (pCurr != nullptr && pNext != nullptr && pNext != endNode) {
		flip(pNext, pNext->next, endNode);
		pNext->next = pCurr;
	}
}

// reverses the interval [head, tail]
ListNode* reverseGroup(ListNode* head, ListNode* tail) {
	if (head != tail) {
		flip(head, head->next, tail->next);
		head->next = nullptr;
	}

	return head;
}

ListNode* reverseKGroup(ListNode* head, int k) {
	ListNode* pStartNextGroup = head;
	ListNode* pEndPrevGroup = nullptr;
	ListNode* pNewHead = nullptr;

	while (pStartNextGroup != nullptr) {
		ListNode* pStartGroup = pStartNextGroup;
		ListNode* pEndGroup = pStartGroup;
		int i = 0;
		for (; i < k - 1; ++i) {
			if (pEndGroup == nullptr) {
				break;
			}

			pEndGroup = pEndGroup->next;
		}

		pStartNextGroup = (pEndGroup != nullptr) ? pEndGroup->next : nullptr;
		
		if (pNewHead == nullptr) {
			pNewHead = (pEndGroup != nullptr) ? pEndGroup : head;
		}

		if (i == k - 1 && pEndGroup != nullptr) {
			if (pEndPrevGroup != nullptr) {
				pEndPrevGroup->next = pEndGroup;
			}

			pEndPrevGroup = reverseGroup(pStartGroup, pEndGroup);
		}
		else if (pEndPrevGroup != nullptr) {
			pEndPrevGroup->next = pStartGroup;
		}
	}
	
	return pNewHead;
}

int main() {
	static const int num_nodes = 10;
	std::vector<ListNode*> pNodes;

	for (int i = 0; i < num_nodes; ++i) {
		ListNode* pNewNode = new ListNode(i);
		pNodes.push_back(pNewNode);

		if (i > 0) {
			pNodes[i - 1]->next = pNewNode;
		}
	}

	printList(pNodes[0]);

	ListNode* pHead = reverseKGroup(pNodes[0], 10);

	printList(pHead);

	for (int i = 0; i < num_nodes; ++i) {
		delete pNodes[i];
		pNodes[i] = nullptr;
	}

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

