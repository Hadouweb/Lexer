#include "lexer.h"

t_tree		*get_right_node(t_tree *root)
{
	while (root->right)
		root = root->right;
	return (root);
}

void		update_tree(void *node)
{
	t_tree	*n;

	n = (t_tree*)node;
	if (n->right)
	{
		n->right->parent = n;
		n->right->depth = n->depth + 1;
	}
	if (n->left)
	{
		n->left->parent = n;
		n->left->depth = n->depth + 1;
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