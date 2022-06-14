#pragma once

#include<stack>

struct list {
	int data;
	list* next;
};

template<typename T>
class CustomStack
{
	// ��� ���������� ����� ������
	int nextIndex;
	int* arr;

	// ��� ���������� ����� ������� ������
	list* top;

	// ��� ���������� ����� ���� STL
	std::stack<int> s;
public:
	CustomStack(int n);

	bool is_empty();
	void push(int a);
	int pop();
	int getTop();
};

