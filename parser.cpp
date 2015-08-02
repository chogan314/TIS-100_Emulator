#include "parser.h"
#include <regex>
#include <sstream>

Program *Parser::GenProgram(const std::string &programSource)
{
	source = programSource;
	index = 0;
	ProgramParse *programParse = ParseProgram();
	Program *program = programParse->CreateProgram();
	delete programParse;
	return program;
}

bool Parser::isEOF()
{
	return index == source.size() - 1;
}

char Parser::Peek()
{
	return source[index];
}

char Parser::ConsumeCharacter()
{
	return source[index++];
}

std::string Parser::ConsumeWhile(Condition condition)
{
	std::stringstream ss;

	while (condition(source[index]) && !isEOF())
	{
		ss << source[index++];
	}

	return ss.str();
}

void Parser::ConsumeWhitespace()
{
	auto isWhitespace = [](char c)
	{
		return std::regex_match(&c, std::regex("\\s"));
	};

	ConsumeWhile(isWhitespace);
}

std::string Parser::ConsumePhrase()
{
	auto isNotWhitespace = [](char c)
	{
		return !std::regex_match(&c, std::regex("\\s"));
	};

	return ConsumeWhile(isNotWhitespace);
}

std::string Parser::ConsumeLine()
{
	auto isNotNewLine = [](char c)
	{
		return std::regex_match(&c, std::regex("."));
	};

	std::string line = ConsumeWhile(isNotNewLine);

	return line;
}

std::string Parser::ConsumeAlphaNumeric()
{
	auto isAlphaNumeric = [](char c)
	{
		return std::regex_match(&c, std::regex("[a-zA-Z0-9]"));
	};

	std::string str = ConsumeWhile(isAlphaNumeric);

	return str;
}

std::string Parser::ConsumePunctuation()
{
	auto isPunctuation = [](char c)
	{
		return c == ':' || c == ',';
	};

	std::string str = ConsumeWhile(isPunctuation);

	return str;
}

ProgramParse *Parser::ParseProgram()
{
	OpDict cmdDict;

	OpData movData;
	movData.opType = OperationType::MOV;
	movData.numArguments = 2;
	cmdDict["MOV"] = movData;

	OpData swpData;
	swpData.opType = OperationType::SWP;
	cmdDict["SWP"] = swpData;

	OpData savData;
	savData.opType = OperationType::SAV;
	cmdDict["SAV"] = savData;

	OpData addData;
	addData.opType = OperationType::ADD;
	addData.numArguments = 1;
	cmdDict["ADD"] = addData;

	OpData subData;
	subData.opType = OperationType::SUB;
	subData.numArguments = 1;
	cmdDict["SUB"] = subData;

	OpData negData;
	negData.opType = OperationType::NEG;
	cmdDict["NEG"] = negData;

	OpData jmpData;
	jmpData.opType = OperationType::JMP;
	jmpData.numArguments = 1;
	jmpData.usesLabel = true;
	cmdDict["JMP"] = jmpData;

	OpData jezData;
	jezData.opType = OperationType::JEZ;
	jezData.numArguments = 1;
	jezData.usesLabel = true;
	cmdDict["JEZ"] = jezData;

	OpData jnzData;
	jnzData.opType = OperationType::JNZ;
	jnzData.numArguments = 1;
	jnzData.usesLabel = true;
	cmdDict["JNZ"] = jnzData;

	OpData jgzData;
	jgzData.opType = OperationType::JGZ;
	jgzData.numArguments = 1;
	jgzData.usesLabel = true;
	cmdDict["JGZ"] = jgzData;

	OpData jlzData;
	jlzData.opType = OperationType::JLZ;
	jlzData.numArguments = 1;
	jlzData.usesLabel = true;
	cmdDict["JLZ"] = jlzData;

	OpData jroData;
	jmpData.opType = OperationType::JRO;
	jmpData.numArguments = 1;
	cmdDict["JRO"] = jroData;

	RegDict regDict;
	regDict["UP"] = RegisterName::UP;
	regDict["DOWN"] = RegisterName::DOWN;
	regDict["LEFT"] = RegisterName::LEFT;
	regDict["RIGHT"] = RegisterName::RIGHT;
	regDict["ACC"] = RegisterName::ACC;

	ProgramParse *programParse = new ProgramParse();

	ConsumeWhitespace();
	while (!isEOF())
	{
		programParse->AddNodeParse(ParseNode(cmdDict, regDict));
	}

	return programParse;
}

NodeParse *Parser::ParseNode(OpDict &opDict, RegDict &regDict)
{
	NodeParse *nodeParse = new NodeParse();

	ConsumePhrase();
	ConsumeWhitespace();
	ConsumePhrase();
	ConsumeWhitespace();

	while (Peek() != '}')
	{
		if (Peek() == '#')
		{
			ConsumeLine();
		}

		else
		{
			std::string phrase = ConsumeAlphaNumeric();
			if (opDict.count(phrase))
			{
				nodeParse->AddInstruction(ParseInstruction(phrase, opDict, regDict));
			}

			else
			{
				nodeParse->AddLabel(phrase);
				ConsumePunctuation();
			}
		}

		ConsumeWhitespace();
	}

	ConsumePhrase();
	ConsumeWhitespace();

	return nodeParse;
}

InstructionParse *Parser::ParseInstruction(const std::string &op, OpDict &opDict, RegDict &regDict)
{
	InstructionParse *iParse = new InstructionParse();

	OpData opData = opDict[op];

	iParse->SetOperationType(opData.opType);

	if (opData.numArguments == 0)
	{
		ConsumeWhitespace();
		return iParse;
	}

	ConsumeWhitespace();
	std::string lhsArg = ConsumeAlphaNumeric();

	if (opData.usesLabel)
	{
		iParse->SetLabel(lhsArg);
	}
	else if (regDict.count(lhsArg))
	{
		iParse->SetLHSRegister(regDict[lhsArg]);
	}
	else
	{
		iParse->SetValue(std::stoi(lhsArg));
	}

	if (opData.numArguments == 1)
	{
		ConsumeWhitespace();
		return iParse;
	}

	ConsumeWhitespace();
	ConsumePunctuation();
	ConsumeWhitespace();
	std::string rhsArg = ConsumeAlphaNumeric();
	iParse->SetRHSRegister(regDict[rhsArg]);
	ConsumeWhitespace();

	return iParse;
}