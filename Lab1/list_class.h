#ifndef LIST_CLASS_H
#define LIST_CLASS_H

class List
{
public:
    
    List();

    void reset_list(); // resets values of list to default
    void add_first(int); // adds Node to the head of the list
    void push_back(int); // adds Node to end (tail) of the list
    void push_front(int); // add Node to the head of the liset
    void pop_back(); // delete last (tail) Node
    void pop_front(); // delete first (head) Node
    void insert(int, size_t); // add new Node before old one at certain index
    int at(size_t); // get Node at certain index
    void remove(size_t); // delete Node at certain index
    size_t get_size(); // get size of List
    void print_to_console(); // print all Nodes to console
    void clear(); // clear List from all Nodes
    void set(size_t, int); // change Node at certain index
    bool isEmpty(); // checks whether the list is empty or not
    void push_back(List); //add another list at the end of current one

    ~List();

private:
    class Node
    {
    public:
        Node(int data, Node* next = nullptr)
        {
            this->data = data;
            this->next = next;
        };
        ~Node() {}

        int data;
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t size;
};

#endif
