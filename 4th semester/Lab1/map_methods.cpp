#include "custom_map.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <class KeyType, class ValueType>
MapNode<KeyType,ValueType>::MapNode()
{
	key = 0;
	value = 0;
	colour = false;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

template <class KeyType, class ValueType>
MapNode<KeyType, ValueType>::MapNode(KeyType NewKey, ValueType NewValue, bool NewColour)
{
	key = NewKey;
	value = NewValue;
	colour = NewColour;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

template <class KeyType, class ValueType>
MapNode<KeyType, ValueType>::~MapNode() 
{}

template <class KeyType, class ValueType>
void MapNode<KeyType,ValueType>::LeftTurn(MapNode* root) // RB-tree left turn
{														// x - prevous node, p - parent of x, y - current node

	if (this->left != nullptr) // if left subtree exists
	{
		this->parent->right = this->right; // x becomes parent of y's subtree

		if (this->parent->parent == nullptr) // if x is the root of the tree
		{
			root = this; // y becomes the root
		}
		else if (this->parent == this->parent->parent->left) // otherwise if x is the left child of p
		{
			this->parent->parent->left = this; // y becomes the left child of p
		}
		else
		{
			this->parent->parent->right = this; // otherwise y becomes the right child of p
		}
	}
}

template <class KeyType, class ValueType>
void MapNode<KeyType, ValueType>::RightTurn(MapNode* root) // RB-tree right turn
{							 // x - prevous node, p - parent of x, y - current node

	if (this->right != nullptr) // if right subtree exists
	{
		this->parent->left = this->left; // x becomes parent of y's subtree

		if (this->parent->parent == nullptr) // if x is the root of the tree
		{
			root = this; // y becomes the root
		}
		else if (this->parent == this->parent->parent->right) // otherwise if x is the right child of p
		{
			this->parent->parent->right = this; // y becomes the right child of p
		}
		else
		{
			this->parent->parent->left = this; // otherwise y becomes the right child of p
		}
	}
}

template <class KeyType, class ValueType>
Map<KeyType, ValueType>::Map()
{
	root = nullptr;
}

template <class KeyType, class ValueType>
Map<KeyType, ValueType>::Map(MapNode<KeyType,ValueType>* NewRoot)
{
	root = NewRoot;
}

template <class KeyType, class ValueType>
void Map<KeyType, ValueType>::insertRepair(MapNode<KeyType, ValueType>* insNode)
{
	MapNode<KeyType,ValueType>* NewNode = insNode;

	while (!(NewNode->parent->colour))
	{
		if (NewNode->parent->parent->left == NewNode->parent)
		{
			if (NewNode->parent->parent->right->colour) // Case I: if right child of granParent for new node is red
			{
				NewNode->parent->parent->right->colour = false; // both children of gP are now painted black
				NewNode->parent->parent->left->colour = false;
				NewNode = NewNode->parent->parent; // gP is now the new node
			}
			else
			{
				if (NewNode->parent->colour) { break; }
														// Case II
				if (NewNode == NewNode->parent->right)  // new node is right child of it's parent 
				{
					NewNode = NewNode->parent; // parent is the new node now
					NewNode->LeftTurn(root);   // and we perform a left rotation
				}
				else
				{
					if (NewNode->parent->colour) { break; }
													 // Case III
					NewNode->parent->colour = false; // change parent's colour to black
					NewNode->parent->parent->RightTurn(root); // perform a right rotation on gP
				}
			}
		}
		else
		{
			if (NewNode->parent->parent->left->colour) // if grandParent is red
			{
				NewNode->parent->parent->left->colour = false;  
				NewNode->parent->parent->right->colour = false; 
				NewNode->parent->parent->colour = true; 
				NewNode = NewNode->parent->parent; // gP is the new node now
			}
			else if (NewNode == NewNode->parent->left) // else if new node if right child of it's parent
			{
				NewNode = NewNode->parent; 
				NewNode->RightTurn(root); 
				NewNode->parent->colour = false; 
				NewNode->parent->parent->colour = true; 
				NewNode->parent->parent->LeftTurn(root); 
			}
		}
	}
}

template <class KeyType, class ValueType>
void Map<KeyType,ValueType>::insert(KeyType NewKey, ValueType NewValue)
{
	MapNode<KeyType,ValueType>* NewNode = new MapNode(NewKey, NewValue, true);
	if (root != nullptr)
	{
		MapNode<KeyType, ValueType>* current = root;
		MapNode<KeyType, ValueType>* parent = root;

		while (current != nullptr)
		{
			if (NewKey >= current->key)
			{
				parent = current;
				current = current->right;
			}
			else
			{
				parent = current;
				current = current->left;
			}
		}
		NewNode->parent = parent;

		if (NewKey >= parent->key)
		{
			parent->right = NewNode;
		}
		else
		{
			parent->left = NewNode;
		}
		insertRepair(NewNode);
	}
	else
	{
		root = NewNode;
	}
}

template <class KeyType, class ValueType>
MapNode<KeyType,ValueType>* Map<KeyType, ValueType>::find(KeyType key) // finds node with given key
{
	if (root != nullptr)
	{
		MapNode<KeyType, ValueType>* current = root;

		while (key != current->key)
		{
			if (key >= current->key)
			{
				current = current->right;
			}
			else
			{
				current = current->left;
			}
		}
	}
	else
	{
		throw out_of_range("Tree is empty, nothing to search");
	}
}

template <class KeyType, class ValueType>
void Map<KeyType, ValueType>::removeRepair(MapNode<KeyType,ValueType>* x)
{
	while ((x == root) && (!(x->colour)))
	{
		if (x->parent->left == x)
		{
			MapNode<KeyType,ValueType>* w = x->parent->right;

			if (w->colour) // case I
			{
				w->colour = false;
				w->parent->colour = true;
				w->leftRotate(root);
				w = x->parent->right;
			}
			if ((!(w->left->colour) || (w->left == nullptr)) && (!(w->right->colour) || (w->right == nullptr))) // case II
			{
				w->colour = true;
				x = x->parent;
			}
			else if (!(w->right->colour)) // case III
			{
				w->left->colour = false;
				w->colour = true;
				w->LeftTurn(root);
				w = x->parent->right;
			}
			else
			{
				w->colour = w->parent->colour;
				x->parent->parent->colour = false;
				w->right->colour = false;
				x->parent->LeftTurn(root);
				root = x;
			}
		}
		else
		{
			Map<KeyType,ValueType>* w = x->parent->left;
			if (w->colour) // case I
			{
				w->colour = false;
				w->parent->colour = true;
				w->RightRotate(root);
				w = x->parent->left;
			}
			if ((!(w->right->colour) || (w->right == nullptr)) && (!(w->left->colour) || (w->left == nullptr))) // case II
			{
				w->colour = true;
				x = x->parent;
				continue;
			}
			else if (!(w->left->colour)) // case III
			{
				w->right->colour = false;
				w->colour = true;
				w->RightTurn(root);
				w = x->parent->left;
			}
			else // case IV
			{
				w->colour = w->parent->colour;
				x->parent->parent->colour = false;
				w->left->colour = false;
				x->parent->RightTurn(root);
				root = x;
			}
		}
		x->colour = false;
	}
}

template <class KeyType, class ValueType>
void Map<KeyType, ValueType>::remove(KeyType key) // removes specific node
{
	MapNode<KeyType,ValueType>* NodeToBeDeleted = find(key);
	if (NodeToBeDeleted != nullptr)
	{
		bool originalColour = NodeToBeDeleted->colour;

		MapNode<KeyType,ValueType>* x;
		if (NodeToBeDeleted->left == nullptr)
		{
			x = NodeToBeDeleted->right;

			if (NodeToBeDeleted->parent->left == NodeToBeDeleted)
			{
				NodeToBeDeleted->parent->left = x;
			}
			else
			{
				NodeToBeDeleted->parent->right = x;
			}
		}
		else
		{
			x = NodeToBeDeleted->left;

			if (NodeToBeDeleted->parent->left == NodeToBeDeleted)
			{
				NodeToBeDeleted->parent->left = x;
			}
			else
			{
				NodeToBeDeleted->parent->right = x;
			}
		}
		removeRepair();
	}
}

template <class KeyType, class ValueType>
void Map<KeyType, ValueType>::clear() // clears the entire tree
{
	MapNode<KeyType, ValueType>* current = root;
	MapNode<KeyType, ValueType>* NodeToBeDeleted = root;

	while (root != nullptr)
	{
		if (current->left != nullptr) 
		{
			current = current->left;
		}
		else if (current->right != nullptr) 
		{
			current = current->right;
		}
		else
		{
			NodeToBeDeleted = current;
			if (current->parent != nullptr) { current = current->parent; }
			delete NodeToBeDeleted;
		}
	}
}

template <class KeyType, class ValueType>
KeyList<KeyType, ValueType>* Map<KeyType, ValueType>::get_keys() // returns list of keys
{
	dft_Iterator* treeIterator = create_dft_iterator();
	MapNode<KeyType, ValueType>* currentNode = root;
	if (root != nullptr)
	{
		bool firstCycle = true;
		KeyList* keyListHead = new KeyList;
		KeyList* previousKey = new KeyList;
		
		while (treeIterator->has_next())
		{
			currentNode = treeIterator->next();
			if (firstCycle)
			{
				keyListHead->key = root->key;
				keyListHead->next = nullptr;
				previousKey = keyListHead;
			}
			else 
			{
				KeyList* currentKey = new KeyList;
				currentKey->key = currentNode->key;
				currentKey->next = nullptr;
				previousKey->next = currentKey;
			}
		}
	}
}

template <class KeyType, class ValueType>
ValueList<KeyType, ValueType>* Map<KeyType, ValueType>::get_values() // returns list of values
{
	dft_Iterator* treeIterator = create_dft_iterator();
	MapNode<KeyType, ValueType>* currentNode;
	if (root != nullptr)
	{
		bool firstCycle = true;
		ValueList* valueListHead = new ValueList;
		ValueList* previousKey = new ValueList;
		ValueList* currentKey;

		while (treeIterator->has_next())
		{
			currentNode = treeIterator->next();
			if (firstCycle)
			{
				valueListHead->value = root->key;
				valueListHead->next = nullptr;
				previousKey = valueListHead;
			}
			else
			{
				currentKey = new ValueList;
				currentKey->value = currentNode->value;
				currentKey->next = nullptr;
				previousKey->next = currentKey;
			}
		}
	}
}

template <class KeyType, class ValueType>
void Map<KeyType, ValueType>::print() // print whole tree to console
{
	dft_Iterator* treeIterator = create_dft_iterator();
	MapNode<KeyType, ValueType>* currentNode;
	if (root != nullptr)
	{
		while (treeIterator->has_next())
		{
			currentNode = treeIterator->next();
			cout << "Key: " << currentNode->key << " | Value:" << currentNode->value << endl;
		}
	}
	else 
	{
		cout << "Error: no data to print" << endl;
	}
}

template <class KeyType, class ValueType>
Map<KeyType, ValueType>::~Map()
{
	this.clear();
}