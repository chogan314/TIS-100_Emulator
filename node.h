#ifndef NODE_H
#define NODE_H

#include <vector>
#include "register.h"

class Instruction;

class Node
{
public:
	Node();
	~Node();
private:
	Node *up = nullptr;
	Node *down = nullptr;
	Node *left = nullptr;
	Node *right = nullptr;

	Register ACC;
	Register BAK;
	Register UP;
	Register DOWN;
	Register LEFT;
	Register RIGHT;

	std::vector<Instruction*> instructions;
	int instructionPointer = 0;

	bool blocking = false;
};

#endif