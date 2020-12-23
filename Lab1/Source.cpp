#include <string>
#include "list_class.h"

using namespace std;

List::List()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

List::~List()
{
	delete head;
	delete tail;
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void List::add_first(int newData)
{
	head = new Node(newData);
	tail = head;
}


size_t List::get_size()
{
	return size;
}

void List::push_back(int newData)
{
	if (size == 0) {
		add_first(newData);
	}
	else {
		tail->next = new Node(newData);
		tail = tail->next;
	}
	size++;
}


void List::push_front(int newData)
{
	if (size == 0) {
		add_first(newData);
	}
	else {
		head = new Node(newData, head);
	}
	size++;

}

void List::pop_back()
{
	if (size == 0) return;

	if (size == 1) 
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node* current = head;
		while (current->next != tail) {
			current = current->next;
		}
		current->next = nullptr;
		delete tail;
		tail = current;
	}
	size--;
}