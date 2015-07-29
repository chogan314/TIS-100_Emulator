#include "instruction.h"

Instruction::Instruction(int index, Node *node) :
	index(index),
	node(node)
{}

NoParamInstruction::NoParamInstruction(int index, Node *node, ExecuteFunc onExecute) :
	Instruction(index, node),
	onExecute(onExecute)
{ }

void NoParamInstruction::Execute()
{
	onExecute(index, node);
}

template <typename T>
ParamInstruction<T>::ParamInstruction(int index, Node *node, T parameters, ExecuteParamFunc<T> onExecute) :
	Instruction(index, node),
	parameters(parameters),
	onExecute(onExecute)
{ }

template <typename T>
void ParamInstruction<T>::Execute()
{
	onExecute(index, node, parameters);
}