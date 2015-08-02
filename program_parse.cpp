#include "program_parse.h"

ProgramParse::~ProgramParse()
{
	for (NodeParse *parse : nodeParses)
	{
		delete parse;
	}
}

Program *ProgramParse::CreateProgram()
{
	Program *program = new Program();
	for (NodeParse *nParse : nodeParses)
	{
		program->AddNode(nParse->CreateNode());
	}
	return program;
}

void ProgramParse::AddNodeParse(NodeParse *parse)
{
	nodeParses.push_back(parse);
}

