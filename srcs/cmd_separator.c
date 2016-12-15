#include "lexer.h"

t_list	*get_sub_list(t_link **l)
{
	t_list	*list;
	t_token	*token;

	list = NULL;
	while (*l)
	{
		token = PTR_NODE(*l, t_token, link);
		if (token->tk == TK_SCOL || token->tk == TK_AND_IF)
			return (list);
		if (token->tk != TK_WSPC && token->tk != TK_END)
		{
			ft_list_push_back(&list, &token->link_tmp);
		}
		*l = (*l)->next;
	}
	return (list);
}

void		filter_lexer_list(t_list **list, t_list **list_tk_sep)
{
	t_list		*sub_list;
	t_link		*l;

	l = (*list)->head;
	while (l)
	{
		sub_list = get_sub_list(&l);
		if (sub_list)
			ft_list_push_back(list_tk_sep, &sub_list->link);
		if (l)
			l = l->next;
	}
	//printf("%lu\n", ft_list_size(*list_tk_sep));
	//ft_list_print((*list_tk_sep)->head, debug_print_token);
}
