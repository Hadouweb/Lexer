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

int				find_token_substr(t_lex *lex)
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
	return (find);
}

void			next_char_substr(t_lex *lex)
{
	int 	i;

	i = 0;
	lex->nend++;
	while (i < TK_COUNT)
	{
		lex->status[i].prev = lex->status[i].curr;
		i++;
	}
}

enum e_tk		end_substr(t_lex *lex)
{
	int 	i;
	int 	accepted_token;

	i = 0;
	accepted_token = TK_COUNT;
	while (i < TK_COUNT)
	{
		if (lex->status[i].prev == STS_ACCEPT)
			accepted_token = i;
		lex->status[i].prev = STS_HUNGRY;
		lex->status[i].curr = STS_REJECT;
		i++;
	}
	return (accepted_token);
}

enum e_lex		last_substr(t_lex *lex)
{
	int 	accepted_token;

	accepted_token = end_substr(lex);
	push_token(lex, accepted_token);
	if (accepted_token == TK_COUNT)
		return (LEX_UNKNOWN_TOKEN);
	push_token(lex, TK_END);
	return (LEX_OK);
}

enum e_lex		main_loop_lex(t_lex *lex)
{
	int 	tk_find;
	int 	accepted_token;

	while (*lex->nend)
	{
		tk_find = find_token_substr(lex);
		if (tk_find)
			next_char_substr(lex);
		else
		{
			accepted_token = end_substr(lex);
			push_token(lex, accepted_token);
			if (accepted_token == TK_COUNT)
			{
				((t_token*)lex->lst_token->end)->end++;
				return (LEX_UNKNOWN_TOKEN);
			}
			lex->nbeg = lex->nend;
		}
		lex->nend++;
	}
	return (last_substr(lex));
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
