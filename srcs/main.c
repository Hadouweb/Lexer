#include "lexer.h"

int 	main(int ac, char **av)
{
	t_listd_info	*lst_token;

	if (ac > 1)
	{
		lst_token = lexer(av[1]);
		parser(lst_token);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}