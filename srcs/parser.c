#include "lexer.h"

t_tree	*find_rule(t_parse *parse, t_listd *node)
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

t_tree	*make_tree(t_parse *parse, t_listd_info *lst)
{
	t_listd		*l;
	t_tree		*root;

	l = lst->beg;
	root = NULL;
	while (l)
	{
		root = find_rule(parse, l);
		if (root != NULL)
			return (root);
		l = l->next;
	}
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