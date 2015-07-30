#ifndef NODE_H
#define NODE_H

#include <vector>
#include "register.h"

class Instruction;

class Node
{
public:
	Node *upNode = nullptr;
	Node *downNode = nullptr;
	Node *leftNode = nullptr;
	Node *rightNode = nullptr;

	Register acc;
	Register bak;
	Register up;
	Register down;
	Register left;
	Register right;

	Register upOut;
	Register downOut;
	Register leftOut;
	Register rightOut;

	Node();
	~Node();

	void AddInstruction(Instruction *instruction);

	void FlushOutputRegisters();

	void Tick();

	void IncInstructionPointer();
	void SetInstructionPointer(int val);

private:
	std::vector<Instruction*> instructions;
	int instructionPointer = 0;

	bool blocking = false;
};

#endif