#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Node.h"
#include "Stack.h"
#include "List.h"

using namespace std;

bool infix_to_postfix_transfer(List& formula)
{
	ifstream in;
	in.open("test.txt");
	in.unsetf(in.skipws);
	Stack operator_stack;

	Node* added_operator = nullptr;
	Node* stack_top = nullptr;

	char probe; // probe, unknown input saved here
	int num;	// numbers, saved as integers
	bool previous_num = false;		// flag indicating two numbers in a row
	bool previous_operator = false; // flag indicating two operators in a row
	int i = 0;
	while (i < 50)
	{
		in >> probe;
		if ((probe == '0') || (probe == '1') || (probe == '2') || (probe == '3') || (probe == '4') || (probe == '5') || (probe == '6') || (probe == '7') || (probe == '8') || (probe == '9'))
		{
			if (previous_num)
			{
				cout << "Error: Two numbers in a row" << endl;
				return true;
			}
			else
			{
				in.seekg(-1, in.cur);
				in >> num; // found a number, saving it directly
				formula.push_back(num);
				previous_num = true;
				previous_operator = false;
				continue;
			}
		}
		else if ((probe == '-') || (probe == '+') || (probe == '*') || (probe == '/') || (probe == '^') || (probe == '(') || (probe == ')'))
		{
			if (previous_operator)
			{
				cout << "Error: Two numbers in a row" << endl;
				return true;
			}
			
			else 
			{
				previous_num = false;
				previous_operator = true;

				switch (probe) // found an operator, saving previous operators with higher or equal priority into list
				{

					case ('-'):
						if (!(operator_stack.isEmpty()))
						{
							stack_top = operator_stack.getTop();

							if ((stack_top->c_data == '-') || (stack_top->c_data == '+') || (stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
							{
								while ((stack_top->c_data == '-') || (stack_top->c_data == '+') || (stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
								{
									formula.push_back(stack_top->c_data);
									operator_stack.pop();
									stack_top = operator_stack.getTop();
								}
							}
						}
						
						added_operator = new Node('-');
						operator_stack.push(added_operator);
						break;

					case ('+'):
						if (!(operator_stack.isEmpty()))
						{
							stack_top = operator_stack.getTop();

							if ((stack_top->c_data == '-') || (stack_top->c_data == '+') || (stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
							{
								while ((stack_top->c_data == '-') || (stack_top->c_data == '+') || (stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
								{
									formula.push_back(stack_top->c_data);
									operator_stack.pop();
									stack_top = operator_stack.getTop();
								}
							}
						}
						
						added_operator = new Node('+');
						operator_stack.push(added_operator);
						break;

					case ('*'):
						if (!(operator_stack.isEmpty()))
						{
							stack_top = operator_stack.getTop();

							if ((stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
							{
								while ((stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
								{
									formula.push_back(stack_top->c_data);
									operator_stack.pop();
									stack_top = operator_stack.getTop();
								}
							}
						}

						added_operator = new Node('*');
						operator_stack.push(added_operator);
						break;

					case ('/'):
						if (!(operator_stack.isEmpty()))
						{
							stack_top = operator_stack.getTop();

							if ((stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
							{
								while ((stack_top->c_data == '*') || (stack_top->c_data == '/') || (stack_top->c_data == '^'))
								{
									formula.push_back(stack_top->c_data);
									operator_stack.pop();
									stack_top = operator_stack.getTop();
								}
							}
						}

						added_operator = new Node('/');
						operator_stack.push(added_operator);
						break;

					case ('^'):
						if (!(operator_stack.isEmpty()))
						{
							stack_top = operator_stack.getTop();

							if (stack_top->c_data == '^')
							{
								while (stack_top->c_data == '^')
								{
									formula.push_back(stack_top->c_data);
									operator_stack.pop();
									stack_top = operator_stack.getTop();
								}
							}
						}

						added_operator = new Node('^');
						operator_stack.push(added_operator);
						break;

					case ('('):
						added_operator = new Node('('); // adding prioritizing bracket, will play later
						operator_stack.push(added_operator);
						break;

					case (')'):
						if (!(operator_stack.isEmpty()))
						{
							stack_top = operator_stack.getTop();

							while (stack_top->c_data != '(')
							{
								formula.push_back(stack_top->c_data); // saving all operators in brackets
								operator_stack.pop();
								stack_top = operator_stack.getTop();
							}
							operator_stack.pop();
						}

						break;
				}
			}
		}
		else if (in.eof()) { break; }
	}
	
	if (i == 50)
	{
		cout << "Formula too long to compute. Try erasing unnececary symbols (spaces, letters, etc.)." << endl;
		in.close();
		return true;
	}
	else 
	{
		if (!(operator_stack.isEmpty()))
		{
			Node* leftover_operators;
			while (!(operator_stack.isEmpty()))
			{
				leftover_operators = operator_stack.pop(); // saving all operators left in stack
				formula.push_back(leftover_operators->c_data);
			}
		}

		cout << "Postfix expression of given formula:" << endl;
		formula.print_to_console();
		cout << endl;

		operator_stack.~Stack();
		in.close();
		
		return false;
	}

}

void postfix_calculator(List& formula)
{
	Stack calculation_stack;
	Node* current = formula.get_head();
	bool node_type = true;

	Node* first_num = new Node(0);
	Node* second_num = new Node(0);
	Node* result = new Node(0);

	size_t formula_size = formula.get_size();
	int result_int = 0;

	for (size_t i = 1; i <= formula_size; i++)
	{
		node_type = formula.check_type(i);
		if (node_type)
		{
			calculation_stack.push(current); // since it's a number, we just add it to stack
			current = current->next;
		}
		else 
		{
			second_num = calculation_stack.pop(); // we take out last two numbers in stack to count with
			first_num = calculation_stack.pop(); // but numbers in stack are in reverse order

			switch (current->c_data)
			{
				case ('-'):
					if ((first_num->i_data < -1073741823) || (second_num->i_data < -1073741823))
					{
						throw out_of_range("Resulting number is too big");
						return;
					}
					else
					{
						result->i_data = (first_num->i_data) * (second_num->i_data);
					}
					break;
				
				case ('+'):
					if ((first_num->i_data > 1073741823) || (second_num->i_data > 1073741823))
					{
						throw out_of_range("Resulting number is too big");
						return;
					}
					else
					{
						result->i_data = (first_num->i_data) + (second_num->i_data);
					}
					break;

				case ('*'):
					if ((first_num->i_data > 1073741823) || (second_num->i_data > 1073741823))
					{
						throw out_of_range("Resulting number is too big");
						return;
					}
					else 
					{
						result->i_data = (first_num->i_data) * (second_num->i_data);
					}
					break;

				case ('/'):
						if (second_num->i_data > 1073741823)
						{
							throw out_of_range("Resulting number is too big");
							return;
						}
						else
						{
							result->i_data = (first_num->i_data) / (second_num->i_data);
						}
					break;

				case ('^'):
					int power = second_num->i_data;
					result->i_data = first_num->i_data;
						
					for (int j = 1; j <= power; j++)
					{
						result->i_data *= (first_num->i_data);
						if (result->i_data > 1431655764)
						{
							throw out_of_range("Resulting number is too big");
							return;
						}
					}
					break;
			}

			result_int = result->i_data;
			Node* rez = new Node(result_int);
			calculation_stack.push(rez);
		}
	}

	result = calculation_stack.getTop();
	result_int = result->i_data;

	cout << "Result of calculations: " << result_int << endl;

	delete first_num;
	delete second_num;
	delete result;

	current = nullptr;
	calculation_stack.~Stack();
	return;
}