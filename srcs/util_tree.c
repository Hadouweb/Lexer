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