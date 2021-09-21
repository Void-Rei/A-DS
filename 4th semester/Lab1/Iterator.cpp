#include "custom_map.h"
#include <stdexcept>

using namespace std;

template <class KeyType, class ValueType>
Map<KeyType,ValueType>::Stack::Stack()
{
	top = nullptr;
}

template <class KeyType, class ValueType>
Map<KeyType,ValueType>::Stack::~Stack() 
{
	while (!isEmpty()) {
		pop();
	}
}

template <class KeyType, class ValueType>
void Map<KeyType,ValueType>::Stack::push(MapNode<KeyType, ValueType>* new_elem)
{
	top = new stackNode(new_elem, top);
}

template <class KeyType, class ValueType>
MapNode<KeyType, ValueType>* Map<KeyType,ValueType>::Stack::pop()
{
	MapNode<KeyType, ValueType>* temp = top->element;
	top = top->next;
	return temp;
}

template <class KeyType, class ValueType>
bool Map<KeyType,ValueType>::Stack::isEmpty() 
{
	return (top == nullptr);
}

template <class KeyType, class ValueType>
MapNode<KeyType, ValueType>* Map<KeyType,ValueType>::Stack::getTop()
{
	return top->element;
}

template <class KeyType, class ValueType>
Map<KeyType, ValueType>::dft_Iterator* Map<KeyType,ValueType>::create_dft_iterator()
{
	return new dft_Iterator(root);
}

template <class KeyType, class ValueType>
Map<KeyType,ValueType>::dft_Iterator::dft_Iterator(MapNode<KeyType, ValueType>* start)
{
	stack = new Stack();
	stack->push(start);
}

template <class KeyType, class ValueType>
bool Map<KeyType,ValueType>::dft_Iterator::has_next() 
{
	return !(stack->isEmpty());
}

template <class KeyType, class ValueType>
MapNode<KeyType, ValueType>* Map<KeyType,ValueType>::dft_Iterator::next()
{
	MapNode<KeyType, ValueType>* current;
	current = stack->pop();
	
	if (current->left != nullptr) {
		stack->push(current->left);
	}
	
	if (current->right != nullptr) {
		stack->push(current->right);
	}

	return current;
}
