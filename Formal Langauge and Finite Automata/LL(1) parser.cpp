// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <list>
using namespace std;

int main()
{
	/* Thought process: 
	- Create LL(1) table to reference
	- Since c++ doesn't have strings as a primitive, write out table and use the rows and column numbers as the references
	- Have user enter a string and store it into a variable (input)
	- For loop going through string to get user input
	- if statements to check what the symbol is and then check if it is part of the table, otherwise break out and cout << "String not accepted" << endl;
	- create char array for stack. With ones with multiple characters just push the appropriate amount of times
		ex: if (input[i].equals("x") && stack.top == 'S') {
			stack.push('T');
			stack.push('s'); (lowercase letters for prime)
		}
		and so on
	
	*/

	unordered_map<char, unordered_map<char, string>> table = 
	{ {
		{'S', { {'+', ""}, {'-', ""}, {'*', ""}, {'/', ""}, {'x', "Ts"}, {'(', "Ts"}, {')', ""}, {'$', ""} }},
		{'s', {{'+', "+Ts"}, {'-', "-Ts"}, {'*', ""}, {'/', ""}, {'x', ""}, {'(', ""}, {')', "e"}, {'$', "e"} }},
		{'T', {{'+', ""}, {'-', ""}, {'*', ""}, {'/', ""}, {'x', "Rt"}, {'(', "Rt"}, {')', ""}, {'$', "e"} }},
		{'t', {{'+', "e"}, {'-', ""}, {'*', "*Rt"}, {'/', "/Rt"}, {'x', ""}, {'(', ""}, {')', "e"}, {'$', "e"} }},
		{'R', {{'+', ""}, {'-', ""}, {'*', ""}, {'/', ""}, {'x', "x"}, {'(', "(S)"}, {')', ""}, {'$', ""} }},
} };

	/* Table reference
		  | + | - | * | / | x  | (  | ) | $ |
		  ___________________________________
		S |   |   |   |   | Ts | Ts |   |   |
		s |+Ts|-Ts|   |   |    |    | e | e |
		T |   |   |   |   | Rt | Rt |   |   |
		t | e | e |*Rt|/Rt|    |    | e | e |
		R |   |   |   |   | x  | (S)|   |   |
	*/ 

	string input;
	int counter = 0;
	cout << "Enter a string:" << endl;
	cin >> input;
	input += "$";

	stack<char> stack;
	stack.push('S'); // Starting point of stack

	do {
		// x possibilities
		if (input.at(counter) == 'x' && stack.top() == 'S') {
			stack.pop();
			stack.push('s');
			stack.push('T');
		}
		else if (input.at(counter) == 'x' && stack.top() == 'T') {
			stack.pop();
			stack.push('t');
			stack.push('R');
		}
		else if (input.at(counter) == 'x' && stack.top() == 'R') {
			stack.pop();
			stack.push('x');
		}
		else if (input.at(counter) == 'x' && stack.top() == 'x') {
			stack.pop();
			counter++;
		}

		// + possibilities
		else if (input.at(counter) == '+' && stack.top() == 's') {
			stack.pop();
			stack.push('s');
			stack.push('T');
			stack.push('+');
		}
		else if (input.at(counter) == '+' && stack.top() == 't') {
			stack.pop();
			stack.push('e');
		}
		else if (input.at(counter) == '+' && stack.top() == '+') {
			stack.pop();
			counter++;
		}

		// - possibilities
		else if (input.at(counter) == '-' && stack.top() == 's') {
			stack.pop();
			stack.push('s');
			stack.push('T');
			stack.push('-');
		}
		else if (input.at(counter) == '-' && stack.top() == 't') {
			stack.pop();
			stack.push('e');
		}
		else if (input.at(counter) == '-' && stack.top() == '-') {
			stack.pop();
			counter++;
		}

		// * possibilities
		else if (input.at(counter) == '*' && stack.top() == 't') {
			stack.pop();
			stack.push('t');
			stack.push('R');
			stack.push('*');
		}
		else if (input.at(counter) == '*' && stack.top() == '*') {
			stack.pop();
			counter++;
		}

		// / possibilities
		else if (input.at(counter) == '/' && stack.top() == 't') {
			stack.pop();
			stack.push('t');
			stack.push('R');
			stack.push('/');
		}
		else if (input.at(counter) == '/' && stack.top() == '/') {
			stack.pop();
			counter++;
		}

		// ( possibilities
		else if (input.at(counter) == '(' && stack.top() == 'S') {
			stack.pop();
			stack.push('s');
			stack.push('T');
		}
		else if (input.at(counter) == '(' && stack.top() == 'T') {
			stack.pop();
			stack.push('t');
			stack.push('R');
		}
		else if (input.at(counter) == '(' && stack.top() == 'R') {
			stack.pop();
			stack.push(')');
			stack.push('S');
			stack.push('(');
		}
		else if (input.at(counter) == '(' && stack.top() == '(') {
			stack.pop();
			counter++;
		}

		// ) possibilities
		else if (input.at(counter) == ')' && stack.top() == 's') {
			stack.pop();
			stack.push('e');
		}
		else if (input.at(counter) == ')' && stack.top() == 't') {
		stack.pop();
		stack.push('e');
		}
		else if (input.at(counter) == ')' && stack.top() == ')') {
		stack.pop();
		counter++;
		}

		// $ possibilities
		else if (input.at(counter) == '$' && stack.top() == 's') {
		stack.pop();
		stack.push('e');
		}
		else if (input.at(counter) == '$' && stack.top() == 't') {
		stack.pop();
		stack.push('e');
		}

		// e possibilities
		else if (stack.top() == 'e') {
		stack.pop();
		}

		// else
		else {
		cout << "Not accepted" << endl;
		return 0;
		}


	} while (!stack.empty());

	cout << "String accepted" << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
