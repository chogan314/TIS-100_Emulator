#include <iostream>
#include "node.h"
#include "instruction.h"
#include <vector>

int main(int argc, char **argv)
{
	std::vector<Node> nodes;
	for (int i = 0; i < 12; i++)
	{
		nodes.push_back(Node());
	}

	for (int i = 0; i < 12; i++)
	{
		if (i % 4 != 0)
		{
			nodes[i].leftNode = &nodes[i - 1];
		}

		if ((i + 1) % 4 != 0)
		{
			nodes[i].rightNode = &nodes[i + 1];
		}

		if (i > 3)
		{
			nodes[i].upNode = &nodes[i - 4];
		}

		if (i < 8)
		{
			nodes[i].downNode = &nodes[i + 4];
		}
	}

	ValueRegisterParam param0;
	param0.val = 1;
	param0.reg = &nodes[0].downOut;

	nodes[0].AddInstruction(GenMOV(0, &nodes[0], param0));

	RegisterRegisterParam param1;
	param1.regA = &nodes[4].up;
	param1.regB = &nodes[4].downOut;

	nodes[4].AddInstruction(GenMOV(0, &nodes[4], param1));

	for (int i = 0; i < 10; i++)
	{
		for (Node &node : nodes)
		{
			node.FlushOutputRegisters();
		}

		for (Node &node : nodes)
		{
			node.Tick();
		}
	}
}