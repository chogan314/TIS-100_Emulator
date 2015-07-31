#ifndef PROGRAM_PARSE_H
#define PROGRAM_PARSE_H

#include "node_parse.h"

class ProgramParse
{
public:
	~ProgramParse();

	void AddNodeParse(NodeParse *parse);

private:
	std::vector<NodeParse*> nodeParses;
};

#endif