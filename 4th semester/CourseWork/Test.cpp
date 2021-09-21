#include <iostream>
#include <stdexcept>
#include <fstream>
#include "node.h"
#include "tree.h"

int main()
{
	ifstream in;
	in.open("test.txt");

	char probe;
	char parent = 'S';
	char child = 'T';
	unsigned capcity = 0;
	bool parentFlag = true;
	Tree net;

	int i = 0;
	while ((i < 50) && !(in.eof()))
	{
		in >> probe;
		//cout << probe << endl;
		if ((probe >= 65) && (probe <= 90) && parentFlag)
		{
			parent = probe;
			parentFlag = false;
		}
		else if ((probe >= 65) && (probe <= 90) && !parentFlag)
		{
			child = probe;
		}
		else if ((probe >= 48) && (probe <= 57) && !parentFlag)
		{
			in.seekg(-1, in.cur);
			in >> capcity;
			parentFlag = true;
			i++;
		}
		else if ((probe != '\n') && !(in.eof()))
		{
			cout << "Error: invalid text input;" << endl;
		}

		net.insert(parent, child, capcity);
	}

	net.setHeight(i);
	
	in.close();

	unsigned netMaxFlow = net.Push_Relabel_maxFlow();

	cout << "Maximum flow is: " << netMaxFlow << endl;
}