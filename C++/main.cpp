#include "SinglyLinkedList.h"

int main() {
	int arr[7]{ 1,2,3,4,5, 4, 7 };
	SinglyLinkedList<int> t{ arr, 7 };
	auto p = t.pop();
	auto y = t.count(4);
	auto z = t.index(5);
	t.insert(2, 10);
	int x = 1;
	return 0;
}