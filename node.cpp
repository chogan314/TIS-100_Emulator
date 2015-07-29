#include "node.h"

Node::Node() :
	ACC(GenNonvolatileRegister()),
	BAK(GenNonvolatileRegister()),
	UP(GenVolatileRegister()),
	DOWN(GenVolatileRegister()),
	LEFT(GenVolatileRegister()),
	RIGHT(GenVolatileRegister())
{ }

Node::~Node()
{
	for (Instruction *instruction : instructions)
	{
		delete instruction;
	}
}