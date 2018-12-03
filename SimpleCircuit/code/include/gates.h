#ifndef GATES_H
#define GATES_H

#include <iostream>
#include <string>
#include <map>

using std::ostream;
using std::string;
using std::map;

class Gate {
public:
	int  gateType;
	string name;
	Gate* input1;
	Gate* input2;
	map<string, Gate*> output;
	bool value;
	Gate();
	virtual void setValue() = 0;
	void operator=(int type);
};

class andGate :public Gate {
public:
	static int num;
	andGate();
	void setValue();
};

class notGate :public Gate {
public:
	static int num;
	notGate();
	void setValue();
};

class orGate :public Gate {
public:
	static int num;
	orGate();
	void setValue();
};

class xorGate :public Gate {
public:
	static int num;
	xorGate();
	void setValue();
};

class iPort :public Gate {
public:
	static int num;
	iPort();
	void setValue();
};

class oPort :public Gate {
public:
	static int num;
	oPort();
	void setValue();
	friend ostream& operator<<(ostream& os, oPort* op);
};

#endif