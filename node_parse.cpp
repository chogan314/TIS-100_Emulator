#include "node_parse.h"
#include "node.h"

NodeParse::~NodeParse()
{
	for (InstructionParse *instParse : instructionParses)
	{
		delete instParse;
	}
}

Node *NodeParse::CreateNode()
{
	Node *node = new Node();
	for (unsigned int i = 0; i < instructionParses.size(); i++)
	{
		node->AddInstruction(instructionParses[i]->CreateInstruction(i, node, labelDict));
	}
	return node;
}

void NodeParse::AddLabel(std::string label)
{
	labelDict[label] = instructionParses.size();
}

void NodeParse::AddInstruction(InstructionParse *instruction)
{
	instructionParses.push_back(instruction);
}