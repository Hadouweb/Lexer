#include "lexer.h"

t_tree		*rule_great(t_listd *node)
{
	t_tree			*root;
	t_tree_token	*token;
	t_tree			*ref_node;

	root = NULL;
	token = (t_tree_token*)node->content;
	if (token->tk == TK_GREAT)
	{
		root = ft_tree_new(token, sizeof(t_tree_token));
		ref_node = root;
		while (node->prev)
		{
			ref_node = ft_tree_add(ref_node, TREE_LEFT,
			node->prev->content, node->prev->content_size);
			node = node->prev;
		}
	}
	return (root);
}