/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:37:20 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/23 12:37:21 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			update_status(t_lex *lex)
{
	int		i;
	int 	find;

	i = 0;
	find = 0;
	while (i < TK_COUNT)
	{
		if (lex->status[i].prev != STS_REJECT)
			lex->status[i].curr = lex->token_func[i](*lex->nend, lex->state[i]);
		if (lex->status[i].curr != STS_REJECT)
			find = 1;
		i++;
	}
}

void			main_loop_lex(t_lex *lex)
{
	while (*lex->nend)
	{
		update_status(lex);
		/*
		if (tk_find)
			;//
		else
			;//
		*/
		lex->nend++;
	}
}

void			lex(char *str)
{
	t_lex			lex;

	init_lexer(&lex, str);
	push_token(&lex, TK_BEG);
	main_loop_lex(&lex);
	//debug_print_status(lex.status);
	//debug_print_state(lex.state);
	ft_lstd_print(lex.lst_token, debug_print_lst_token, 0);
}
