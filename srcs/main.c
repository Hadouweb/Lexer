#include "lexer.h"

int 			main(int ac, char **av)
{
	t_list			*list_token_separate;
	t_parse			parse;
	t_lex			lex;

	list_token_separate = NULL;
	parse.last_process = NULL;
	if (ac > 1)
	{
		lexer(&lex, av[1]);
		filter_lexer_list(&lex.list_token, &list_token_separate);
		debug_print_list_sep(list_token_separate);
//		parser(&parse, list_token_separate);
		//debug_print_list_tree(parse.list_tree);
		//clean_list_tree(&parse.list_tree);
		clean_sub_list_token(&list_token_separate);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}