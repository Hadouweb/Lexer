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

char 	*get_concat_str_stack(t_parse *parse, t_token **root)
{
	t_link		*l;
	char 		*str;

	l = parse->stack->head;
	if (parse->last_process)
		str = ft_strdup((parse->last_process)->str);
	else if ((*root)->tree.left)
		str = ft_strdup((PTR_NODE((*root)->tree.left, t_token, tree))->str);
	else
	{
		str = ft_strdup((PTR_NODE(l, t_token, link))->str);
		l = l->next;
	}
	//printf("__ %s\n", str);
	while (l)
	{
		str = ft_strjoin_free(str, " ", 1);
		str = ft_strjoin_free(str,
		(PTR_NODE(l, t_token, link))->str, 1);
		l = l->next;
	}
	return (str);
}

void	add_instr(t_parse *parse, t_token **root)
{
	char 			*str;
	t_token			*instr;

	if (parse->stack && parse->stack->head)
	{
		str = get_concat_str_stack(parse, root);
		//printf("__%s\n", str);

		if (parse->last_process)
		{
			//debug_print_token_node(parse->last_process);
			ft_strdel(&parse->last_process->str);
			parse->last_process->str = str;
		}
		else if ((*root)->tree.left)
		{
			//debug_print_token_node(parse->last_process);
			ft_strdel(&(PTR_NODE((*root)->tree.left, t_token, tree))->str);
			(PTR_NODE((*root)->tree.left, t_token, tree))->str = str;
		}
		else
		{
			instr = make_token(str, TK_STR);
			ft_tree_add(&(*root)->tree, TREE_LEFT, &instr->tree);
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
		cur_token = PTR_NODE(l, t_token, link_tmp);
		branch = find_rule(parse, &l, root);
		if (branch == NULL)
			ft_list_push_back(&parse->stack, &cur_token->link);
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
		ft_list_push_back(&parse->list_tree, &root->link_tmp);
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