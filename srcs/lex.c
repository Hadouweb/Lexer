#include "lexer.h"

void	init_sts(t_status *status)
{
	int 	i;

	i = 0;
	while (i < TK_COUNT)
	{
		status[i].prev = STS_HUNGRY;
		status[i].curr = STS_REJECT;
		i++;
	}
}

void	push_token(t_lex lex, unsigned int tk)
{
	t_token		token;

	token.beg = ft_strdup(lex.nbeg);
	token.end = ft_strdup(lex.nend);
	token.tk = tk;
	ft_lstd_pushback(&lex.lst_token, &token, sizeof(t_token));
}

void	lex(char *str)
{
	t_lex			lex;

	ft_bzero(&lex, sizeof(t_lex));
	init_sts(lex.status);
	ft_memset(lex.state, 0, sizeof(unsigned int) * TK_COUNT);
	push_token(lex, TK_BEG);


	//debug_print_status(lex.status);
	//debug_print_state(lex.state);
	ft_lstd_print(lex.lst_token, debug_print_lst_token, 0);
	printf("%s\n", str);
}