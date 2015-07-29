#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Register;

struct RegisterParam
{
	Register *reg = nullptr;
};

struct RegisterRegisterParam
{
	Register *regA = nullptr;
	Register *regB = nullptr;
};

struct ValueRegisterParam
{
	int val = 0;
	Register *reg = nullptr;
};

class Node;

typedef void(*ExecuteFunc)(int index, Node *node);

template <typename T>
using ExecuteParamFunc = void(*)(int index, Node *node, T parameters);

class Instruction
{
public:
	Instruction(int index, Node *node);
	virtual void Execute() = 0;
protected:
	int index;
	Node *node;
};

class NoParamInstruction : public Instruction
{
public:
	NoParamInstruction(int index, Node *node, ExecuteFunc onExecute);
	void Execute();
private:
	ExecuteFunc onExecute;
};

template <typename T>
class ParamInstruction : public Instruction
{
public:
	ParamInstruction(int index, Node *node, T parameters, ExecuteParamFunc<T> onExecute);
	void Execute();
private:
	T parameters;
	ExecuteParamFunc<T> onExecute;
};

#endif