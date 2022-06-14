#include <iostream>
#include <stack>
#include "CustomStack.h"

using namespace std;

/*
	Для разных шаблонных типов разные реализации методов
*/

CustomStack<list>::CustomStack(int n) {
	top = nullptr;
	nextIndex = 0;
	arr = nullptr;
	top = nullptr;
}
CustomStack<int*>::CustomStack(int n) {
	top = nullptr;
	nextIndex = 0;
	arr = new int[n];
	top = nullptr;
}
CustomStack<stack<int>>::CustomStack(int n) {
	top = nullptr;
	nextIndex = 0;
	arr = nullptr;
	top = nullptr;
}

bool CustomStack<list>::is_empty() {
	return top == nullptr;
}
bool CustomStack<int*>::is_empty() {
	return nextIndex == 0;
}
bool CustomStack<stack<int>>::is_empty() {
	return s.empty();
}


void CustomStack<int*>::push(int a) {
	arr[nextIndex++] = a;
}
void CustomStack<list>::push(int a) {
	list* temp = new list{ a, top };

	top = temp;
}
void CustomStack<stack<int>>::push(int a) {
	s.push(a);
}

int CustomStack<list>::pop() {
	if (is_empty()) {
		cout << "stack underflow" << endl;

		return 0;
	}

	int a = top->data;
	list* temp = top->next;

	delete top;

	top = temp;

	return a;
}
int CustomStack<int*>::pop() {
	if (is_empty()) {
		cout << "stack underflow" << endl;

		return 0;
	}

	int a = arr[--nextIndex];

	return a;
}
int CustomStack<stack<int>>::pop() {
	if (is_empty()) {
		cout << "stack underflow" << endl;

		return 0;
	}

	int a = s.top();
	s.pop();

	return a;
}

int CustomStack<list>::getTop() {
	return top->data;
}
int CustomStack<int*>::getTop() {
	return arr[nextIndex - 1];
}
int CustomStack<stack<int>>::getTop() {
	return s.top();
}