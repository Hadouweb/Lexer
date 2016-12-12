#include "lexer.h"

int 			main(int ac, char **av)
{
	t_list			*lst_token_separate;
	t_parse			parse;
	t_lex			lex;

	lst_token_separate = NULL;
	if (ac > 1)
	{
		lexer(&lex, av[1]);
		filter_lexer_list(&lex.lst_token, &lst_token_separate);
		parser(&parse, lst_token_separate);
		debug_print_lst_tree(parse.lst_tree);
		clean_lst_tree(&parse.lst_tree);
		clean_sub_lst_token(&lst_token_separate);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}