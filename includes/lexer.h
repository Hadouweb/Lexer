/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:42:25 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/23 12:42:26 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft.h"

enum	e_tk
{
	TK_BEG,
	TK_SPC,
	TK_COUNT,
};

enum	e_sts
{
	STS_ACCEPT,
	STS_REJECT,
	STS_HUNGRY,
};

typedef struct		s_token
{
	char			*beg;
	char			*end;
	enum e_tk		tk;
}					t_token;

typedef struct		s_status
{
	unsigned int	prev;
	unsigned int	curr;
}					t_status;

typedef struct		s_lex
{
	char			*nbeg;
	char			*nend;
	t_status		status[TK_COUNT];
	unsigned int	state[TK_COUNT];
	t_token			*token;
	unsigned int	ntoken;
	t_listd			*lst_token;
	enum e_sts		(*token_func[TK_COUNT])(unsigned int, unsigned int);
}					t_lex;

void				lex(char *str);
void				init_sts(t_status *status);
void				debug_print_status(t_status *status);
void				debug_print_state(unsigned int *state);
void				debug_print_lst_token(void *content);
enum e_sts			tk_name(unsigned int c, unsigned int s);
enum e_sts			tk_spc(unsigned int c, unsigned int s);
void				init_sts(t_status *status);
void				init_token_func(t_lex *lex);
void				init_lexer(t_lex *lex, char *str);
void				push_token(t_lex *lex, enum e_tk tk);

#endif
