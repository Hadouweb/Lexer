#include "lexer.h"

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

void	clean_sub_list_token(t_list **list)
{
	t_link			*l;
	t_list			*tmp;

	l = (*list)->head;
	while (l)
	{
		tmp = (t_list*)l;
		l = l->next;
		clean_list_token(&tmp);
	}
	free(*list);
	*list = NULL;
}
