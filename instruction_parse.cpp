#include "instruction_parse.h"
#include "node.h"

Instruction *InstructionParse::CreateInstruction(int index,
	Node *node, LabelDict &dict)
{
	switch (operationType)
	{
	case OperationType::MOV:
		return CreateMOVInstruction(index, node);
		break;
	case OperationType::SWP:
		return CreateSWPInstruction(index, node);
		break;
	case OperationType::SAV:
		return CreateSAVInstruction(index, node);
		break;
	case OperationType::ADD:
		return CreateADDInstruction(index, node);
		break;
	case OperationType::SUB:
		return CreateSUBInstruction(index, node);
		break;
	case OperationType::NEG:
		return CreateNEGInstruction(index, node);
		break;
	case OperationType::JMP:
		return CreateJMPInstruction(index, node, dict);
		break;
	case OperationType::JEZ:
		return CreateJEZInstruction(index, node, dict);
		break;
	case OperationType::JNZ:
		return CreateJNZInstruction(index, node, dict);
		break;
	case OperationType::JGZ:
		return CreateJGZInstruction(index, node, dict);
		break;
	case OperationType::JLZ:
		return CreateJLZInstruction(index, node, dict);
		break;
	case OperationType::JRO:
		return CreateJROInstruction(index, node);
		break;
	default:
		break;
	}
}

void InstructionParse::SetOperationType(OperationType type)
{
	operationType = type;
}

void InstructionParse::SetLHSRegister(RegisterName registerName)
{
	lhsRegister = registerName;
}

void InstructionParse::SetRHSRegister(RegisterName registerName)
{
	rhsRegister = registerName;
}

void InstructionParse::SetValue(int value)
{
	this->value = value;
}

Register *InstructionParse::FindRegister(RegisterName name, Node *node, bool isOutput)
{
	Register *reg;

	switch (name)
	{
	case RegisterName::UP:
		reg = isOutput ? &node->upOut : &node->up;
		break;
	case RegisterName::DOWN:
		reg = isOutput ? &node->downOut : &node->down;
		break;
	case RegisterName::LEFT:
		reg = isOutput ? &node->leftOut : &node->left;
		break;
	case RegisterName::RIGHT:
		reg = isOutput ? &node->rightOut : &node->right;
		break;
	case RegisterName::ACC:
		reg = &node->acc;
		break;
	case RegisterName::ANY:
		break;
	case RegisterName::LAST:
		break;
	case RegisterName::NIL:
		break;
	default:
		break;
	}

	return reg;
}

ValueRegisterParam InstructionParse::GenValRegParam(Node *node)
{
	ValueRegisterParam param;
	param.val = value;
	param.reg = FindRegister(rhsRegister, node, true);
	return param;
}

RegisterRegisterParam InstructionParse::GenRegRegParam(Node *node)
{
	RegisterRegisterParam param;
	param.regA = FindRegister(lhsRegister, node, false);
	param.regB = FindRegister(rhsRegister, node, true);
	return param;
}

RegisterParam InstructionParse::GenRegParam(Node *node)
{
	RegisterParam param;
	param.reg = FindRegister(lhsRegister, node, false);
	return param;
}

Instruction *InstructionParse::CreateMOVInstruction(int index, Node *node)
{
	if (lhsRegister == RegisterName::NO_REGISTER)
	{
		return GenMOV(index, node, GenValRegParam(node));
	}

	else
	{
		return GenMOV(index, node, GenRegRegParam(node));
	}
}

Instruction *InstructionParse::CreateSWPInstruction(int index, Node *node)
{
	return GenSWP(index, node);
}

Instruction *InstructionParse::CreateSAVInstruction(int index, Node *node)
{
	return GenSAV(index, node);
}

Instruction *InstructionParse::CreateADDInstruction(int index, Node *node)
{
	if (lhsRegister == RegisterName::NO_REGISTER)
	{
		return GenADD(index, node, value);
	}

	else
	{
		return GenADD(index, node, GenRegParam(node));
	}
}

Instruction *InstructionParse::CreateSUBInstruction(int index, Node *node)
{
	if (lhsRegister == RegisterName::NO_REGISTER)
	{
		return GenSUB(index, node, value);
	}

	else
	{
		return GenSUB(index, node, GenRegParam(node));
	}
}

Instruction *InstructionParse::CreateNEGInstruction(int index, Node *node)
{
	return GenNEG(index, node);
}

Instruction *InstructionParse::CreateJMPInstruction(int index, Node *node, LabelDict &dict)
{
	return GenJMP(index, node, dict[jmpLabel]);
}

Instruction *InstructionParse::CreateJEZInstruction(int index, Node *node, LabelDict &dict)
{
	return GenJEZ(index, node, dict[jmpLabel]);
}

Instruction *InstructionParse::CreateJNZInstruction(int index, Node *node, LabelDict &dict)
{
	return GenJNZ(index, node, dict[jmpLabel]);
}

Instruction *InstructionParse::CreateJGZInstruction(int index, Node *node, LabelDict &dict)
{
	return GenJGZ(index, node, dict[jmpLabel]);
}

Instruction *InstructionParse::CreateJLZInstruction(int index, Node *node, LabelDict &dict)
{
	return GenJLZ(index, node, dict[jmpLabel]);
}

Instruction *InstructionParse::CreateJROInstruction(int index, Node *node)
{
	if (lhsRegister == RegisterName::NO_REGISTER)
	{
		return GenJRO(index, node, value);
	}

	else
	{
		return GenJRO(index, node, GenRegParam(node));
	}
}