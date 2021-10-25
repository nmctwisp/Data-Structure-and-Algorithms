#include "catch.hpp"
#include "SinglyLinkedList.h"
#include <memory>
#include <optional>

TEST_CASE("SinglyLinkedList") {
	const size_t arr_size{ 7 };
	int arr[arr_size]{ 1,2,3,4,5,4,7 };
	SinglyLinkedList<int> list{arr, arr_size};
	
	SECTION("Append") {
		int val = 2;
		list.append(val);
		
		REQUIRE(list.size() == 8);
		REQUIRE(list.back()->data() == val);

		auto current{ list.front() };
		std::shared_ptr<SinglyLinkedList<int>::Node> prev;
		while (current != list.back()) {
			prev = current;
			current = current->next();

		}

		REQUIRE(prev->next() == current);
		REQUIRE(current == list.back());
	}

	SECTION("Pop Head") {
		auto old_head_next{ list.front()->next() };

		list.pop(0);

		REQUIRE(list.size() == 6);
		REQUIRE(old_head_next == list.front());

	}

	SECTION("Pop Tail") {
		auto current{ list.front() };
		std::shared_ptr<SinglyLinkedList<int>::Node> prev;
		while (current != list.back()) {
			prev = current;
			current = current->next();
		}

		list.pop();
		REQUIRE(list.size() == 6);
		REQUIRE(prev == list.back());

		current = list.front();
		while (current != list.back()) {
			prev = current;
			current = current->next();
		}

		REQUIRE(prev->next() == list.back());


	}
	

}