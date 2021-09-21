#ifndef CUSTOM_MAP_H
#define CUSTOM_MAP_H

#include "Iterator.h"

template <class KeyType, class ValueType>
struct KeyList // structure for list of keys
{
	KeyType key;
	KeyType* next;
};

template <class KeyType, class ValueType>
struct ValueList // structure for list of values
{
	ValueType value;
	ValueType* next;
};

template <class KeyType, class ValueType>
class MapNode
{
public:
	KeyType key;
	ValueType value;
	bool colour; // true == red, false == black
	MapNode* left;
	MapNode* right;
	MapNode* parent;

	MapNode();
	MapNode(KeyType NewKey, ValueType NewValue, bool NewColour);
	~MapNode();

	void LeftTurn(MapNode* root); // left rotatiion (turn) for RB-tree
	void RightTurn(MapNode* root); // right rotatiion (turn) for RB-tree
};

template <class KeyType, class ValueType>
class Map
{
public:
	class Stack
	{
	private:

		class stackNode
		{
		public:

			MapNode<KeyType, ValueType>* element;
			stackNode* next;

			stackNode(MapNode<KeyType, ValueType>* element, stackNode* next = nullptr) {
				this->element = element;
				this->next = next;
			}
			~stackNode() {}
		};

		stackNode* top;

	public:

		Stack();
		~Stack();

		void push(MapNode<KeyType, ValueType>*);
		MapNode<KeyType, ValueType>* pop();
		bool isEmpty();
		MapNode<KeyType, ValueType>* getTop();
	};

	class dft_Iterator
	{
	public:
		dft_Iterator(MapNode<KeyType, ValueType>* start);
		bool has_next();
		MapNode<KeyType, ValueType>* next();

	private:
		Stack* stack;
	};

	dft_Iterator* create_dft_iterator();

	Map();
	Map(MapNode<KeyType, ValueType>* NewRoot);

	void insertRepair(MapNode<KeyType, ValueType>* insNode); // restores qualities of RB-tree after insertion
	void insert(KeyType NewKey, ValueType NewValue); // inserts node with specified key
	MapNode<KeyType, ValueType>* find(KeyType key); // finds node with given key
	void removeRepair(MapNode<KeyType, ValueType>* x); // restores qualities of RB-tree after removal
	void remove(KeyType key); // removes specific node
	void clear(); // clears the entire tree
	struct KeyList<KeyType, ValueType>* get_keys(); // returns list of keys
	struct ValueList<KeyType, ValueType>* get_values(); // returns list of values
	void print(); // prints the whole tree to console
	
	~Map();

private:
	MapNode<KeyType, ValueType>* root;
}; 

#endif