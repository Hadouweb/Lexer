#include "lexer.h"

t_listd_info	*get_sub_list(t_listd **l)
{
	t_listd_info	*sub_list;
	t_token			*token;
	unsigned int	size;
	t_tree_token	tree_token;

	sub_list = NULL;
	while (*l)
	{
		token = (t_token *) (*l)->content;
		if (token->tk == TK_SCOL || token->tk == TK_AND)
			return (sub_list);
		if (token->tk != TK_WSPC && token->tk != TK_END)
		{
			size = ft_strlen(token->beg) - ft_strlen(token->end);
			tree_token.str = ft_strndup(token->beg, size);;
			tree_token.tk = token->tk;
			ft_lstd_pushback(&sub_list, &tree_token, sizeof(t_tree_token));
		}
		*l = (*l)->next;
	}
	return (sub_list);
}

void			filter_lexer_list(t_listd_info **lst, t_list **lst_tk_sep)
{
	t_listd_info	*sub_lst;
	t_listd			*l;

	l = (*lst)->beg;
	while (l)
	{
		sub_lst = get_sub_list(&l);
		if (sub_lst)
			ft_lstpush_back(lst_tk_sep, sub_lst, sizeof(sub_lst));
		if (l)
			l = l->next;
	}
	clean_lst_token(*lst);
}

int 			main(int ac, char **av)
{
	t_listd_info	*lst_token;
	t_list			*lst_token_separate;

	if (ac > 1)
	{
		lst_token = lexer(av[1]);
		filter_lexer_list(&lst_token, &lst_token_separate);
		parser(lst_token_separate);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}