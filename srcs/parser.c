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

void	push_stack(t_list **stack, t_token *data)
{
	t_stack		*stack_token;

	stack_token = (t_stack*)ft_memalloc(sizeof(t_stack));
	if (stack_token == NULL)
		return ;
	stack_token->data = data;
	ft_list_push_back(stack, &stack_token->link);
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
			push_stack(&parse->stack, cur_token);
		else
		{
			root = branch;
			break ;
			//add_instr(parse, &root);
		}
		if (l)
			l = l->next;
	}
	//ft_putstr("STACK\n");
	//debug_print_token_node(parse->last_process);
	//ft_listd_print(parse->stack, debug_print_token, 0);
	if (root)
	{
		ft_tree_preorder(&root->tree, debug_print_token_tree);
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

	l = list->head;
	while (l)
	{
		make_tree(parse, (t_list*)l);
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