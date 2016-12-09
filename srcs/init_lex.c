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
	lex->token_func[0] = tk_word;
	lex->token_func[1] = tk_and_if;
	lex->token_func[2] = tk_or_if;
	lex->token_func[3] = tk_dless;
	lex->token_func[4] = tk_dgreat;
	lex->token_func[5] = tk_lessand;
	lex->token_func[6] = tk_greatand;
	lex->token_func[7] = tk_lessgreat;
	lex->token_func[8] = tk_clobber;
	lex->token_func[9] = tk_wspc;
	lex->token_func[10] = tk_pipe;
	lex->token_func[11] = tk_scol;
	lex->token_func[12] = tk_and;
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