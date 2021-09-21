#ifndef NODE_H
#define NODE_H

using namespace std;

struct flow
{
	unsigned LeftCapacity;
	unsigned RightCapacity;
	unsigned LeftFlow;
	unsigned RightFlow;
};

class Node
{
public:

	char letter; // letter of the node
	struct flow f;
	unsigned excess; // excess flow 
	size_t height;
	Node* left;
	Node* right;

	Node(char letter, Node* left = nullptr, Node* right = nullptr)
	{
		this->letter = letter;
		this->f.LeftCapacity = 0;
		this->f.RightCapacity = 0;
		this->f.LeftFlow = 0;
		this->f.RightFlow = 0;
		this->left = left;
		this->right = right; 
		this->excess = 0;
		this->height = 0;
	};
	~Node() {}

};

#endif