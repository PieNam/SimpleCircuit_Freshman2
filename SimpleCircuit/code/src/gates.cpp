#include "gates.h"

#include <sstream>

using std::string;
using std::stringstream;

//members' implementations of Gate
Gate::Gate() {
	input1 = input2 = NULL;
}
void Gate::operator=(int type) {
	gateType = type;
}

//members' implementations of andGate
int andGate::num = 0;
andGate::andGate() {
	num++;
	stringstream t;
	t << "and" << num;
	t >> name;
}
void andGate::setValue() {
	if (input1->value && input2->value) value = 1;
	else value = 0;
}

//members' implementations of notGate
int notGate::num = 0;
notGate::notGate() {
	num++;
	stringstream t;
	t << "not" << num;
	t >> name;
}
void notGate::setValue() {
	if (input1->value) value = 0;
	else value = 1;
}

//members' implementations of orGate
int orGate::num = 0;
orGate::orGate() {
	num++;
	stringstream t;
	t << "or" << num;
	t >> name;
}
void orGate::setValue() {
	if (input1->value || input2->value) value = 1;
	else value = 0;
}

//members' implementations of xorGate
int xorGate::num = 0;
xorGate::xorGate() {
	num++;
	stringstream t;
	t << "xor" << num;
	t >> name;
}
void xorGate::setValue() {
	if (input1->value != input2->value) value = 1;
	else value = 0;
}

//members' implementations of iPort
int iPort::num = 0;
iPort::iPort() {
	num++;
	stringstream t;
	t << "input" << num;
	t >> name;
}
void iPort::setValue() {}

//members' implementations of oPort
int oPort::num = 0;
oPort::oPort() {
	num++;
	stringstream t;
	t << "output" << num;
	t >> name;
}
void oPort::setValue() {
	value = input1->value;
}