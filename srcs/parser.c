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

void	clean_stack(t_listd_info **listd)
{
	t_listd		*l;
	t_listd		*tmp;
	t_token		*token;

	l = (*listd)->beg;
	while (l)
	{
		token = (t_token*)l->content;
		tmp = l;
		l = l->next;
		free(tmp);
	}
	free(*listd);
	*listd = NULL;
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

void	clean_tree_token(t_tree *node)
{
	t_token		*token = NULL;

	token = (t_token*)node->content;
	free(token->str);
	free(node->content);
	free(node);
}

void	clean_lst_tree(t_list **lst)
{
	t_list	*tmp;
	t_list	*l;

	l = *lst;
	while (l)
	{
		tmp = l;
		l = l->next;
		ft_tree_postorder((t_tree*)tmp->content, clean_tree_token);
		//free(tmp->content);
		//free(tmp);
	}
	free(*lst);
	*lst = NULL;
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
		{
			ft_tree_postorder(root, clean_tree_token); //Exemple ls > test > test2 alors free tree > ls test pour garder > ls test2
			root = tmp;
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