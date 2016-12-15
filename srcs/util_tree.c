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

void		merge_tree(t_token *prev_tree, t_token **cur_tree)
{
	//printf("------------------- prev_tree -------------------\n");
	//ft_tree_preorder(prev_tree, debug_print_token_node);
	//printf("-------------------  cur_tree -------------------\n");
	//ft_tree_preorder(*cur_tree, debug_print_token_node);
	t_tree	*right_node;

	right_node = get_right_node(&prev_tree->tree);
	right_node->right = &(*cur_tree)->tree;
	(*cur_tree)->tree = prev_tree->tree;
	ft_tree_preorder(&(*cur_tree)->tree, update_tree);
}