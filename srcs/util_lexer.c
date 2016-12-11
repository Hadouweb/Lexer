#include "lexer.h"

void			push_token(t_lex *lex, enum e_tk tk)
{
	t_token				token;
	unsigned int		size;

	size = ft_strlen(lex->nbeg) - ft_strlen(lex->nend);
	token.str = ft_strndup(lex->nbeg, size);
	token.tk = tk;
	ft_lstpush_back_alloc(&lex->lst_token, &token, sizeof(t_token));
}