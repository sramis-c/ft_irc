#include "../test.hpp"

int main(int argc, char **argv)
{
	ArgParser parser(argc, argv);
	try {
		parser.testInvalidArgument();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return (0);
	}
	return (1);
}