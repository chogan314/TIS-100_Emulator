#include "instruction.h"
#include "node.h"

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

Instruction *GenMOV(int index, Node *node, ValueRegisterParam param)
{
	ExecuteParamFunc<ValueRegisterParam> onExecute = [](int index, Node *node, ValueRegisterParam param)
	{
		param.reg->SetValue(param.val);
		node->IncInstructionPointer();
	};

	return new ParamInstruction<ValueRegisterParam>(index, node, param, onExecute);
}

Instruction *GenMOV(int index, Node *node, RegisterRegisterParam param)
{
	ExecuteParamFunc<RegisterRegisterParam> onExecute = [](int index, Node *node, RegisterRegisterParam param)
	{
		if (!param.regA->HasValue())
		{
			param.regA->RequestInput();
			return;
		}

		param.regB->SetValue(param.regA->GetValue());
		node->IncInstructionPointer();
	};

	return new ParamInstruction<RegisterRegisterParam>(index, node, param, onExecute);
}

Instruction *GenSWP(int index, Node *node)
{
	ExecuteFunc onExecute = [](int index, Node *node)
	{
		int temp = node->acc.GetValue();
		node->acc.SetValue(node->bak.GetValue());
		node->bak.SetValue(temp);
		node->IncInstructionPointer();
	};

	return new NoParamInstruction(index, node, onExecute);
}

Instruction *GenSAV(int index, Node *node)
{
	ExecuteFunc onExecute = [](int index, Node *node)
	{
		node->bak.SetValue(node->acc.GetValue());
		node->IncInstructionPointer();
	};

	return new NoParamInstruction(index, node, onExecute);
}

Instruction *GenADD(int index, Node *node, int param)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int param)
	{
		node->acc.SetValue(node->acc.GetValue() + param);
		node->IncInstructionPointer();
	};

	return new ParamInstruction<int>(index, node, param, onExecute);
}

Instruction *GenADD(int index, Node *node, RegisterParam param)
{
	ExecuteParamFunc<RegisterParam> onExecute = [](int index, Node *node, RegisterParam param)
	{
		if (!param.reg->HasValue())
		{
			param.reg->RequestInput();
			return;
		}

		node->acc.SetValue(node->acc.GetValue() + param.reg->GetValue());
		node->IncInstructionPointer();
	};

	return new ParamInstruction<RegisterParam>(index, node, param, onExecute);
}

Instruction *GenSUB(int index, Node *node, int param)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int param)
	{
		node->acc.SetValue(node->acc.GetValue() - param);
		node->IncInstructionPointer();
	};

	return new ParamInstruction<int>(index, node, param, onExecute);
}

Instruction *GenSUB(int index, Node *node, RegisterParam param)
{
	ExecuteParamFunc<RegisterParam> onExecute = [](int index, Node *node, RegisterParam param)
	{
		if (!param.reg->HasValue())
		{
			param.reg->RequestInput();
			return;
		}

		node->acc.SetValue(node->acc.GetValue() - param.reg->GetValue());
		node->IncInstructionPointer();
	};

	return new ParamInstruction<RegisterParam>(index, node, param, onExecute);
}

Instruction *GenNEG(int index, Node *node)
{
	ExecuteFunc onExecute = [](int index, Node *node)
	{
		node->acc.SetValue(-node->acc.GetValue());
		node->IncInstructionPointer();
	};

	return new NoParamInstruction(index, node, onExecute);
}

Instruction *GenJMP(int index, Node *node, int nextIndex)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int nextIndex)
	{
		node->SetInstructionPointer(nextIndex);
	};

	return new ParamInstruction<int>(index, node, nextIndex, onExecute);
}

Instruction *GenJEZ(int index, Node *node, int nextIndex)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int nextIndex)
	{
		if (node->acc.GetValue() == 0)
		{
			node->SetInstructionPointer(nextIndex);
		}
		else
		{
			node->IncInstructionPointer();
		}
	};

	return new ParamInstruction<int>(index, node, nextIndex, onExecute);
}

Instruction *GenJNZ(int index, Node *node, int nextIndex)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int nextIndex)
	{
		if (node->acc.GetValue() != 0)
		{
			node->SetInstructionPointer(nextIndex);
		}
		else
		{
			node->IncInstructionPointer();
		}
	};

	return new ParamInstruction<int>(index, node, nextIndex, onExecute);
}

Instruction *GenJGZ(int index, Node *node, int nextIndex)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int nextIndex)
	{
		if (node->acc.GetValue() > 0)
		{
			node->SetInstructionPointer(nextIndex);
		}
		else
		{
			node->IncInstructionPointer();
		}
	};

	return new ParamInstruction<int>(index, node, nextIndex, onExecute);
}

Instruction *GenJLZ(int index, Node *node, int nextIndex)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int nextIndex)
	{
		if (node->acc.GetValue() < 0)
		{
			node->SetInstructionPointer(nextIndex);
		}
		else
		{
			node->IncInstructionPointer();
		}
	};

	return new ParamInstruction<int>(index, node, nextIndex, onExecute);
}

Instruction *GenJRO(int index, Node *node, int offset)
{
	ExecuteParamFunc<int> onExecute = [](int index, Node *node, int offset)
	{
		node->SetInstructionPointer(index + offset);
	};

	return new ParamInstruction<int>(index, node, offset, onExecute);
}

Instruction *GenJRO(int index, Node *node, RegisterParam offset)
{
	ExecuteParamFunc<RegisterParam> onExecute = [](int index, Node *node, RegisterParam offset)
	{
		if (!offset.reg->HasValue())
		{
			offset.reg->RequestInput();
			return;
		}

		node->SetInstructionPointer(index + offset.reg->GetValue());
	};

	return new ParamInstruction<RegisterParam>(index, node, offset, onExecute);
}