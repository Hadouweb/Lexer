#include "lexer.h"

t_tree		*get_right_node(t_tree *root)
{
	while (root->right)
		root = root->right;
	return (root);
}

void		update_tree(t_tree *node)
{
	if (node->right)
	{
		node->right->parent = node;
		node->right->depth = node->depth + 1;
	}
	if (node->left)
	{
		node->left->parent = node;
		node->left->depth = node->depth + 1;
	}
}

void		merge_tree(t_tree *prev_tree, t_tree **cur_tree)
{
	//printf("------------------- prev_tree -------------------\n");
	//ft_tree_preorder(prev_tree, debug_print_token_node);
	//printf("-------------------  cur_tree -------------------\n");
	//ft_tree_preorder(*cur_tree, debug_print_token_node);
	t_tree	*right_node;

	right_node = get_right_node(prev_tree);
	right_node->right = *cur_tree;
	*cur_tree = prev_tree;
	ft_tree_preorder(*cur_tree, update_tree);
}

t_tree		*rule_great(t_listd **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			new_token;
	t_listd			*n;

	root = NULL;
	n = *node;
	token = (t_token*)n->content;

	//if (prev_tree)
	//	ft_tree_preorder(prev_tree, debug_print_token_node);

	if (token->tk == TK_GREAT)
	{
		root = ft_tree_new_alloc(token, sizeof(t_token));
		((t_token*)root->content)->str = ft_strdup(token->str);
		if (n->next != NULL)
		{
			new_token.str = ft_strdup(((t_token *) (*node)->next->content)->str);
			new_token.tk = ((t_token *) (*node)->next->content)->tk;
			ft_tree_add_alloc(root, TREE_RIGHT, &new_token, sizeof(t_token));
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
		*node = (*node)->next;
	}
	return (root);
}