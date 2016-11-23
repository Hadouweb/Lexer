#include "lexer.h"

void			init_sts(t_status *status)
{
	int		i;

	i = 0;
	while (i < TK_COUNT)
	{
		status[i].prev = STS_HUNGRY;
		status[i].curr = STS_REJECT;
		i++;
	}
}

void			init_token_func(t_lex *lex)
{
	lex->token_func[0] = tk_name;
	lex->token_func[1] = tk_spc;
}

void			init_lexer(t_lex *lex, char *str)
{
	ft_bzero(lex, sizeof(t_lex));
	init_sts(lex->status);
	init_token_func(lex);
	ft_memset(lex->state, 0, sizeof(unsigned int) * TK_COUNT);
	lex->nbeg = str;
	lex->nend = str;
}