#include "lexer.h"

void	debug_print_status(t_status *status)
{
	int 			i;

	i = 0;
	printf("** debug_print_status **\n");
	while (i < TK_COUNT)
	{
		if (status[i].prev == STS_ACCEPT)
			printf("[%d] prev: [%s]\n", i, "STS_ACCEPT");
		else if (status[i].prev == STS_HUNGRY)
			printf("[%d] prev: [%s]\n", i, "STS_HUNGRY");
		else if (status[i].prev == STS_REJECT)
			printf("[%d] prev: [%s]\n", i, "STS_REJECT");

		if (status[i].curr == STS_ACCEPT)
			printf("[%d] curr: [%s]\n", i, "STS_ACCEPT");
		else if (status[i].curr == STS_HUNGRY)
			printf("[%d] curr: [%s]\n", i, "STS_HUNGRY");
		else if (status[i].curr == STS_REJECT)
			printf("[%d] curr: [%s]\n", i, "STS_REJECT");
		printf("____________________________\n");
		i++;
	}
}

void	debug_print_state(unsigned int *state)
{
	int 			i;

	i = 0;
	printf("** debug_print_state **\n");
	while (i < TK_COUNT)
	{
		printf("[%d] state: [%u]\n", i, state[i]);
		i++;
	}
}

void	debug_print_list_sep(t_list *list)
{
	t_link	*l;

	l = list->head;
	while (l)
	{
		ft_putstr("------------------- CMD -------------------\n");
		ft_list_print(((t_list*)l)->head, debug_print_token);
		l = l->next;
	}
}

void	debug_print_token(void *content)
{
	t_token	*token;

	token = PTR_NODE(content, t_token, link);
	ft_putstr("str : \t[");
	ft_putstr(token->str);
	ft_putstr("]\ttk : \t");
	ft_putstr(debug_get_token_name(token->tk));
	ft_putstr("\n");
}

void	debug_print_token_node(void *node)
{
	t_tree	*n;

	n = (t_tree*)node;
	if (n->parent)
	{
		ft_putstr("\033[036mparent : \033[0m[");
		ft_putstr(((t_token*)n->parent)->str);
		ft_putstr("]");
		ft_putchar('\n');
	}
	ft_putstr("\033[033mcontent : \033[0m[");
	debug_print_token(node);
	ft_putstr("]\t\033[035mdepth : \033[0m[");
	ft_putnbr(n->depth);
	ft_putstr("]");
	if (n->parent)
	{
		if (n->parent->left == node)
			ft_putstr(" LEFT");
		if (n->parent->right == node)
			ft_putstr(" RIGHT");
	}
	ft_putstr("\n\n");
}

void	debug_all_sub_tree(t_list *list)
{
	t_link		*l;
	t_tree		*sub_tree;

	if (list)
	{
		l = list->head;
		while (l)
		{
			sub_tree = (t_tree*)l;
			ft_putstr("___________________________________\n");
			ft_tree_preorder(sub_tree, debug_print_token_node);
			l = l->next;
		}
	}
}

void			debug_print_list_tree(t_list *list)
{
	t_link	*l;

	l = list->head;
	while (l)
	{
		ft_putstr("------------------- AST -------------------\n");
		ft_tree_preorder((t_tree*)l, debug_print_token_node);
		l = l->next;
	}
}

const char* debug_get_token_name(enum e_tk tk)
{
	switch (tk)
	{
		case TK_STR: return "TK_STR";
		case TK_OPT: return "TK_OPT";
		case TK_WSPC: return "TK_WSPC";
		case TK_AND_IF: return "TK_AND_IF";
		case TK_OR_IF: return "TK_OR_IF";
		case TK_DLESS: return "TK_DLESS";
		case TK_DGREAT: return "TK_DGREAT";
		case TK_LESSAND: return "TK_LESSAND";
		case TK_GREATAND: return "TK_GREATAND";
		case TK_LESSGREAT: return "TK_LESSGREAT";
		case TK_CLOBBER: return "TK_CLOBBER";
		case TK_PIPE: return "TK_PIPE";
		case TK_SCOL: return "TK_SCOL";
		case TK_AND: return "TK_AND";
		case TK_LESS: return "TK_LESS";
		case TK_GREAT: return "TK_GREAT";
		case TK_COUNT: return "TK_COUNT";
		case TK_BEG: return "TK_BEG";
		case TK_END: return "TK_END";
	}
}