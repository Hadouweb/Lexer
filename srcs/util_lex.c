#include "lexer.h"

void			push_token(t_lex *lex, enum e_tk tk)
{
	t_token		token;

	token.beg = ft_strdup(lex->nbeg);
	token.end = ft_strdup(lex->nend);
	token.tk = tk;
	ft_lstd_pushback(&lex->lst_token, &token, sizeof(t_token));
	ft_lstd_pushback(&lex->lst_token, &token, sizeof(t_token));
	ft_lstd_pushback(&lex->lst_token, &token, sizeof(t_token));
	ft_lstd_pushback(&lex->lst_token, &token, sizeof(t_token));
}