#ifndef STACK_H
#define STACK_H

#include <vector>
#include <cstddef>
#include <stdexcept>

template <typename T, class Container = std::vector<T>>
class myStack
{
private:
	Container data;

public:
	myStack() = default;

	void push(const T& value)
	{
		data.push_back(value);
	}

	void pop()
	{
		if (data.empty())
			throw std::out_of_range("Stack::pop: stack is empty");
		data.pop_back();
	}

	T& top()
	{
		if (data.empty())
			throw std::out_of_range("Stack::top: stack is empty");
		return data.back();
	}

	const T& top() const //просмотр верхнего элемента 
	{
		if (data.empty())
			throw std::out_of_range("Stack::top is empty");
		return data.back();
	}

	bool empty() const
	{
		return data.empty();
	}

	std::size_t size() const
	{
		return data.size();
	}

};

#endif // STACK_H
