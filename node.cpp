#include "node.h"
#include "instruction.h"

Node::Node() :
	acc(GenNonvolatileRegister()),
	bak(GenNonvolatileRegister()),
	up(GenVolatileRegister()),
	down(GenVolatileRegister()),
	left(GenVolatileRegister()),
	right(GenVolatileRegister()),
	upOut(GenVolatileRegister()),
	downOut(GenVolatileRegister()),
	leftOut(GenVolatileRegister()),
	rightOut(GenVolatileRegister())
{ }

Node::~Node()
{
	for (Instruction *instruction : instructions)
	{
		delete instruction;
	}
}

void Node::AddInstruction(Instruction *instruction)
{
	instructions.push_back(instruction);
}

void Node::FlushOutputRegisters()
{
	if (upOut.HasValue())
	{
		if (upNode && upNode->down.IsRequestingInput())
		{
			upNode->down.SetValue(upOut.GetValue());
		}
		else
		{
			blocking = true;
		}
	} 
	
	else if (downOut.HasValue())
	{
		if (downNode && downNode->up.IsRequestingInput())
		{
			downNode->up.SetValue(downOut.GetValue());
		}
		else
		{
			blocking = true;
		}
	}

	else if (leftOut.HasValue())
	{
		if (leftNode && leftNode->right.IsRequestingInput())
		{
			leftNode->right.SetValue(leftOut.GetValue());
		}
		else
		{
			blocking = true;
		}
	}

	else if (rightOut.HasValue())
	{
		if (rightNode && rightNode->left.IsRequestingInput())
		{
			rightNode->left.SetValue(rightOut.GetValue());
		}
		else
		{
			blocking = true;
		}
	}
}

void Node::Tick()
{
	if (blocking)
	{
		return;
	}

	if (instructions.size() > 0)
	{
		instructions[instructionPointer]->Execute();
	}
}

void Node::IncInstructionPointer()
{
	instructionPointer++;
	if (instructionPointer >= instructions.size())
	{
		instructionPointer = 0;
	}
}

void Node::SetInstructionPointer(int val)
{
	if (val >= instructions.size())
	{
		val = instructions.size() - 1;
	}

	instructionPointer = val;
}