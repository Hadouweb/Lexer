#include "lexer.h"

void	clean_lst_token(t_list *l)
{
	t_list		*tmp;
	t_token		*token;

	while (l)
	{
		tmp = l;
		token = (t_token*)l->content;
		l = l->next;
		ft_strdel(&token->str);
		free(tmp);
	}
}