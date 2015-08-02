#ifndef NODE_PARSE
#define NODE_PARSE

#include <vector>
#include "instruction_parse.h"

class NodeParse
{
public:
	NodeParse::~NodeParse();

	Node *CreateNode();

	void AddLabel(std::string label);
	void AddInstruction(InstructionParse *instruction);

private:
	LabelDict labelDict;
	std::vector<InstructionParse*> instructionParses;
};

#endif