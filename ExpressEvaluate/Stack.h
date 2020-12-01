#pragma once

template<class Type>
class Stack
{
public:
	Stack(int sz = DEFAULT_SIZE)
	{
		capacity = sz > DEFAULT_SIZE ? sz : DEFAULT_SIZE;
		base = new Type[capacity];
		top = 0;
	}
	~Stack()
	{
		delete []base;
		base = NULL;
		capacity = top = 0;
	}
public:
	bool IsFull()const;
	bool IsEmpty()const;

	void Push(const Type &x);
	void Pop();
	Type GetTop()const;

private:
	enum{DEFAULT_SIZE = 100};
	Type *base;
	size_t capacity;
	size_t top;
};
												 
template<class Type>
bool Stack<Type>::IsFull() const
{
	return top == capacity;
}
																				 
template<class Type>
bool Stack<Type>::IsEmpty() const
{
	return top == 0;
}

template<class Type>
void Stack<Type>::Push(const Type &x)
{
	base[top] = x;
	++top;
}											  

template<class Type>										 
void Stack<Type>::Pop()
{
	--top;
}
template<class Type>
Type Stack<Type>::GetTop() const
{
	return base[top - 1];
}								 