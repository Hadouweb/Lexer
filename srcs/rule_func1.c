#include "lexer.h"

t_tree		*rule_great(t_listd **node)
{
	t_tree			*root;
	t_token			*token;
	t_token			new_token;
	t_listd			*n;

	root = NULL;
	n = *node;
	token = (t_token*)n->content;
	if (token->tk == TK_GREAT)
	{
		root = ft_tree_new_alloc(token, sizeof(t_token));
		((t_token*)root->content)->str = ft_strdup(token->str);
		if (n->next == NULL)
			return (root);
		new_token.str = ft_strdup(((t_token*)(*node)->next->content)->str);
		new_token.tk = ((t_token*)(*node)->next->content)->tk;
		ft_tree_add_alloc(root, TREE_RIGHT, &new_token, sizeof(t_token));
		*node = (*node)->next;
	}
	return (root);
}