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

void			init_sts(t_status *status)
{
	int		i;

	i = 0;
	while (i < TK_COUNT)
	{
		status[i].prev = STS_HUNGRY;
		status[i].curr = STS_REJECT;
		i++;
	}
}

void			init_token_func(t_lex *lex)
{
	lex->token_func[0] = tk_name;
	lex->token_func[1] = tk_spc;
}

void			init_lexer(t_lex *lex, char *str)
{
	ft_bzero(lex, sizeof(t_lex));
	init_sts(lex->status);
	init_token_func(lex);
	ft_memset(lex->state, 0, sizeof(unsigned int) * TK_COUNT);
	lex->nbeg = str;
	lex->nend = str;
}

void			push_token(t_lex *lex, unsigned int tk)
{
	t_token		token;

	token.beg = ft_strdup(lex->nbeg);
	token.end = ft_strdup(lex->nend);
	token.tk = tk;
	ft_lstd_pushback(&lex->lst_token, &token, sizeof(t_token));
}

unsigned int	tk_name(unsigned int c, unsigned int s)
{
	if (c + s)
		return (1);
	return (0);
}

unsigned int	tk_spc(unsigned int c, unsigned int s)
{
	if (c + s)
		return (1);
	return (0);
}

void			update_status(t_lex *lex)
{
	int		i;

	i = 0;
	while (i < TK_COUNT)
	{
		if (lex->status[i].prev != STS_REJECT)
			lex->status[i].curr = lex->token_func[i](*lex->nend, lex->state[i]);
		i++;
	}
}

void			main_loop_lex(t_lex *lex)
{
	while (*lex->nend)
	{
		update_status(lex);
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
