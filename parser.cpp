#include "parser.h"
#include <regex>
#include <sstream>

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

	while (condition(source[index]))
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

std::string Parser::ConsumeLine()
{
	auto isNotNewLine = [](char c)
	{
		return std::regex_match(&c, std::regex("."));
	};

	std::string line = ConsumeWhile(isNotNewLine);

	return line;
}
