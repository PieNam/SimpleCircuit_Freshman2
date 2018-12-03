#include "build.h"
#include "global.h"
#include "gates.h"

#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using std::pair;

extern map<string, Gate*> circuit;

void build() {
	cout << endl << endl;
	for (int i = 0; i < 25; i++) cout << "/";
	cout << "Build";
	for (int i = 0; i < 25; i++) cout << "/";
	cout << endl;
	cout << "Enter the following number to take opertaions:" << endl << endl;
	cout << "1.Create. To add new gates to your circuit." << endl;
	cout << "2.Connect. To connect the gates or i/o ports." << endl;
	cout << "3.Disconnect. To disconnect the gates or i/o." << endl;
	cout << "0.Exit. To exit the whole project." << endl;
	int buildOpr;
	cin >> buildOpr;
	switch (buildOpr) {
	case 1:create();
		break;
	case 2:connect();
		break;
	case 3:disconnect();
		break;
	case 0:exiting();
		break;
	default:otherwise();
		break;
	}
}

void create() {
	cout << endl << "   ";
	for (int i = 0; i < 22; i++) cout << "/";
	cout << "Create";
	for (int i = 0; i < 22; i++) cout << "/";
	cout << endl;
	cout << "Keep entering the corresponding number to get enough gates." << endl;
	cout << "The number of numbers would be also the gates'. Enter 0 to end." << endl;
	cout << "Enter the following number to create corresponding gates:" << endl << endl;
	cout << "1.And Gate;    2.Not Gate;    3.Or Gate;     4.Xor Gate;    " << endl;
	cout << "5.Input Port;                 6.Outout Port;                " << endl;
	int gateKind;
	do {
		cin >> gateKind;
		switch (gateKind) {
		case 1: {
			Gate* tg = new andGate;
			*tg = 1;
			circuit.insert(pair<string, Gate*>(tg->name, tg));
			break;
		}
		case 2: {
			Gate* tg = new notGate;
			*tg = 2;
			circuit.insert(pair<string, Gate*>(tg->name, tg));
			break;
		}
		case 3: {
			Gate* tg = new orGate;
			*tg = 3;
			circuit.insert(pair<string, Gate*>(tg->name, tg));
			break;
		}
		case 4: {
			Gate* tg = new xorGate;
			*tg = 4;
			circuit.insert(pair<string, Gate*>(tg->name, tg));
			break;
		}
		case 5: {
			Gate* tg = new iPort;
			*tg = 5;
			circuit.insert(pair<string, Gate*>(tg->name, tg));
			break;
		}
		case 6: {
			Gate* tg = new oPort;
			*tg = 6;
			circuit.insert(pair<string, Gate*>(tg->name, tg));
			break;
		}
		case 0:break;
		default:break;
		}
	} while (gateKind != 0);
}

void connect() {
	string gate1, gate2;
	do {
		display();
		cout << "   ";
		for (int i = 0; i < 21; i++) cout << "/";
		cout << "Connect";
		for (int i = 0; i < 21; i++) cout << "/";
		cout << endl;
		cout << "All gates you have added are above." << endl;
		cout << "Enter the names of two gates you want to connect together:" << endl;
		cout << "(If valid, the former will be an input of the latter)" << endl;
		cout << "(Enter two 0 to end the operation of connecting)" << endl;
		cin >> gate1 >> gate2;
		map<string, Gate*>::iterator it1, it2;
		it1 = circuit.find(gate1);
		it2 = circuit.find(gate2);
		if (it1 != circuit.end() && it2 != circuit.end()) {
			if (it1->second->gateType == 6 || it2->second->gateType == 5) {
				cout << "Invalid command. Input port can't have input and output port can't have output." << endl;
				continue;
			}
			if (it2->second->gateType == 2 || it2->second->gateType > 4) {
				it2->second->input1 = it1->second;
				it1->second->output.insert(pair<string, Gate*>(it2->second->name, it2->second));
			}
			else {
				cout << "Enter the input port number of " << gate2 << " you want to set." << endl;
				cout << "1 or 2 ?";
				int inputNumber;
				cin >> inputNumber;
				if (inputNumber == 2) {
					it2->second->input2 = it1->second;
					it1->second->output.insert(pair<string, Gate*>(it2->second->name, it2->second));
				}
				else {
					it2->second->input1 = it1->second;
					it1->second->output.insert(pair<string, Gate*>(it2->second->name, it2->second));
				}
			}
			cout << "Connecting operation done." << endl;
		}
		else {
			if (gate1 != "0"&&gate2 != "0") {
				cout << "Gate(s) called is(are) not found..." << endl;
				cout << "Please check the gates and try again..." << endl;
				string ttt;
				getline(cin, ttt);
			}
		}
	} while (gate1 != "0"&&gate2 != "0");
}

void disconnect() {
	string gate1, gate2;
	do {
		display();
		cout << "   ";
		for (int i = 0; i < 20; i++) cout << "/";
		cout << "Disconnect";
		for (int i = 0; i < 20; i++) cout << "/";
		cout << endl;
		cout << "All gates you have added are above." << endl;
		cout << "Enter the names of two gates you want to disconnect:" << endl;
		cout << "(If valid, the connection between the former as an input" << endl;
		cout << "of the latter and the latter will be cut off)" << endl;
		cout << "(Enter two 0 to end the operation of connecting)" << endl;
		cin >> gate1 >> gate2;
		map<string, Gate*>::iterator it1, it2;
		it1 = circuit.find(gate1);
		it2 = circuit.find(gate2);
		if (it1 != circuit.end() && it2 != circuit.end()) {
			if (it2->second->input2 == it1->second) {
				it2->second->input2 = NULL;
				map<string, Gate*>::iterator i;
				i = it1->second->output.find(it2->first);
				if (i != it1->second->output.end()) it1->second->output.erase(i);
			}
			else if (it2->second->input1 == it1->second) {
				it2->second->input1 = NULL;
				map<string, Gate*>::iterator i;
				i = it1->second->output.find(it2->first);
				if (i != it1->second->output.end()) it1->second->output.erase(i);
			}
			else {
				cout << "They are not connected together already." << endl;
			}
			cout << "Disconnecting operation done." << endl;
		}
		else {
			if (gate1 != "0"&&gate2 != "0") {
				cout << "Gate(s) called is(are) not found..." << endl;
				cout << "Please check the gates and try again..." << endl;
			}
			string ttt;
			getline(cin, ttt);
		}
	} while (gate1 != "0"&&gate2 != "0");
}