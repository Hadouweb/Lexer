#include "lexer.h"

t_token	*find_rule(t_parse *parse, t_link **node, t_token *prev_tree)
{
	int		i;
	t_token	*tree;

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
	if (parse->last_process)
		return (parse->last_process);
	else if ((*root)->tree.left)
		return (PTR_NODE((*root)->tree.left, t_token, tree));
	return (*root);
}

void	add_instr(t_parse *parse, t_token **root)
{
	t_link		*l;
	t_token		*token;
	t_token		*process;

	if (parse->stack && parse->stack->head)
	{
		process = get_process(parse, root);
		l = parse->stack->head;
		while (l)
		{
			token = PTR_NODE(l, t_token, l_stack);
			ft_tree_add(&process->tree, TREE_LEFT, &token->tree);
			l = l->next;
		}
	}
	clean_stack(&parse->stack);
}

t_token	*make_tree(t_parse *parse, t_list *list)
{
	t_link		*l;
	t_token		*root;
	t_token		*branch;
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
			add_instr(parse, &root);
		}
		if (l)
			l = l->next;
	}
	//ft_putstr("STACK\n");
	//debug_print_token_node(parse->last_process);
	//ft_listd_print(parse->stack, debug_print_token, 0);
	if (root)
	{
		//ft_tree_preorder(&root->tree, debug_print_token_tree);
		//printf("Final instr\n");
		//ft_listd_print(parse->stack, debug_print_token, 0);
		//add_instr(parse, &root);
	}
	else
		clean_stack(&parse->stack);
	return (root);
}

void	for_each_cmd(t_parse *parse, t_list *list)
{
	t_link		*l;
	t_list		*sub_list;
	t_token		*root;

	l = list->head;
	while (l)
	{
		sub_list = PTR_NODE(l, t_list, link);
		root = make_tree(parse, sub_list);
		ft_list_push_back(&parse->list_tree, &root->link);
		//ft_tree_preorder(&root->tree, debug_print_token_tree);
		l = l->next;
	}
	//ft_putstr("------------------- AST -------------------\n");
	//ft_tree_preorder(root, debug_print_token_node);
}

void	parser(t_parse *parse, t_list *list)
{
	init_parser(parse);
	if (list)
	{
		for_each_cmd(parse, list);
	}
}