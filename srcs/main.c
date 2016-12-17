#include "lexer.h"

void			clean_parser(t_parse *parse, t_lex *lex)
{
	clean_sub_list(&lex->list_token_separate);
	clean_list_token(&lex->list_token);
	free(parse->list_tree);
};

int 			main(int ac, char **av)
{
	t_parse			parse;
	t_lex			lex;


	if (ac > 1)
	{
		lexer(&lex, av[1]);
		ft_list_print(lex.list_token->head, debug_print_token_list);

		filter_lexer_list(&lex.list_token, &lex.list_token_separate);
		debug_print_list_sep(lex.list_token_separate);

		parser(&parse, lex.list_token_separate);
		debug_print_list_tree(parse.list_tree);
		clean_parser(&parse, &lex);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}