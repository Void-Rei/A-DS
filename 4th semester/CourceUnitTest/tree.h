#ifndef TREE_CLASS_H
#define TREE_CLASS_H

#include "node.h"

class Tree
{
private:

	Node* s; // source
	Node* t; // sink

public:

	Tree();
	Tree(Node*, Node*, size_t);
	~Tree();

	//bool contains(int); // finds cerain elsement
	void insert(char, char, unsigned); // insert new element 
	//void remove(int); // delete certain element
	void setHeight(size_t height);

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
		Node* next();

	private:

		Stack* stack;
	};
	
	dft_Iterator* create_dft_Iterator();
	
	unsigned Push_Relabel_maxFlow();
};

#endif