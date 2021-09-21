#ifndef TREE_CLASS_H
#define TREE_CLASS_H

#include "node.h"
#include "list_class.h"
#include <string>

class Tree
{
private:

	Node* root;

public:

	Tree();
	Tree(Node*);
	~Tree();

	void setCodes(List*);

	/*bool contains(int); // finds cerain elsement
	void insert(int); // insert new element 
	void remove(int); // delete certain element*/

	class Stack
	{
	private:

		class stack_Node
		{
		public:

			stack_Node(Node* element, stack_Node* next = nullptr) {
				this->element = element;
				this->next = next;
			};
			~stack_Node() {};

			Node* element;
			stack_Node* next;
		};

		stack_Node* top;

	public:

		Stack();
		~Stack();

		void push(Node*);
		Node* pop();
		bool isEmpty();
		Node* getTop();
	};

	class dft_Iterator
	{
	public:

		dft_Iterator(Node* start);
		bool has_next();
		char next();

	private:

		Stack* stack;
	};

	dft_Iterator* create_dft_iterator();
};

#endif