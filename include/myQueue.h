#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <deque>
#include <cstddef>
#include <stdexcept>

template <typename T, class Container = std::deque<T>> 
class myQueue
{
private:
	Container data;

public:
	myQueue() = default;

	void push(const T& value) 
	{ 
		data.push_back(value); 
	}

	void pop() 
	{
		if (data.empty())
			throw std::out_of_range("Queue::pop: queue is empty");
		data.pop_front();
	}

	T& back()
	{
		if (data.empty())
			throw std::out_of_range("Queue::back: queue is empty");
		return data.back();
	}

	const T& back() const 
	{
		if (data.empty())
			throw std::out_of_range("Queue::back: queue is empty");
		return data.back();
	}

	T& front()
	{
		if (data.empty())
			throw std::out_of_range("Queue::front: queue is empty");
		return data.front();
	}

	const T& front() const
	{
		if (data.empty())
			throw std::out_of_range("Queue::front: queue is empty");
		return data.front();
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

#endif // MYQUEUE_H
