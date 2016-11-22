#include "lexer.h"

int 	main(int ac, char **av)
{
	if (ac > 1)
	{
		lex(av[1]);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}