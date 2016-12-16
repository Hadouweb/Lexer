#include "lexer.h"

t_tree	*find_rule(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	int		i;
	t_tree	*tree;

	i = 0;
	tree = NULL;
	if (node && prev_tree && parse)
		;
	while (i < RULE_COUNT)
	{
		tree = parse->rule_func[i](parse, node, prev_tree);
		if (tree)
			return (tree);
		i++;
	}
	return (tree);
}

t_token 	*get_process(t_parse *parse, t_token **root)
{
	t_tree	*process;

	if (parse->last_process)
		return (parse->last_process);
	else if ((*root)->tree.left)
	{
		process = &(*root)->tree;
		while (process->left)
			process = process->left;
		return (PTR_NODE(process, t_token, tree));
	}
	return (*root);
}

void	add_instr(t_parse *parse, t_token **root)
{
	t_link		*l;
	t_token		*token;
	t_token		*process;
	t_tree		*cur_tree;

	if (parse->stack && parse->stack->head)
	{
		process = get_process(parse, root);
		l = parse->stack->head;
		cur_tree = &process->tree;
		while (l)
		{
			token = PTR_NODE(l, t_token, l_stack);
			cur_tree = ft_tree_add(cur_tree, TREE_LEFT, &token->tree);
			l = l->next;
		}
	}
	clean_stack(&parse->stack);
}

t_tree	*default_tree(t_parse *parse)
{
	t_link		*l;
	t_tree		*root;
	t_token		*token;

	root = NULL;
	if (parse->stack && parse->stack->head)
	{
		l = parse->stack->head;
		token = PTR_NODE(l, t_token, l_stack);
		root = &token->tree;
		parse->stack->head = l->next;
	}
	add_instr(parse, &token);
	return (root);
}

t_tree	*make_tree(t_parse *parse, t_list *list)
{
	t_link		*l;
	t_tree		*root;
	t_tree		*branch;
	t_token		*cur_token;

	l = list->head;
	root = NULL;
	while (l)
	{
		cur_token = PTR_NODE(l, t_token, link);
		branch = find_rule(parse, &l, root);
		if (branch == NULL)
			ft_list_push_back(&parse->stack, &cur_token->l_stack);
		else
		{
			root = branch;
			cur_token = PTR_NODE(root, t_token, tree);
			add_instr(parse, &cur_token);
		}
		if (l)
			l = l->next;
	}
	if (root)
	{
		cur_token = PTR_NODE(root, t_token, tree);
		add_instr(parse, &cur_token);
	}
	else
		return (default_tree(parse));

	clean_stack(&parse->stack);
	return (root);
}

void	for_each_cmd(t_parse *parse, t_list *list)
{
	t_link		*l;
	t_list		*sub_list;
	t_tree		*root;

	l = list->head;
	while (l)
	{
		parse->last_process = NULL;
		sub_list = PTR_NODE(l, t_list, link);
		root = make_tree(parse, sub_list);
		ft_list_push_back(&parse->list_tree, &root->link);
		//ft_tree_preorder(&root->tree, debug_print_token_tree);
		l = l->next;
	}
	//ft_putstr("------------------- AST -------------------\n");
	//ft_tree_preorder(root, debug_print_token_node);
}

void	update_tk_context(void *node)
{
	t_token		*token;
	t_token		*token_parent;

	token = PTR_NODE(node, t_token, tree);
	if (token->tree.parent)
	{
		token_parent = PTR_NODE(token->tree.parent, t_token, tree);
		if (token_parent->tk == TK_GREATAND)
			token->tk = TK_FD;
	}
}

void	for_each_tree(t_list *list)
{
	t_link	*l;
	t_tree	*root;

	l = list->head;
	while (l)
	{
		root = PTR_NODE(l, t_tree, link);
		ft_tree_postorder(root, update_tk_context);
		l = l->next;
	}
}

void	parser(t_parse *parse, t_list *list)
{
	init_parser(parse);
	if (list)
	{
		for_each_cmd(parse, list);
		//for_each_tree(parse->list_tree);
	}
}