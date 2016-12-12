#include "lexer.h"

void	clean_lst_token(t_list **lst)
{
	t_list		*tmp;
	t_token		*token;
	t_list		*l;

	l = *lst;
	while (l)
	{
		tmp = l;
		token = (t_token*)l->content;
		l = l->next;
		ft_strdel(&token->str);
		free(tmp->content);
		free(tmp);
	}
	//free(*lst);
	//*lst = NULL;
}

void	clean_tree_token(t_tree *node)
{
	t_token		*token = NULL;

	token = (t_token*)node->content;
	free(token->str);
	free(node->content);
	free(node);
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
		ft_tree_postorder((t_tree*)tmp->content, clean_tree_token);
		//free(tmp->content);
		//free(tmp);
	}
	free(*lst);
	*lst = NULL;
}

void	clean_stack(t_listd_info **listd)
{
	t_listd		*l;
	t_listd		*tmp;
	t_token		*token;

	if (*listd == NULL)
		return ;
	l = (*listd)->beg;
	while (l)
	{
		token = (t_token*)l->content;
		tmp = l;
		l = l->next;
		free(tmp);
	}
	free(*listd);
	*listd = NULL;
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
		free(tmp->content);
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
		free(tmp->content);
		free(tmp);
	}
}
