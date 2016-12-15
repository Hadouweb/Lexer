#include "lexer.h"

void	clean_tree_token(void *node)
{
	t_token	*token;

	token = PTR_NODE(node, t_token, tree);
	//free(token->str);
	//free(token);
}

void	clean_list_tree(t_list **list)
{
	t_link	*l;
	t_token	*token;

	token = PTR_NODE((*list)->head, t_token, link_tmp);
	l = &token->link_tmp;
	while (l)
	{
		token = PTR_NODE(l, t_token, link_tmp);
		l = l->next;
		ft_tree_postorder(&token->tree, clean_tree_token);
	}
	free(*list);
	*list = NULL;
}

void	clean_stack(t_list **list)
{
	t_link	*tmp;
	t_token	*token;
	t_link	*l;

	token = PTR_NODE((*list)->head, t_token, link_tmp);
	l = &token->link_tmp;
	while (l)
	{
		tmp = l;
		l = l->next;
		tmp->next = NULL;
		tmp->next = NULL;
	}
	free(*list);
	*list = NULL;
}

void	clean_list_token(t_list **list)
{
	t_link		*l;
	t_token		*token;

	l = (*list)->head;
	while (l)
	{
		token = PTR_NODE(l, t_token, link);
		l = l->next;
		ft_strdel(&token->str);
		free(token);
	}
	free(*list);
	*list = NULL;
}

void	clean_sub_list(t_list **list)
{
	t_link		*l;
	t_list		*sub_list;

	l = (*list)->head;
	while (l)
	{
		sub_list = PTR_NODE(l, t_list, link);
		l = l->next;
		free(sub_list);
	}
	free(*list);
	*list = NULL;
}