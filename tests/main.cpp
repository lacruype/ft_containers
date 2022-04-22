#include "./tests.hpp"

int main(int argc, char **argv)
{
	std::string choice;
	if (argc != 2)
	{
		std::cout << "No test given, testing vector." << std::endl;
		choice = "vector";
	}
	else
		choice = std::string(argv[1]);
	if (choice == "vector")
		test_vector();
	else if (choice == "map")
		test_map();
	else if (choice == "stack")
		test_stack();
	else if (choice == "enable_if")
		test_enable_if();
	else if (choice == "equal")
		test_equal();
	else if (choice == "lexicographical_compare")
		test_lexicographical_compare();
	else if (choice == "all")
	{
		test_vector();
		test_stack();
		test_map();
		test_enable_if();
		test_equal();
		test_lexicographical_compare();
	}
	else
		std::cout << "No test for " << choice << std::endl;

	return (0);
}