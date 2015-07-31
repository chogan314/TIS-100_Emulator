#ifndef INSTRUCTION_PARSE
#define INSTRUCTION_PARSE

#include "instruction.h"
#include <unordered_map>

class Node;

typedef std::unordered_map<std::string, int> LabelDict;

enum class RegisterName
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ACC,
	ANY,
	LAST,
	NIL,
	NO_REGISTER
};

enum class OperationType
{
	MOV,
	SWP,
	SAV,
	ADD,
	SUB,
	NEG,
	JMP,
	JEZ,
	JNZ,
	JGZ,
	JLZ,
	JRO
};

class InstructionParse
{
public:
	Instruction *CreateInstruction(int index, Node *node, LabelDict &dict);

	void SetOperationType(OperationType type);
	void SetLHSRegister(RegisterName registerName);
	void SetRHSRegister(RegisterName registerName);
	void SetValue(int value);

private:
	OperationType operationType;
	RegisterName lhsRegister = RegisterName::NO_REGISTER;
	RegisterName rhsRegister = RegisterName::NO_REGISTER;
	int value = 0;
	std::string jmpLabel = "";

	Register *FindRegister(RegisterName name, Node *node, bool isOutput);
	ValueRegisterParam GenValRegParam(Node *node);
	RegisterRegisterParam GenRegRegParam(Node *node);
	RegisterParam GenRegParam(Node *node);

	Instruction *CreateMOVInstruction(int index, Node *node);
	Instruction *CreateSWPInstruction(int index, Node *node);
	Instruction *CreateSAVInstruction(int index, Node *node);
	Instruction *CreateADDInstruction(int index, Node *node);
	Instruction *CreateSUBInstruction(int index, Node *node);
	Instruction *CreateNEGInstruction(int index, Node *node);
	Instruction *CreateJMPInstruction(int index, Node *node, LabelDict &dict);
	Instruction *CreateJEZInstruction(int index, Node *node, LabelDict &dict);
	Instruction *CreateJNZInstruction(int index, Node *node, LabelDict &dict);
	Instruction *CreateJGZInstruction(int index, Node *node, LabelDict &dict);
	Instruction *CreateJLZInstruction(int index, Node *node, LabelDict &dict);
	Instruction *CreateJROInstruction(int index, Node *node);
};

#endif