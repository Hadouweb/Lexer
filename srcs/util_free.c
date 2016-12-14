#include "lexer.h"

void	clean_list_token(t_list **list)
{
	t_link		*tmp;
	t_token		*token;
	t_link		*l;

	l = (*list)->head;
	while (l)
	{
		tmp = l;
		token = (t_token*)l;
		l = l->next;
		ft_strdel(&token->str);
		free(tmp);
	}
	//free(*list);
	//*list = NULL;
}

void	clean_tree_token(void *node)
{
	t_tree	*n;

	n = (t_tree*)node;
	t_token		*token = NULL;

	token = (t_token*)n;
	free(token->str);
	free(n);
}

void	clean_list_tree(t_list **list)
{
	t_link	*tmp;
	t_link	*l;

	l = (*list)->head;
	while (l)
	{
		tmp = l;
		l = l->next;
		ft_tree_postorder((t_tree*)tmp, clean_tree_token);
		//free(tmp->content);
		//free(tmp);
	}
	free(*list);
	*list = NULL;
}

void	clean_stack(t_list **list)
{
	t_link		*l;
	t_link		*tmp;
	t_token		*token;

	if (*list == NULL)
		return ;
	l = (*list)->head;
	while (l)
	{
		token = (t_token*)l;
		tmp = l;
		l = l->next;
		free(tmp);
	}
	free(*list);
	*list = NULL;
}

void	clean_listd_info(t_list *list)
{
	t_link		*l;
	t_link		*tmp;
	t_token		*token;

	l = list->head;
	while (l)
	{
		token = (t_token*)l;
		tmp = l;
		l = l->next;
		ft_strdel(&token->str);
		free(tmp);
	}
}

void	clean_sub_list_token(t_list **list)
{
	t_link			*l;
	t_link			*tmp;

	l = (*list)->head;
	while (l)
	{
		tmp = l;
		l = l->next;
		clean_listd_info((t_list*)tmp);
		free(tmp);
	}
}
