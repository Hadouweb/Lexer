#include "lexer.h"

t_tree	*find_rule(t_parse *parse, t_listd **node, t_tree *prev_tree)
{
	int		i;
	t_tree	*tree;

	i = 0;
	tree = NULL;
	while (i < RULE_COUNT)
	{
		tree = parse->rule_func[i](node, prev_tree);
		if (tree)
			return (tree);
		i++;
	}
	return (tree);
}

void	add_instr(t_parse *parse, t_tree **root)
{
	t_listd			*l;
	t_token			instr;

	if (parse->stack && parse->stack->beg)
	{
		l = parse->stack->beg;
		instr.str = ft_strdup(((t_token*)l->content)->str);
		l = l->next;
		while (l)
		{
			instr.str = ft_strjoin_free_s1(instr.str, " ");
			instr.str = ft_strjoin_free_s1(instr.str, ((t_token*)l->content)->str);
			l = l->next;
		}
		instr.tk = TK_STR;
		ft_tree_add_alloc(*root, TREE_LEFT, &instr, sizeof(t_token));
	}
}

t_tree	*make_tree(t_parse *parse, t_listd_info *lst)
{
	t_listd		*l;
	t_tree		*root;
	t_tree		*branch;

	l = lst->beg;
	root = NULL;
	while (l)
	{
		branch = find_rule(parse, &l, root);
		if (branch == NULL)
			ft_lstd_pushback(&parse->stack, l->content, l->content_size);
		else
		{
			root = branch;
		}
		if (l)
			l = l->next;
	}
	if (root)
		add_instr(parse, &root);
	clean_stack(&parse->stack);
	return (root);
}

void	for_each_cmd(t_parse *parse, t_list *l)
{
	t_tree		*root;

	while (l)
	{
		root = make_tree(parse, (t_listd_info*)l->content);
		ft_lstpush_back(&parse->lst_tree, root, sizeof(t_tree));
		l = l->next;
	}
	//ft_putstr("------------------- AST -------------------\n");
	//ft_tree_preorder(root, debug_print_token_node);
}

void	parser(t_parse *parse, t_list *lst)
{
	init_parser(parse);
	if (lst)
	{
		debug_print_lst_sep(lst);
		for_each_cmd(parse, lst);
	}
}