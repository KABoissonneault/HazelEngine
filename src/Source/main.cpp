#include "stdafx.h"

#include <iostream>

#include "HazelEngine.h"

int main(int argc, char* argv[])
{
	auto const argBeg = &argv[0];
	auto const argEnd = argBeg + argc;
	std::vector<std::string> args(argBeg, argEnd);

	HE::Engine engine{args};

	auto engineEnd = engine.Run();

	try
	{
		engineEnd.get();
	}
	catch (const std::exception& e)
	{
		HE::LogError("Fatal unhandled engine error: {0}", e);
		return -1;
	}

	return 0;
}