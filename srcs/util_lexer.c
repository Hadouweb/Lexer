#include "lexer.h"

t_token			*make_token(char *str, enum e_tk tk)
{
	t_token		*token;

	token = (t_token*)ft_memalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->tk = tk;
	return (token);
}

void			push_token(t_lex *lex, enum e_tk tk)
{
	t_token				*token;
	unsigned int		size;

	size = ft_strlen(lex->nbeg) - ft_strlen(lex->nend);
	token = make_token(ft_strndup(lex->nbeg, size), tk);
	ft_list_push_back(&lex->list_token, &token->link);
}