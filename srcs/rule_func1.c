#include "lexer.h"

t_tree		*rule_great(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			new_token;
	t_link			*n;

	root = NULL;
	n = *node;
	token = (t_token*)n;

	if (token->tk == TK_GREAT)
	{
		if (parse)
			;
		//root = ft_tree_new_alloc(token, sizeof(t_token));
		((t_token*)root)->str = ft_strdup(token->str);
		if (n->next != NULL)
		{
			new_token.str = ft_strdup(((t_token *) (*node)->next)->str);
			new_token.tk = ((t_token *) (*node)->next)->tk;
			//ft_tree_add_alloc(root, TREE_RIGHT, &new_token, sizeof(t_token));
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
		*node = (*node)->next;
	}
	return (root);
}

t_tree		*rule_less(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			new_token;
	t_link			*n;

	root = NULL;
	n = *node;
	token = (t_token*)n;

	if (token->tk == TK_LESS)
	{
		if (parse)
			;
		//root = ft_tree_new_alloc(token, sizeof(t_token));
		((t_token*)root)->str = ft_strdup(token->str);
		if (n->next != NULL)
		{
			new_token.str = ft_strdup(((t_token *) (*node)->next)->str);
			new_token.tk = ((t_token *) (*node)->next)->tk;
			//ft_tree_add_alloc(root, TREE_RIGHT, &new_token, sizeof(t_token));
			*node = (*node)->next;
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
	}
	return (root);
}

t_tree		*rule_pipe(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			new_token;
	t_link			*n;

	root = NULL;
	n = *node;
	token = (t_token*)n;

	if (token->tk == TK_PIPE)
	{
		//root = ft_tree_new_alloc(token, sizeof(t_token));
		((t_token*)root)->str = ft_strdup(token->str);
		if (n->next != NULL)
		{
			if (prev_tree)
				add_instr(parse, &prev_tree);
			else
				add_instr(parse, &root);
			new_token.str = ft_strdup(((t_token *) (*node)->next)->str);
			new_token.tk = ((t_token *) (*node)->next)->tk;
			//parse->last_process = ft_tree_add_alloc(root, TREE_RIGHT, &new_token, sizeof(t_token));
			*node = (*node)->next;
		}
		//add_instr(parse, &root);
		if (prev_tree)
			merge_tree(prev_tree, &root);
	}
	return (root);
}