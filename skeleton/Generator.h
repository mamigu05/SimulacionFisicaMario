#pragma once

#include <vector>

class Generator
{
public:
	std::vector<Generator*> generators;

	Generator() {}

	void addGenerator(Generator* g) { generators.push_back(g); }

	void erase() {};
};

