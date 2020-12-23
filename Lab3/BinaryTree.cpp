#include <stdexcept>

#include "BinaryTree.h"

using namespace std;

BinarySearchTree::BinarySearchTree()
{
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
	delete root;
	root = nullptr;
}

bool BinarySearchTree::contains(int SearchKey) // finds cerain element
{
	Node* current = root;
	
	while ((SearchKey != current->key) && (current != nullptr)) // stop when found or not found where expected
	{
		if (SearchKey < current->key) {
			current = current->left;
			continue;
		}

		if (SearchKey > current->key) {
			current = current->right;
			continue;
		}
	}
	
	if (current == nullptr) { return false; } // expected node non-existent
	
	else { return true; }
}

void BinarySearchTree::insert(int InsertKey) // insert new element 
{
	Node* current = root;

	while (current != nullptr) // prevent out of bounds read
	{
		if (InsertKey <= current->key) 
		{
			if (current->left != nullptr) // this edge arleady exists
			{
				current = current->left; // continuing search in this direction
				continue; 
			}
			
			else 
			{ 
				current->left = new Node(InsertKey); // edge is not used, suitable place for the new Node
				break;
			}
		}

		if (InsertKey > current->key) 
		{
			if (current->right != nullptr) // this edge arleady exists
			{
				current = current->right; // continuing search in this direction
				continue;
			}

			else
			{
				current->right = new Node(InsertKey); // edge is not used, suitable place for the new Node
				break;
			}
		}

	}
}

void BinarySearchTree::remove(int DeleteKey) // delete certain element
{
	Node* current = root;
	Node* previous = root;
	bool leftSubTree;

	while ((DeleteKey != current->key) && (current != nullptr)) // stop when found or not found where expected
	{
		if (DeleteKey < current->key) 
		{
			previous = current;
			current = current->left;
			leftSubTree = true;
		}

		if (DeleteKey > current->key) 
		{
			previous = current;
			current = current->right;
			leftSubTree = false;
		}
	}

	if (current == nullptr) { return; } // expected node non-existent

	else 
	{
		if ((current->left == nullptr) && (current->right == nullptr)) // deleing leaf
		{
			if (DeleteKey == root->key) // root is the only Node
			{
				delete root;
				root = nullptr;
			}
			else
			{
				delete current;
				current = nullptr;
				
				if (leftSubTree) {
					previous->left = nullptr;
				}
				else { previous->right == nullptr; }
			}
		}

		else if ((current->left != nullptr) && (current->right != nullptr)) // deleting node with two edges
		{
			Node* change = current->right;

			while (change->left != nullptr)
			{
				change = change->left;
			}

			int tmp = change->key;
			remove(tmp);
			current->key = tmp;
		}

		else // deleting node with one edge
		{
			if (current->left == nullptr)
			{
				current->key = current->right->key;
				remove(current->right->key);
			}

			else 
			{
				current->key = current->left->key;
				remove(current->left->key);
			}
		}
	}
}