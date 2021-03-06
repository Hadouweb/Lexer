#include "lexer.h"

int				find_token_substr(t_lex *lex)
{
	int		i;
	int		find;

	i = 0;
	find = 0;
	while (i < TK_COUNT)
	{
		if (lex->status[i].prev != STS_REJECT)
			lex->status[i].curr =
			lex->token_func[i](*lex->nend, &lex->state[i], &lex->quoting);
		if (lex->status[i].curr != STS_REJECT)
			find = 1;
		i++;
	}
	return (find);
}

void			next_char_substr(t_lex *lex)
{
	int		i;

	i = 0;
	lex->nend++;
	while (i < TK_COUNT)
	{
		lex->status[i].prev = lex->status[i].curr;
		i++;
	}
}

enum e_tk		end_substr(t_lex *lex)
{
	int		i;
	int		accepted_token;

	i = 0;
	accepted_token = TK_COUNT;
	while (i < TK_COUNT)
	{
		if (lex->status[i].prev == STS_ACCEPT)
			accepted_token = i;
		lex->status[i].prev = STS_HUNGRY;
		lex->status[i].curr = STS_REJECT;
		i++;
	}
	return (accepted_token);
}

enum e_lex		last_substr(t_lex *lex)
{
	int 	accepted_token;

	accepted_token = end_substr(lex);
	push_token(lex, accepted_token);
	if (accepted_token == TK_COUNT)
		return (LEX_UNKNOWN_TOKEN);
	return (LEX_OK);
}

enum e_lex		main_loop_lex(t_lex *lex)
{
	int 	tk_find;
	int 	accepted_token;

	while (*lex->nend)
	{
		tk_find = find_token_substr(lex);
		if (tk_find)
		 	next_char_substr(lex);
		else
		{
			accepted_token = end_substr(lex);
			push_token(lex, accepted_token);
			if (accepted_token == TK_COUNT)
				return (LEX_UNKNOWN_TOKEN);
			lex->nbeg = lex->nend;
		}
	}
	return (last_substr(lex));
}