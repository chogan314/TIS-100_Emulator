#ifndef PROGRAM_H
#define PROGRAM_H

#include "node.h"

class Program
{
public:
	~Program();

	void AddNode(Node *node);

	void Tick();

private:
	const int WIDTH = 4;
	const int HEIGHT = 3;
	std::vector<Node*> nodes;
};

#endif