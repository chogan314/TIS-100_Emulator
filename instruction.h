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

Instruction *GenMOV(int index, Node *node, ValueRegisterParam param);
Instruction *GenMOV(int index, Node *node, RegisterRegisterParam param);
Instruction *GenSWP(int index, Node *node);
Instruction *GenSAV(int index, Node *node);
Instruction *GenADD(int index, Node *node, int param);
Instruction *GenADD(int index, Node *node, RegisterParam param);
Instruction *GenSUB(int index, Node *node, int param);
Instruction *GenSUB(int index, Node *node, RegisterParam param);
Instruction *GenNEG(int index, Node *node);
Instruction *GenJMP(int index, Node *node, int nextIndex);
Instruction *GenJEZ(int index, Node *node, int nextIndex);
Instruction *GenJNZ(int index, Node *node, int nextIndex);
Instruction *GenJGZ(int index, Node *node, int nextIndex);
Instruction *GenJLZ(int index, Node *node, int nextIndex);
Instruction *GenJRO(int index, Node *node, int offset);
Instruction *GenJRO(int index, Node *node, RegisterParam offset);

#endif