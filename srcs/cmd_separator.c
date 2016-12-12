#include "lexer.h"

t_listd_info	*get_sub_list(t_list **l)
{
	t_listd_info	*sub_list;
	t_token			*token;
	t_token			new_token;

	sub_list = NULL;
	while (*l)
	{
		token = (t_token *) (*l)->content;
		if (token->tk == TK_SCOL || token->tk == TK_AND_IF)
			return (sub_list);
		if (token->tk != TK_WSPC && token->tk != TK_END)
		{
			new_token.str = ft_strdup(token->str);
			new_token.tk = token->tk;
			ft_lstd_pushback_alloc(&sub_list, &new_token, sizeof(t_token));
		}
		*l = (*l)->next;
	}
	return (sub_list);
}

void	filter_lexer_list(t_list **lst, t_list **lst_tk_sep)
{
	t_listd_info	*sub_lst;
	t_list			*l;

	l = *lst;
	while (l)
	{
		sub_lst = get_sub_list(&l);
		if (sub_lst)
			ft_lstpush_back(lst_tk_sep, sub_lst, sizeof(t_listd_info));
		if (l)
			l = l->next;
	}
	clean_lst_token(lst);
}
