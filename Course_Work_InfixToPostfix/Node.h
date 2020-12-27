#ifndef NODE_CLASS_H
#define NODE_CLASS_H

class Node
{
public:
    Node(int data, Node* next = nullptr) // integer-data node
    {
        this->i_data = data;
        this->c_data = 'i';
        this->next = next;
    };

    Node(char data, Node* next = nullptr) // char-data node (for operators)
    {
        this->c_data = data;
        this->i_data = 0;
        this->next = next;
    };

    ~Node() {}

    int i_data;
    char c_data;
    Node* next;
};

#endif

