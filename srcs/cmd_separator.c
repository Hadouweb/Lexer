#include "lexer.h"

t_list	*get_sub_list(t_link **l)
{
	t_list		*sub_list;
	t_token		*token;
	t_token		new_token;

	sub_list = NULL;
	while (*l)
	{
		token = (t_token *)(*l);
		if (token->tk == TK_SCOL || token->tk == TK_AND_IF)
			return (sub_list);
		if (token->tk != TK_WSPC && token->tk != TK_END)
		{
			new_token.str = ft_strdup(token->str);
			new_token.tk = token->tk;
			//ft_listd_pushback_alloc(&sub_list, &new_token, sizeof(t_token));
		}
		*l = (*l)->next;
	}
	return (sub_list);
}

void	filter_lexer_list(t_list **list, t_list **list_tk_sep)
{
	t_list		*sub_list;
	t_link		*l;

	if (list_tk_sep)
		;

	l = (*list)->head;
	while (l)
	{
		sub_list = get_sub_list(&l);
		if (sub_list)
			;//ft_listpush_back(list_tk_sep, sub_list, sizeof(t_list));
		if (l)
			l = l->next;
	}
	clean_list_token(list);
}
