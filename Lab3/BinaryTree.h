#ifndef BINARY_TREE_CLASS_H
#define BINARY_TREE_CLASS_H

#include "Iterator.h"

class Node
{
public:

	Node(int data, Node* left = nullptr, Node* right = nullptr)
	{
		this->key = data;
		this->left = left;
		this->right = right;
	};
	~Node() {}

	int key;
	Node* left;
	Node* right;
};

class BinarySearchTree
{
private:

	Node* root;

public:

	BinarySearchTree();
	~BinarySearchTree();

	bool contains(int); // finds cerain elsement
	void insert(int); // insert new element 
	void remove(int); // delete certain element

	class Queue 
	{
	private:
		
		class queue_Node 
		{
		public:

			queue_Node(Node* element, queue_Node* next = nullptr) 
			{
				this->element = element;
				this->next = next;
			};
			~queue_Node() {};
			Node* element;
			queue_Node* next;
		};

		queue_Node* first;
		queue_Node* last;

	public:

		Queue();
		~Queue();

		bool isEmpty();
		void push(Node*);
		Node* pop();
		Node* front();
	};

	Iterator* create_bft_iterator();

	class bft_Iterator : public Iterator 
	{
	public:

		bft_Iterator(Node* start);
		bool has_next() override;
		int next() override;

	private:

		Queue* queue;
	};


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
	
	Iterator* create_dft_iterator();

	class dft_Iterator : public Iterator 
	{
	public:

		dft_Iterator(Node* start);
		bool has_next() override;
		int next() override;

	private:

		Stack* stack;
	};
};
	

#endif