#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Node.h"
#include "Stack.h"
#include "List.h"
#include "InfixToPosfix.h"

using namespace std;

int main()
{
	List formula;
	bool errors_present;

	errors_present =  infix_to_postfix_transfer(formula);

	if (errors_present)
	{
		cout << "Formula creation was stopped. This was ready before an error occured: " << endl;
		formula.print_to_console();
		
		formula.~List();
		throw runtime_error("Two smth in a row");
		return 0;
	}
	else
	{
		cout << endl;

		postfix_calculator(formula);
		formula.clear();

		return 1;
	}
}