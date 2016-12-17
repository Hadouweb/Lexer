#include "lexer.h"

t_list	*get_sub_list(t_link **l)
{
	t_list	*list;
	t_token	*token;
	t_token	*new_token;

	list = NULL;
	while (*l)
	{
		token = PTR_NODE(*l, t_token, link);
		if (token->tk == TK_SCOL)
			return (list);
		if (token->tk != TK_WSPC)
		{
			new_token = make_token(token->str, token->tk);
			ft_list_push_back(&list, &new_token->link);
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
		//printf("----\n");
		//ft_list_print(sub_list->head, debug_print_token_list);
		if (sub_list)
			ft_list_push_back(list_tk_sep, &sub_list->link);
		if (l)
			l = l->next;
	}
	//printf("%lu\n", ft_list_size(*list_tk_sep));
	//ft_list_print((*list_tk_sep)->head, debug_print_token);
}
