#include "simulate.h"
#include "global.h"

#include <iostream>
#include <exception>

using std::cout;
using std::endl;
using std::logic_error;

extern map<string, Gate*> circuit;
extern bool hasSetInput;

static unsigned int checkGate = 0;

void simulate() {
	checkGate = 0;
	cout << endl << endl;
	for (int i = 0; i < 25; i++) cout << "/";
	cout << "Simulate";
	for (int i = 0; i < 25; i++) cout << "/";
	cout << endl;
	bool flag = 0;
	try {
		check();
		flag = 1;
	}
	catch (logic_error le) {
		cout << "There exits an error in your circuit:" << endl;
		cout << le.what() << endl;
		cout << "Correct it and try it again." << endl;
	}
	if (!flag) return;
	if (!hasSetInput) {
		cout << "There exits an error in your circuit:" << endl;
		cout << "The input port(s) has not set yet." << endl;
		cout << "Set the input(s) and try it again." << endl;
		return;
	}
	cout << "The simulation has been operated successfully." << endl;
	map<string, Gate*>::iterator i;
	for (i = circuit.begin(); i != circuit.end(); i++) {
		if (i->second->gateType == 5) {
			setV(i->second);
		}
	}
	cout << endl;
	for (int i = 0; i < 25; i++) cout << "/";
	cout << "Output";
	for (int i = 0; i < 25; i++) cout << "/";
	cout << endl;
	cout << "The output of the port(s) that've been set is as follows:" << endl;
	for (i = circuit.begin(); i != circuit.end(); i++) {
		if (i->second->gateType == 6 && i->second->input1) {
			cout << i->second->name << ": " << i->second->value << endl;
		}
	}
	for (int i = 0; i < 56; i++)cout << "/";
	cout << endl;
}

void setV(Gate* c) {
	c->setValue();
	if (!c->output.empty()) {
		map<string, Gate*>::iterator checkI;
		for (checkI = c->output.begin(); checkI != c->output.end(); checkI++) {
			setV(checkI->second);
		}
	}
}

void check() {
	map<string, Gate*>::iterator i;
	for (i = circuit.begin(); i != circuit.end(); i++) {
		if (i->second->gateType == 5) {
			checkOut(i->second);
		}
		if (i->second->gateType == 6) {
			checkIn(i->second);
		}
	}
}

void checkOut(Gate* c) {
	checkGate++;
	if (checkGate > (4 * circuit.size())) throw logic_error("There is a circle in your circuit, which is not allowed.");
	if (!c->output.empty()) {
		map<string, Gate*>::iterator checkI;
		for (checkI = c->output.begin(); checkI != c->output.end(); checkI++) {
			checkOut(checkI->second);
		}
	}
	else if (c->gateType != 6) {
		string info = "There is an output of ";
		info += c->name;
		info += " that is not connected.";
		throw logic_error(info);
	}
}

void checkIn(Gate*c) {
	if (c->input1) {
		checkIn(c->input1);
	}
	else if (c->input2) {
		checkIn(c->input2);
	}
	else if (c->gateType != 5) {
		string info = "There is an input of ";
		info += c->name;
		info += "that is not connected.";
		throw logic_error(info);
	}
}