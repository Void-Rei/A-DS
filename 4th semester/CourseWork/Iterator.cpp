#include "Tree.h"
#include "node.h"
#include <stdexcept>

using namespace std;

Tree::Stack::Stack() 
{
	top = nullptr;
}

Tree::Stack::~Stack() 
{
	while (!isEmpty()) {
		pop();
	}
}

void Tree::Stack::push(Node* new_elem) 
{
	top = new stack_Node(new_elem, top);
}

Node* Tree::Stack::pop() 
{
	Node* temp = top->element;
	top = top->next;
	return temp;
}

bool Tree::Stack::isEmpty() 
{
	return (top == nullptr);
}

Node* Tree::Stack::getTop() 
{
	return top->element;
}

Tree::dft_Iterator* Tree::create_dft_Iterator()
{
	return new dft_Iterator(s);
}

Tree::dft_Iterator::dft_Iterator(Node* start) 
{
	stack = new Stack();
	stack->push(start);
}

bool Tree::dft_Iterator::has_next() 
{
	return !(stack->isEmpty());
}

Node* Tree::dft_Iterator::next() 
{
	Node* current;
	current = stack->pop();
	
	if (current->left != nullptr) 
	{
		stack->push(current->left);
	}
	
	if (current->right != nullptr) 
	{
		stack->push(current->right);
	}

	return current;
}