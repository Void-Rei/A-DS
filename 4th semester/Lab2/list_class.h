#ifndef LIST_CLASS_H
#define LIST_CLASS_H

#include "node.h"
#include <string>

class List // list class uses the same node as the BinaryTree, 
{          // where next element is always on the left of current one
private:
    void add_first(char, unsigned); // adds Node to the head of the list

    Node* head;
    Node* tail;
    size_t size;

public:
    
    List();

    void reset_list(); // resets values of list to default
    void push_back(char, unsigned); // adds Node to end (tail) of the list
    void push_front(char, unsigned); // add Node to the head of the liset
    void pop_back(); // delete last (tail) Node
    void pop_front(); // delete first (head) Node
    void insert(char, unsigned , size_t); // add new Node before old one at certain index
    size_t weightAt(size_t); // get Node at certain index
    size_t find(char); // finds node with cretain letter and gives it's index
    void remove(size_t); // delete Node at certain index
    size_t get_size(); // get size of List
    Node* get_head();
    unsigned print_to_console(); // print all Nodes to console
    void clear(); // clear List from all Nodes
    void setLetter(size_t, char); // change Node's letter at certain index
    void setWeight(size_t, size_t); // change Node's weight at certain index
    void setCode(size_t, std::string);
    void minPair(); // finds minimal pair
    void copy(List); // copies list
    bool isEmpty(); // checks whether the list is empty or not
    void push_back(List); //add another list at the end of current one

    ~List();

};

#endif
