#include "lexer.h"

void	clean_lst_token(t_listd_info *token_lst)
{
	t_listd		*l;
	t_listd		*tmp;

	if (token_lst == NULL)
		return ;
	l = token_lst->beg;
	while (l)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
}