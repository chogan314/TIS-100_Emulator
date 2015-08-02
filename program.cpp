#include "program.h"

Program::~Program()
{
	for (Node *node : nodes)
	{
		delete node;
	}
}

void Program::AddNode(Node *node)
{
	if (nodes.size() >= 12)
	{
		return;
	}

	nodes.push_back(node);
	
	if (nodes.size() == 12)
	{
		for (int i = 0; i < 12; i++)
		{
			if (i % 4 != 0)
			{
				nodes[i]->leftNode = nodes[i - 1];
			}

			if ((i + 1) % 4 != 0)
			{
				nodes[i]->rightNode = nodes[i + 1];
			}

			if (i > 3)
			{
				nodes[i]->upNode = nodes[i - 4];
			}

			if (i < 8)
			{
				nodes[i]->downNode = nodes[i + 4];
			}
		}
	}
}

void Program::Tick()
{
	for (Node *node : nodes)
	{
		node->FlushOutputRegisters();
		node->Tick();
	}
}