#include "Stack.h"

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	while (!isEmpty()) {
		pop();
	}
}

void Stack::push(Node* new_elem)
{
	top = new StackNode(new_elem, top);
}

Node* Stack::pop()
{
	Node* temp = top->element;
	top = top->next;
	return temp;
}

bool Stack::isEmpty()
{
	return (top == nullptr);
}

Node* Stack::getTop()
{
	return top->element;
}
