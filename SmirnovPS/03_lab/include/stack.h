#ifndef __STACK_H__
#define __STACK_H__

#include <algorithm>
#include <stdexcept>

const int MAX_STACK_SIZE = 1000000;

template<typename T>
class Stack {
private:
	size_t maxSize;
	int topIdx;
	T* pMem;
public:
	Stack(size_t sz = 10) : maxSize(sz) {
		if (maxSize == 0 || maxSize > MAX_STACK_SIZE)
			throw std::out_of_range("Stack");
		topIdx = -1;
		pMem = new T[maxSize]();
	}

	Stack(const Stack<T>& s) : maxSize(s.maxSize), topIdx(s.topIdx) {
		pMem = new T[maxSize];
		std::copy(s.pMem, s.pMem + s.size(), pMem);
	}

	Stack(Stack<T>&& s) noexcept : maxSize(s.maxSize), topIdx(s.topIdx), pMem(s.pMem) {
		s.maxSize = 0;
		s.topIdx = -1;
		s.pMem = nullptr;
	}

	~Stack() {
		delete[] pMem;
	}

	Stack<T>& operator= (const Stack<T>& s) {
		if (this == &s)
			return *this;
		if (maxSize != s.maxSize) {
			T* tmp = new T[s.maxSize];
			std::copy(s.pMem, s.pMem + s.size(), tmp);
			delete[] pMem;
			pMem = tmp;
			maxSize = s.maxSize;
		}
		else
			std::copy(s.pMem, s.pMem + s.size(), pMem);

		topIdx = s.topIdx;
		return *this;
	}

	Stack<T>& operator= (Stack<T>&& s) noexcept {
		if (this == &s)
			return *this;

		delete[] pMem;

		pMem = s.pMem;
		maxSize = s.maxSize;
		topIdx = s.topIdx;

		s.pMem = nullptr;
		s.maxSize = 0;
		s.topIdx = -1;

		return *this;
	}

	bool operator==(const Stack<T>& s) const noexcept {
		if (topIdx != s.topIdx)
			return false;

		for (int i = 0; i <= topIdx; i++)
			if (pMem[i] != s.pMem[i])
				return false;

		return true;
	}

	bool operator!=(const Stack<T>& s) const noexcept {
		return !(*this == s);
	}

	size_t size() const noexcept { return topIdx + 1; }
	bool isEmpty() const noexcept { return topIdx == -1; }
	bool isFull() const noexcept { return topIdx == maxSize - 1; }

	void push(const T& elem) {
		if (isFull())
			throw std::out_of_range("Cannot add element to full stack");
		pMem[++topIdx] = elem;
	}

	void pop() {
		if (isEmpty())
			throw std::out_of_range("Cannot remove element from empty stack");
		topIdx--;
	}

	T top() const {
		if (isEmpty())
			throw std::out_of_range("No elements in this stack");
		return pMem[topIdx];
	}
};

#endif