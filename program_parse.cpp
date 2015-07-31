#include "program_parse.h"

ProgramParse::~ProgramParse()
{
	for (NodeParse *parse : nodeParses)
	{
		delete parse;
	}
}

void ProgramParse::AddNodeParse(NodeParse *parse)
{
	nodeParses.push_back(parse);
}

