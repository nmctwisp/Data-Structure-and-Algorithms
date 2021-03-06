#pragma once
#include <memory>
#include <optional>

template <typename T>
class DoublyLinkedList {

	class Node;

private:
	size_t m_size{ 0 };
	std::shared_ptr<Node> m_head{ nullptr };
	std::shared_ptr<Node> m_tail{ nullptr };
public:
	DoublyLinkedList<T>() {};
	DoublyLinkedList<T>(T arr[], int size);

	class Iterator;
	class Reverse_Iterator;

	Iterator begin();
	Iterator end();

	Reverse_Iterator rbegin();
	Reverse_Iterator rend();

	void append(T data);
	void insert(int index, T data);
	T pop(std::optional<size_t> index = std::nullopt);
	void remove(T data);
	void remove_all(T data);
	T index(size_t index);
	int count(T data);
	void clear();
	size_t size();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T arr[], int size) {
	for (auto idx = 0; idx < size; ++idx)
		append(arr[idx]);
}

template <typename T>
class DoublyLinkedList<T>::Node {
	friend class DoublyLinkedList;
private:
	T m_data;
	std::shared_ptr<Node> prev{ nullptr };
	std::shared_ptr<Node> next{ nullptr };
public:
	Node(T value) : m_data(value) {};
};

template <typename T>
class DoublyLinkedList<T>::Iterator {
public:
	std::shared_ptr<DoublyLinkedList<T>::Node> m_current{ nullptr };
	Iterator(const std::shared_ptr<DoublyLinkedList<T>::Node> node) noexcept : m_current(node) {};

	DoublyLinkedList<T>::Iterator& operator=(std::shared_ptr<DoublyLinkedList<T>::Node> node) {
		m_current = node;
		return *this;
	}

	// prefix operator
	DoublyLinkedList<T>::Iterator& operator++() {
		if (m_current)
			m_current = m_current->m_next;

		return *this;
	};

	// postfix operator
	DoublyLinkedList<T>::Iterator operator++(int) {

		Iterator iterator = *this;
		++* this;

		return iterator;
	}

	bool operator!=(const DoublyLinkedList<T>::Iterator& iterator) {
		return m_current != iterator.m_current;
	}

	T operator*() {
		return m_current->m_data;
	}
};

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {

	return Iterator(m_head);
}

template <typename T>
typename DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {

	return Iterator(m_tail->m_next);
}

template <typename T>
class DoublyLinkedList<T>::Reverse_Iterator {
public:
	std::shared_ptr<DoublyLinkedList<T>::Node> m_current{ nullptr };
	Reverse_Iterator(const std::shared_ptr<DoublyLinkedList<T>::Node> node) noexcept :
		m_current(node) {};

	
	DoublyLinkedList<T>::Reverse_Iterator& operator=(std::shared_ptr<DoublyLinkedList<T>::Node> node) {
		
		m_current = node;
		
		return *this;
	}

	DoublyLinkedList<T>::Reverse_Iterator& operator++() {
		
		if (m_current)
			m_current = m_current->prev;

		return *this;
	}

	DoublyLinkedList<T>::Reverse_Iterator& operator++(int) {
		
		Reverse_Iterator riterator = *this;
		++* this;

		return riterator;
	}

	bool operator!=(const DoublyLinkedList<T>::Reverse_Iterator& riterator) {

		return m_current != riterator.m_current;

	}

	T operator*() {
		
		return m_current->m_data;
	}
};

template <typename T>
typename DoublyLinkedList<T>::Reverse_Iterator DoublyLinkedList<T>::rbegin() {

	return Reverse_Iterator(m_tail);
}

template <typename T>
typename DoublyLinkedList<T>::Reverse_Iterator DoublyLinkedList<T>::rend() {

	return Reverse_Iterator(m_head->prev);
}

template <typename T>
void DoublyLinkedList<T>::append(T data) {
	std::shared_ptr<Node> node{ std::make_shared<Node>(data) };

	if (!m_head) {
		m_head = node;
		m_tail = node;
	}
	else {
		node->prev = m_tail;
		m_tail->m_next = node;
		m_tail = node;
	}

	++(m_size);
};

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
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
			current = current->m_next;
			++position;
		}
	}

	if (prev) {
		node->m_next = current;
		node->prev = prev;
		prev->m_next = node;
		current->prev = node;
		current = node;
	}
	else {
		current->prev = node;
		node->m_next = current;
		m_head = node;
	}

	++m_size;
}

template <typename T>
T DoublyLinkedList<T>::pop(std::optional<size_t> index) {
	auto current = m_head;
	std::shared_ptr<Node> prev{ nullptr };
	int position{ 0 };

	if (!current) {
		return current->m_data;
	}

	if (index == 0) {
		m_head = current->m_next;
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
				current = current->m_next;
				position += 1;
			}
		}

		prev->m_next = current->m_next;

		if (prev->m_next)
			prev->m_next->prev = prev;
		else
			m_tail = prev;
	}

	--m_size;

	return current->m_data;

}

template <typename T>
void DoublyLinkedList<T>::remove(T data) {
	auto current = m_head;
	auto prev = m_head->prev;

	while (current) {
		if (current->m_data == data) {

			if (current == m_head) {
				current->m_next->prev = prev;
				m_head = current->m_next;
			}
			else if (current == m_tail) {
				prev->m_next = current->m_next;
				m_tail = prev;
			}
			else {
				current->m_next->prev = prev;
				prev->m_next = current->m_next;
			}

			--m_size;
			return;
		}

		prev = current;
		current = current->m_next;
	}
}

template <typename T>
void DoublyLinkedList<T>::remove_all(T data) {
	auto current = m_head;
	auto prev = m_head->prev;

	while (current) {
		if (current->m_data == data) {

			if (current == m_head) {
				current->m_next->prev = prev;
				m_head = current->m_next;
			}
			else if (current == m_tail) {
				prev->m_next = current->m_next;
				m_tail = prev;
			}
			else {
				current->m_next->prev = prev;
				prev->m_next = current->m_next;
			}

			--m_size;
		}

		prev = current;
		current = current->m_next;
	}
}

template <typename T>
T DoublyLinkedList<T>::index(size_t index) {
	if (index > m_size - 1)
		throw std::exception("Error");

	int position{ 0 };
	auto current = m_head;

	while (current) {
		if (position == index)
			break;

		current = current->m_next;
		++position;
	}

	return current->m_data;
};

template <typename T>
int DoublyLinkedList<T>::count(T data) {
	int cnt{ 0 };
	auto current = m_head;

	while (current) {
		if (current->m_data == data)
			++cnt;
		current = current->m_next;
	}

	return cnt;

}

template <typename T>
void DoublyLinkedList<T>::clear() {
	m_head.reset();
	m_tail.reset();
	m_size = 0;
}

template <typename T>
size_t DoublyLinkedList<T>::size() {

	return m_size;
}
