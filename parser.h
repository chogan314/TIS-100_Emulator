#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <unordered_set>
#include "program_parse.h"
#include "program.h"

struct OpData
{
	OperationType opType;
	int numArguments = 0;
	bool usesLabel = false;
};

typedef bool(*Condition)(char c);
typedef std::unordered_map<std::string, OpData> OpDict;
typedef std::unordered_map<std::string, RegisterName> RegDict;

class Parser
{
public:
	Program *GenProgram(const std::string &programSource);
private:
	std::string source = "";
	unsigned long index = 0;

	bool isEOF();
	char Peek();
	char ConsumeCharacter();
	std::string ConsumeWhile(Condition condition);
	void ConsumeWhitespace();
	std::string ConsumePhrase();
	std::string ConsumeLine();
	std::string ConsumeAlphaNumeric();
	std::string ConsumePunctuation();

	ProgramParse *ParseProgram();
	NodeParse *ParseNode(OpDict &opDict, RegDict &regDict);
	InstructionParse *ParseInstruction(const std::string &op, OpDict &opDict, RegDict &regDict);
};

#endif