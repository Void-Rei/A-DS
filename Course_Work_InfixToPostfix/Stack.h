#ifndef CUSTOM_STACK_CLASS_H
#define CUSTOM_STACK_CLASS_H

#include "Node.h"

class Stack
{
public:

	Stack();
	~Stack();

	void push(Node*);
	Node* pop();
	bool isEmpty();
	Node* getTop();

private:

	class StackNode
	{
	public:

		StackNode(Node* element, StackNode* next = nullptr) {
			this->element = element;
			this->next = next;
		};
		~StackNode() {};

		Node* element;
		StackNode* next;
	};

	StackNode* top;
};

#endif
