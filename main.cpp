#include <iostream>
#include "node.h"
#include "instruction.h"
#include <vector>
#include "parser.h"
#include <fstream>
#include <sstream>

int main(int argc, char **argv)
{
	Parser parser;

	std::stringstream programSource;
	std::ifstream in("Programs/test.txt");
	
	std::string line;
	while (std::getline(in, line))
	{
		programSource << line;
		programSource << "\n";
	}

	Program *program = parser.GenProgram(programSource.str());

	for (int i = 0; i < 10; i++)
	{
		program->Tick();
	}
}