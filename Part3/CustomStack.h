#pragma once

#include<stack>

struct list {
	int data;
	list* next;
};

template<typename T>
class CustomStack
{
	// для реализации через массив
	int nextIndex;
	int* arr;

	// для реализации через связный список
	list* top;

	// для реализации через стек STL
	std::stack<int> s;
public:
	CustomStack(int n);

	bool is_empty();
	void push(int a);
	int pop();
	int getTop();
};

