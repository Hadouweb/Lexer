#include "lexer.h"

int		match_rule(t_parse *parse, t_token *token_node)
{
	int		i;

	i = 0;

	while (i < RULE_COUNT)
	{
		if (parse->rule_func[i](token_node))
			return (1);
		i++;
	}
	return (0);
}

void	add_stack_on_left(t_parse *parse, t_tree *root)
{
	t_listd	*l;
	t_tree	*cur_node;

	if (parse->stack)
	{
		l = parse->stack->beg;
		cur_node = root;
		while (l)
		{
			cur_node = ft_tree_add(cur_node, TREE_LEFT, l->content, l->content_size);
			l = l->next;
		}
	}
	clean_lst_token(parse->stack);
}

t_tree	*create_branch(t_parse *parse, t_token *token_node)
{
	//printf("NICE I'M HERE %s [%s] [%s]\n", debug_get_token_name(token_node->tk), token_node->beg, token_node->end);
	t_tree	*root;
	char 	*str;

	str = ft_strndup(token_node->beg,
	ft_strlen(token_node->beg) - ft_strlen(token_node->end));
	root = ft_tree_new(str, ft_strlen(str));
	ft_strdel(&str);

	add_stack_on_left(parse, root);

	ft_lstd_pushback(&parse->lst_sub_tree, root, sizeof(t_tree));
	// FREE
	return (root);
}

void	add_on_stack(t_parse *parse, t_token *token_node)
{
	char 	*str;

	str = ft_strndup(token_node->beg,
	ft_strlen(token_node->beg) - ft_strlen(token_node->end));
	ft_lstd_pushback(&parse->stack, str, ft_strlen(str));
	ft_strdel(&str);
}

void	parse_each_node(t_listd_info *lst, t_parse *parse)
{
	t_listd		*l;

	l = lst->beg;
	l = l->next; // Skip beg
	while (l)
	{
		if (match_rule(parse, (t_token*)l->content))
			create_branch(parse, (t_token *) l->content);
		else
			add_on_stack(parse, (t_token*)l->content);
		l = l->next;
	}
}

t_tree	*parser(t_list *lst)
{
	t_parse		parse;

	init_parser(&parse);
	if (lst)
	{
		debug_print_lst_sep(lst);
		//ft_lstd_print(lst, debug_print_lst_token, 0);
	}
	//parse_each_node(lst, &parse);

	//debug_all_sub_tree(parse.lst_sub_tree);

	return (parse.root);
}