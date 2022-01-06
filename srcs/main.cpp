#include "../includes/ft_containers.hpp"

int	testing(std::vector<std::string> *args);

int main(int ac, char **av)
{
	std::vector<std::string> args;
	if (ac == 0)
	{
		av = NULL;
		args.push_back("Yes");
		args.push_back("No");
		args.push_back("Maybe");
	}
	else
	{
		for (int i = 0; i < ac; i++)
			args.push_back(av[i]);
	}
	testing(args);
}

void	testing(std::vector<std::string> args)
{
	
}