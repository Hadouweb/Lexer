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

void	clean_stack(t_listd_info **stack)
{
	t_listd		*l;
	t_listd		*tmp;

	if ((*stack) == NULL)
		return ;
	l = (*stack)->beg;
	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
	*stack = NULL;
}

t_tree	*create_branch(t_parse *parse, t_token *token_node)
{
	if (parse)
		;
	printf("NICE I'M HERE %s [%s] [%s]\n", debug_get_token_name(token_node->tk), token_node->beg, token_node->end);

	t_tree	*root;

	root = ft_tree_new(token_node, sizeof(t_token));

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
	clean_stack(&parse->stack);

	ft_tree_preorder(root, debug_print_token_node);
	return (root);
}

void	add_on_stack(t_parse *parse, t_listd *node)
{
	if (parse && node)
		;
	ft_lstd_pushback(&parse->stack, node->content, node->content_size);
}

void	parse_each_node(t_listd_info *lst, t_parse *parse)
{
	t_listd		*l;
	t_tree		*sub_tree;

	l = lst->beg;
	l = l->next; // Skip beg
	while (l)
	{
		sub_tree = NULL;
		if (match_rule(parse, (t_token*)l->content))
			sub_tree = create_branch(parse, (t_token*)l->content);
		else
			add_on_stack(parse, l);
		//printf("STACK\n");
		//ft_lstd_print(parse->stack, debug_print_lst_token, 0);
		l = l->next;
	}
}

t_tree	*parser(t_listd_info *lst)
{
	t_parse		parse;

	init_parser(&parse);
	ft_lstd_print(lst, debug_print_lst_token, 0);
	parse_each_node(lst, &parse);

	return (parse.root);
}