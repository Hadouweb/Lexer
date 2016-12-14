#include "lexer.h"

t_tree	*find_rule(t_parse *parse, t_link **node, t_tree *prev_tree)
{
	int		i;
	t_tree	*tree;

	i = 0;
	tree = NULL;
	while (i < RULE_COUNT)
	{
		tree = parse->rule_func[i](parse, node, prev_tree);
		if (tree)
			return (tree);
		i++;
	}
	return (tree);
}

char 	*get_concat_str_stack(t_parse *parse, t_tree **root)
{
	t_link		*l;
	char 		*str;

	str = NULL;
	if (parse->stack && parse->stack->head)
	{
		l = parse->stack->head;
		if (parse->last_process)
			str = ft_strdup(((t_token*)parse->last_process)->str);
		else if ((*root)->left)
			str = ft_strdup(((t_token*)(*root)->left)->str);
		else
		{
			str = ft_strdup(((t_token*)l)->str);
			l = l->next;
		}
		//printf("__ %s\n", str);
		while (l)
		{
			str = ft_strjoin_free(str, " ", 1);
			str = ft_strjoin_free(str, ((t_token*)l)->str, 1);
			l = l->next;
		}
	}
	return (str);
}

void	add_instr(t_parse *parse, t_tree **root)
{
	char 			*str;
	t_token			instr;

	if (parse->stack && parse->stack->head)
	{
		str = get_concat_str_stack(parse, root);
		//printf("%s\n", str);

		if (parse->last_process)
		{
			//debug_print_token_node(parse->last_process);
			ft_strdel(&((t_token *)parse->last_process)->str);
			((t_token *) parse->last_process)->str = str;
		}
		else if ((*root)->left)
		{
			//debug_print_token_node(parse->last_process);
			ft_strdel(&((t_token *)(*root)->left)->str);
			((t_token *)(*root)->left)->str = str;
		}
		else
		{
			instr.str = str;
			instr.tk = TK_STR;
			//ft_tree_add_alloc(*root, TREE_LEFT, &instr, sizeof(t_token));
		}
	}
	clean_stack(&parse->stack);
}

t_tree	*make_tree(t_parse *parse, t_list *list)
{
	t_link		*l;
	t_tree		*root;
	t_tree		*branch;

	l = list->head;
	root = NULL;
	while (l)
	{
		branch = find_rule(parse, &l, root);
		if (branch == NULL)
			;//ft_listd_pushback(&parse->stack, l->content, l->content_size);
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
	if (root) {
		//printf("Final instr\n");
		//ft_listd_print(parse->stack, debug_print_token, 0);
		add_instr(parse, &root);
	}
	else
		clean_stack(&parse->stack);
	return (root);
}

void	for_each_cmd(t_parse *parse, t_list *list)
{
	t_tree		*root;
	t_link		*l;

	l = list->head;
	while (l)
	{
		root = make_tree(parse, (t_list*)l);
		//ft_listpush_back(&parse->list_tree, root, sizeof(t_tree));
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
		debug_print_list_sep(list);
		for_each_cmd(parse, list);
	}
}