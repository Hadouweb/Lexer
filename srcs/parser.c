#include "lexer.h"

t_tree	*find_rule(t_parse *parse, t_listd **node)
{
	int		i;
	t_tree	*root;

	i = 0;
	root = NULL;
	while (i < RULE_COUNT)
	{
		root = parse->rule_func[i](node);
		if (root)
			return (root);
		i++;
	}
	return (root);
}

void	add_instr(t_parse *parse, t_tree **root)
{
	t_listd			*l;
	t_tree_token	instr;

	if (parse->stack && parse->stack->beg)
	{
		l = parse->stack->beg;
		instr.str = ft_strdup(((t_tree_token*)l->content)->str);
		l = l->next;
		while (l)
		{
			instr.str = ft_strjoin_free_s1(instr.str, " ");
			instr.str = ft_strjoin_free_s1(instr.str, ((t_tree_token*)l->content)->str);
			l = l->next;
		}
		instr.tk = TK_STR;
		ft_tree_add(*root, TREE_LEFT, &instr, sizeof(t_tree_token));
	}
	//clean_lst_token(parse->stack);
	//parse->stack = NULL;
}

t_tree	*make_tree(t_parse *parse, t_listd_info *lst)
{
	t_listd		*l;
	t_tree		*root;
	t_tree		*tmp;

	l = lst->beg;
	root = NULL;
	while (l)
	{
		tmp = find_rule(parse, &l);
		if (tmp == NULL)
			ft_lstd_pushback(&parse->stack, l->content, l->content_size);
		else
			root = tmp;
		if (l)
			l = l->next;
	}
	add_instr(parse, &root);
	return (root);
}

void	for_each_cmd(t_parse *parse, t_list *l)
{
	t_tree		*root;

	while (l)
	{
		root = make_tree(parse, (t_listd_info*)l->content);
		l = l->next;
	}
	ft_putstr("------------------- AST -------------------\n");
	ft_tree_preorder(root, debug_print_token_node);
}

t_tree	*parser(t_list *lst)
{
	t_parse		parse;

	init_parser(&parse);
	if (lst)
	{
		debug_print_lst_sep(lst);
		for_each_cmd(&parse, lst);
	}

	//debug_all_sub_tree(parse.lst_sub_tree);

	return (parse.root);
}