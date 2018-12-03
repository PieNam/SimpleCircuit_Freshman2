#include "global.h"
#include "gates.h"
#include "build.h"
#include "simulate.h"

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <map>

using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::cin;
using std::map;
using std::string;

void welcome();
void operation();
void setInput();
void clear();

map<string, Gate*> circuit;
bool hasSetInput = false;

void welcome() {
	for (int i = 0; i < 55; i++) cout << "/";
	cout << endl;
	cout << left << setw(53) << "//            Welcome to Simple Circuit!";
	cout << "//" << endl;
	cout << left << setw(53) << "// Here, you are allowed to create your own circuits";
	cout << "//" << endl;
	cout << left << setw(53) << "//       by using just and, not, or, xor gates.";
	cout << "//" << endl;
	cout << left << setw(53) << "//  The gates available has at most two input ports";
	cout << "//" << endl;
	cout << left << setw(53) << "//and more other gates or same gates with more inputs";
	cout << "//" << endl;
	cout << left << setw(53) << "//       can be simulated by using gates above.";
	cout << "//" << endl;
	for (int i = 0; i < 55; i++) cout << "/";
	cout << endl;
}

void operation() {
	cout << endl << endl << endl;
	cout << "Enter the following number to take opertaions:" << endl << endl;
	cout << "1.Build. To create gates and connections between them." << endl;
	cout << "2.Display. To show the current gates and the connections." << endl;
	cout << "3.Input setting. To set the initial input(s)." << endl;
	cout << "4.Stimulate. To check and run the circuit, see the output(s)." << endl;
	cout << "0.Exit. To exit the whole project." << endl;
	int opr;
	cin >> opr;
	switch (opr) {
	case 1:build();
		break;
	case 2:display();
		break;
	case 3:setInput();
		break;
	case 4:simulate();
		break;
	case 0:exiting();
		break;
	default:otherwise();
		break;
	}
}

void setInput() {
	cout << endl << endl;
	for (int i = 0; i < 25; i++) cout << "/";
	cout << "SetInput";
	for (int i = 0; i < 25; i++) cout << "/";
	cout << endl;
	display();
	cout << "Set the value of the following input ports:(0/1)" << endl << endl;
	map<string, Gate*>::iterator i;
	for (i = circuit.begin(); i != circuit.end(); i++) {
		if (i->second->gateType == 5) {
			cout << i->first << ":";
			int v;
			cin >> v;
			i->second->value = v;
		}
	}
	cout << "Input setting done." << endl;
	hasSetInput = true;
}

void clear() {
	map<string, Gate*>::iterator i;
	for (i = circuit.begin(); i != circuit.end(); i++) {
		delete i->second;
	}
}

int main() {
	welcome();
	while (true)
		operation();
	clear();
	return 0;
}