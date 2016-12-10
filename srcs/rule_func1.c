#include "lexer.h"

t_tree		*rule_great(t_listd **node)
{
	t_tree			*root;
	t_tree_token	*token;
	t_listd			*n;

	root = NULL;
	n = *node;
	token = (t_tree_token*)n->content;
	if (token->tk == TK_GREAT)
	{
		root = ft_tree_new(token, sizeof(t_tree_token));
		if (n->next == NULL)
			;// ls > A Revoir
		ft_tree_add(root, TREE_RIGHT, (*node)->next->content, (*node)->next->content_size);
		*node = (*node)->next;
	}
	return (root);
}