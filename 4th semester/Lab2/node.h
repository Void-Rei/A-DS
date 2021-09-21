#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
public:

	char letter;
	size_t weight;
	Node* left;
	Node* right;
	std::string code;

	Node(char nletter, unsigned nweight, Node* nleft = nullptr, Node* nright = nullptr)
	{
		letter = nletter;
		weight = nweight;
		left = nleft;
		right = nright; 
		code = "";
	};
	~Node() 
	{
		left = nullptr;
		right = nullptr;
		code.clear();
	}

};

#endif