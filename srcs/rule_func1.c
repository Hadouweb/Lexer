#include "lexer.h"

t_tree		*rule_great(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			*next_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link);
	next_token = PTR_NODE(token->link.next, t_token, link);
	if (token->tk == TK_GREAT)
	{
		if (parse)
			;
		root = &token->tree;
		if (next_token != NULL)
		{
			next_token->tk = TK_FILE;
			ft_tree_add(root, TREE_RIGHT, &next_token->tree);
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
		*node = (*node)->next;
	}
	return (root);
}

t_tree		*rule_dgreat(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			*next_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link);
	next_token = PTR_NODE(token->link.next, t_token, link);
	if (token->tk == TK_DGREAT)
	{
		if (parse)
			;
		root = &token->tree;
		if (next_token != NULL)
		{
			next_token->tk = TK_FILE;
			ft_tree_add(root, TREE_RIGHT, &next_token->tree);
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
		*node = (*node)->next;
	}
	return (root);
}

t_tree		*rule_greatand(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			*next_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link);
	next_token = PTR_NODE(token->link.next, t_token, link);
	if (token->tk == TK_DGREAT)
	{
		if (parse)
			;
		root = &token->tree;
		if (next_token != NULL)
		{
			next_token->tk = TK_FILE;
			ft_tree_add(root, TREE_RIGHT, &next_token->tree);
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
	t_token			*next_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link);
	next_token = PTR_NODE(token->link.next, t_token, link);
	if (token->tk == TK_GREATAND)
	{
		if (parse)
			;
		root = &token->tree;
		if (next_token != NULL)
		{
			next_token->tk = TK_FILE;
			ft_tree_add(root, TREE_RIGHT, &next_token->tree);
			*node = (*node)->next;
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
	}
	return (root);
}

t_tree		*rule_dless(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	t_tree			*root;
	t_token			*token;
	t_token			*next_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link);
	next_token = PTR_NODE(token->link.next, t_token, link);
	if (token->tk == TK_DLESS)
	{
		if (parse)
			;
		root = &token->tree;
		if (next_token != NULL)
		{
			next_token->tk = TK_HEREDOC;
			ft_tree_add(root, TREE_RIGHT, &next_token->tree);
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
	t_tree			*next_tree;
	t_token			*token;
	t_token			*next_token;
	t_token			*prev_token;

	root = NULL;
	token = PTR_NODE(*node, t_token, link);
	next_token = PTR_NODE(token->link.next, t_token, link);
	prev_token = PTR_NODE(token->link.prev, t_token, link);
	if (token->tk == TK_PIPE)
	{
		root = &token->tree;
		if (next_token != NULL)
		{
			if (prev_tree)
				add_instr(parse, &prev_token);
			else
				add_instr(parse, &token);
			next_tree = ft_tree_add(root, TREE_RIGHT, &next_token->tree);
			parse->last_process = PTR_NODE(next_tree, t_token, tree);
			*node = (*node)->next;
		}
		if (prev_tree)
			merge_tree(prev_tree, &root);
	}
	return (root);
}