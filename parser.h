#ifndef PARSER_H
#define PARSER_H

#include <string>

typedef bool(*Condition)(char c);

class Parser
{
public:
private:
	std::string source;
	unsigned long index;

	char Peek();
	char ConsumeCharacter();
	std::string ConsumeWhile(Condition condition);
	void ConsumeWhitespace();
	std::string ConsumeLine();
};

#endif