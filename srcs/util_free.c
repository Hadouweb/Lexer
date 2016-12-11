#include "lexer.h"

void	clean_lst_token(t_list **lst)
{
	t_list		*tmp;
	t_token		*token;
	t_list		*l;

	l = *lst;
	while (l)
	{
		tmp = l;
		token = (t_token*)l->content;
		l = l->next;
		ft_strdel(&token->str);
		free(tmp->content);
		free(tmp);
	}
	//free(*lst);
	//*lst = NULL;
}