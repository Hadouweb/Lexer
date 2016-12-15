#include "lexer.h"

t_token		*rule_great(t_parse *parse, t_link **node, t_token *prev_tree)
{
	t_token			*root;
	t_token			*token;
	t_token			*next_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link_tmp);
	next_token = PTR_NODE(token->link.next, t_token, link_tmp);
	if (token->tk == TK_GREAT)
	{
		if (parse)
			;
		root = token;
		if (next_token != NULL)
			ft_tree_add(&root->tree, TREE_RIGHT, &next_token->tree);
		if (prev_tree)
			merge_tree(prev_tree, &root);
		*node = (*node)->next;
	}
	return (root);
}

/*t_token		*rule_less(t_parse *parse, t_link **node, t_token *prev_tree)
{
	t_token			*root;
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
		root->str = ft_strdup(token->str);
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

t_token		*rule_pipe(t_parse *parse, t_link **node, t_token *prev_tree)
{
	t_token			*root;
	t_token			*token;
	t_token			new_token;
	t_link			*n;

	root = NULL;
	n = *node;
	token = (t_token*)n;

	if (token->tk == TK_PIPE)
	{
		//root = ft_tree_new_alloc(token, sizeof(t_token));
		root->str = ft_strdup(token->str);
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
}*/