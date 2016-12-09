#include "lexer.h"

int		match_rule(t_parse *parse, t_token *token_node)
{
	int		i;

	i = 0;
	//printf("match_rule\n");
	while (i < RULE_COUNT)
	{
		if (parse->rule_func[i](token_node))
			return (1);
		i++;
	}
	return (0);
}

t_tree	*create_branch(t_parse *parse, t_token *token_node)
{
	if (parse)
		;
	printf("NICE I'M HERE %s [%s] [%s]\n",
	debug_get_token_name(token_node->tk), token_node->beg, token_node->end);
	return (NULL);
}

void	parse_each_node(t_listd_info *lst, t_parse *parse)
{
	t_listd		*l;
	t_tree		*sub_tree;

	l = lst->beg;
	while (l)
	{
		sub_tree = NULL;
		if (match_rule(parse, (t_token*)l->content))
			sub_tree = create_branch(parse, (t_token*)l->content);
		else
			;//add on stack
		l = l->next;
	}
}

t_tree	*parser(t_listd_info *lst)
{
	t_parse		parse;

	init_rule_func(&parse);
	ft_lstd_print(lst, debug_print_lst_token, 0);

	parse_each_node(lst, &parse);

	return (parse.root);
}