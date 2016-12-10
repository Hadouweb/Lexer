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
		if (token->tk == TK_SCOL || token->tk == TK_AND)
			return (sub_list);
		if (token->tk != TK_WSPC && token->tk != TK_END)
		{
			new_token.str = ft_strdup(token->str);
			new_token.tk = token->tk;
			ft_lstd_pushback(&sub_list, &new_token, sizeof(t_token));
		}
		*l = (*l)->next;
	}
	return (sub_list);
}

void			filter_lexer_list(t_list **lst, t_list **lst_tk_sep)
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
	clean_lst_token(*lst);
}

void	clean_listd_info(t_listd_info *listd)
{
	t_listd		*l;
	t_listd		*tmp;
	t_token		*token;

	l = listd->beg;
	while (l)
	{
		token = (t_token*)l->content;
		tmp = l;
		l = l->next;
		ft_strdel(&token->str);
		free(tmp);
	}
}

void	clean_sub_lst_token(t_list **lst)
{
	t_list			*l;
	t_list			*tmp;

	l = *lst;
	while (l)
	{
		tmp = l;
		l = l->next;
		clean_listd_info((t_listd_info*)tmp->content);
		free(tmp);
	}
}

void	clean_lst_tree(t_list **lst)
{
	t_list	*tmp;
	t_list	*l;

	l = *lst;
	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
	*lst = NULL;
}

int 			main(int ac, char **av)
{
	t_list			*lst_token;
	t_list			*lst_token_separate;
	t_list			*lst_tree;

	lst_token = NULL;
	lst_token_separate = NULL;
	lst_tree = NULL;
	if (ac > 1)
	{
		lst_token = lexer(av[1]);
		filter_lexer_list(&lst_token, &lst_token_separate);
		lst_tree = parser(lst_token_separate);
		clean_sub_lst_token(&lst_token_separate);
		clean_lst_tree(&lst_tree);
	}
	else
		printf("Usage: [lexer string]\n");
	return(0);
}