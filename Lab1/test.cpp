#include <iostream>
#include <stdexcept>

#include "list_class.h"

using namespace std;

int main()
{
	List l;
	l.push_front(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(5);
	l.push_back(6);

	l.insert(4, 4);
	l.insert(0, 1);

	int a = l.at(1);
	cout << "At 1-st index we have: " << a << endl;

	if (a == 0) {
		cout << "Yay" << endl << endl;
	}
	else { cout << "Meh" << endl << endl; }
	
	l.at(4);
	cout << "At 4-th index we have: " << a << endl;
	
	if (a == 4) {
		cout << "Yay" << endl << endl;
	}
	else { cout << "Meh" << endl << endl; }

	l.set(1, 1);
	l.remove(2);

	int a = l.at(2);
	cout << "At 2-nd index we have: " << a << endl;

	if (a == 3) {
		cout << "Yay" << endl << endl;
	}
	else { cout << "Meh" << endl << endl; }

	l.pop_front();
	l.pop_back();

	List l2;
	l2 = l;

	l.push_back(l2);

	cout << "Final list size: " << l.get_size() << endl << endl;
	l.print_to_console();
}