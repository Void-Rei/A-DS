#include "Tree.h"
#include "node.h"

#include <string>
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

Tree::dft_Iterator* Tree::create_dft_iterator()
{
	return new dft_Iterator(root);
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

char Tree::dft_Iterator::next() 
{
	Node* current;
	current = stack->pop();
	
	if (current->left != nullptr) 
	{
		stack->push(current->left);
		current->left->code = current->code;
		current->left->code.push_back('0');
	}
	
	if (current->right != nullptr) 
	{
		stack->push(current->right);
		current->right->code = current->code;
		current->right->code.push_back('1');
	}

	return current->letter;
}
