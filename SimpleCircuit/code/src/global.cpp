#include "global.h"
#include "gates.h"

#include <iostream>
#include <iomanip>
#include <Windows.h>

using std::cout;
using std::endl;
using std::left;
using std::setw;

extern map<string, Gate*> circuit;

void display() {
	cout << endl;
	for (int i = 0; i < 25; i++) cout << "/";
	cout << "Display";
	for (int i = 0; i < 25; i++) cout << "/";
	cout << endl;
	cout << "The gates and connections between them are as follows." << endl;
	cout << "They are shown in the form of [ input1 (input2) -> Gate -> output ]" << endl << endl;
	map<string, Gate*>::iterator i;
	for (i = circuit.begin(); i != circuit.end(); i++) {
		if (i->second->gateType == 5) {
			cout << "[ NoInput ";
		}
		else {
			cout << "[ ";
			if (i->second->input1) cout << i->second->input1->name << " ";
			else cout << "NOGATE ";
			if (i->second->gateType != 2 && i->second->gateType != 6) {
				if (i->second->input2) cout << i->second->input2->name << " ";
				else cout << "NOGATE ";
			}
		}
		cout << "-> " << i->first << " -> ";
		if (i->second->gateType == 6) {
			cout << "NoOuput ]" << endl;
		}
		else {
			if (!i->second->output.empty()) {
				map<string, Gate*>::iterator oi;
				for (oi = i->second->output.begin(); oi != i->second->output.end(); oi++) {
					cout << oi->first << " ";
				}
			}
			else cout << "NOGATE ";
			cout << "]" << endl;
		}
	}
	cout << endl;
}

void exiting() {
	cout << endl << endl << endl;
	for (int i = 0; i < 55; i++) cout << "/";
	cout << endl;
	cout << left << setw(53) << "//           Thanks for using Simple Circuit!";
	cout << "//" << endl;
	cout << left << setw(53) << "//                Ready to exit in 5s...";
	cout << "//" << endl;
	cout << left << setw(53) << "//                                        by XuBinnan";
	cout << "//" << endl;
	for (int i = 0; i < 55; i++) cout << "/";
	Sleep(5000);
	exit(0);
}

void otherwise() {
	cout << "Please enter the valid number. Try again." << endl;
}