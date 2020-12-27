#ifndef LIST_CLASS_H
#define LIST_CLASS_H

#include "Node.h"

class List
{
public:
    
    List();

    void reset_list(); // resets values of list to default
    void push_back(int); // adds Node to end (tail) of the list
    void push_back(char);
    bool check_type(size_t); // checks type of a Node, true - integer, false - char
    size_t get_size(); // get size of List
    Node* get_head(); // get head of the list
    void print_to_console(); // print all Nodes to console
    void pop_back(); // clears first node
    void clear(); // clear List from all Nodes
    bool isEmpty(); // checks whether the list is empty or not

    ~List();

private:
    void add_first(int); // adds Node to the head of the list
    void add_first(char);

    Node* head;
    Node* tail;
    size_t size;
};

#endif
