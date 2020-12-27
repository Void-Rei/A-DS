#ifndef POSTFIX_METHODS_H
#define POSTFIX_METHODS_H

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Node.h"
#include "Stack.h"
#include "List.h"

using namespace std;

bool infix_to_postfix_transfer(List& formula);

void postfix_calculator(List& formula);


#endif POSTFIX_METHODS_H

