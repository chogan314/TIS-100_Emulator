#ifndef PROGRAM_PARSE_H
#define PROGRAM_PARSE_H

#include "node_parse.h"
#include "program.h"

class ProgramParse
{
public:
	~ProgramParse();

	Program *CreateProgram();

	void AddNodeParse(NodeParse *parse);

private:
	std::vector<NodeParse*> nodeParses;
};

#endif