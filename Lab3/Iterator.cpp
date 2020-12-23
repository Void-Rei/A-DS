#include "BinaryTree.h"
#include <stdexcept>

using namespace std;

BinarySearchTree::Queue::Queue() 
{
	first = nullptr;
	last = nullptr;
}

BinarySearchTree::Queue::~Queue() 
{
	while (first != nullptr) 
	{
		queue_Node* temp = first;
		first = first->next;
		delete temp;
	}
}

bool BinarySearchTree::Queue::isEmpty() 
{
	return (first == nullptr);
}

void BinarySearchTree::Queue::push(Node* new_elem)
{
	if (isEmpty()) 
	{
		first = new queue_Node(new_elem);
		last = first;
	}
	else 
	{
		last->next = new queue_Node(new_elem);
		last = last->next;
	}
}

Node* BinarySearchTree::Queue::pop() 
{
	Node* temp = first->element;
	first = first->next;
	return temp;
}

Node* BinarySearchTree::Queue::front() 
{
	return first->element;
}

Iterator* BinarySearchTree::create_bft_iterator() 
{
	return new bft_Iterator(root);
}

BinarySearchTree::bft_Iterator::bft_Iterator(Node* start) 
{
	queue = new Queue();
	queue->push(start);
}

bool BinarySearchTree::bft_Iterator::has_next() 
{
	return !(queue->isEmpty());
}

int BinarySearchTree::bft_Iterator::next()
{
	Node* current;
	current = queue->pop();

	if (current->left != nullptr) {
		queue->push(current->left);
	}

	if (current->right != nullptr) {
		queue->push(current->right);
	}

	return current->data;
}

BinarySearchTree::Stack::Stack() 
{
	top = nullptr;
}

BinarySearchTree::Stack::~Stack() 
{
	while (!isEmpty()) {
		pop();
	}
}

void BinarySearchTree::Stack::push(Node* new_elem) 
{
	top = new stack_Node(new_elem, top);
}

Node* BinarySearchTree::Stack::pop() 
{
	Node* temp = top->element;
	top = top->next;
	return temp;
}

bool BinarySearchTree::Stack::isEmpty() 
{
	return (top == nullptr);
}

Node* BinarySearchTree::Stack::getTop() 
{
	return top->element;
}

Iterator* BinarySearchTree::create_dft_iterator() 
{
	return new dft_Iterator(root);
}

BinarySearchTree::dft_Iterator::dft_Iterator(Node* start) 
{
	stack = new Stack();
	stack->push(start);
}

bool BinarySearchTree::dft_Iterator::has_next() 
{
	return !(stack->isEmpty());
}

int BinarySearchTree::dft_Iterator::next() 
{
	Node* current;
	current = stack->pop();
	
	if (current->left != nullptr) {
		stack->push(current->left);
	}
	
	if (current->right != nullptr) {
		stack->push(current->right);
	}

	return current->data;
}
