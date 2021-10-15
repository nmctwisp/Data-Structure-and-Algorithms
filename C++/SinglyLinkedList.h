#pragma once
#include <memory>
#include <optional>

template <typename T>
class SinglyLinkedList {

	class Node {
		friend class SinglyLinkedList;
	private:
		T m_data;
		std::shared_ptr<Node> next{ nullptr };
	public:
		Node(T value) : m_data(value) {};
	};

private:
	size_t m_size{ 0 };
	std::shared_ptr<Node> m_head{ nullptr };
	std::shared_ptr<Node> m_tail{ nullptr };
public:
	SinglyLinkedList() {};
	SinglyLinkedList(T arr[], int size) {
		for (auto idx = 0; idx < size; ++idx)
			append(arr[idx]);
	}

	void append(T data) {
		std::shared_ptr<Node> node{ std::make_shared<Node>(data) };
		
		if (!m_head) {
			m_head = node;
			m_tail = node;
		}
		else {
			m_tail->next = node;
			m_tail = node;
		}

		++(m_size);
	};
	
	T pop(std::optional<int> index = std::nullopt) {
		auto current = m_head;
		std::shared_ptr<Node> prev{ nullptr };
		int position{ 0 };
		
		if (!current) {
			return current->m_data;
		}

		if (index == 0) {
			m_head = current->next;
		}
		else {
			if (index == std::nullopt) {
				index = m_size - 1;
			}

			while (true) {
				if (index == position)
					break;
				else {
					prev = current;
					current = current->next;
					position += 1;
				}
			}

			prev->next = current->next;
			m_tail = prev;
		}

		--m_size;

		return current->m_data;
		
	}
	
	size_t size() { return m_size; }
	
	void clear() {
		m_head.reset();
		m_tail.reset();
		m_size = 0;
	}
	
	int count(T data) {
		int cnt{ 0 };
		auto current = m_head;
		
		while (current) {
			if (current->m_data == data)
				++cnt;
			current = current->next;
		}
		
		return cnt;

	}
	
	T index(size_t index) {
		if (index > m_size - 1)
			throw std::exception("Error");

		int position{ 0 };
		auto current = m_head;
		
		while (current) {
			if (position == index)
				break;
			
			current = current->next;
			++position;
		}

		return current->m_data;
	};
	
	void insert(int index, T data) {
		auto node{ std::make_shared<Node>(data) };
		auto current = m_head;
		std::shared_ptr<Node> prev{ nullptr };
		
		int position{ 0 };

		while (current) {
			if (position == index) {
				break;
			}
			else {
				prev = current;
				current = current->next;
				++position;
			}
		}

		if (prev) {
			node->next = current;
			prev->next = node;
			current = node;
		}
		else {
			node->next = current;
			m_head = node;
		}

		++m_size;
	}


};