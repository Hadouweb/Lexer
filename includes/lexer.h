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
	TK_NAME,
	TK_NMBR,
	TK_ASSN,	// '='
	TK_WSPC,	// ' '
	TK_SCOL,	// ';'
	TK_COUNT,
	TK_BEG,
	TK_END,
};

enum	e_sts
{
	STS_ACCEPT,
	STS_REJECT,
	STS_HUNGRY,
};

enum	e_lex
{
	LEX_OK,
	LEX_NOMEM,
	LEX_UNKNOWN_TOKEN,
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
	t_listd_info	*lst_token;
	enum e_sts		(*token_func[TK_COUNT])(char, unsigned int*);
}					t_lex;

void				lex(char *str);
void				init_sts(t_status *status);
void				debug_print_status(t_status *status);
void				debug_print_state(unsigned int *state);
void				debug_print_lst_token(void *content);
enum e_sts			tk_name(char c, unsigned int *state);
enum e_sts			tk_nmbr(char c, unsigned int *state);
enum e_sts			tk_assn(char c, unsigned int *state);
enum e_sts			tk_wspc(char c, unsigned int *state);
enum e_sts			tk_scol(char c, unsigned int *state);
void				init_sts(t_status *status);
void				init_token_func(t_lex *lex);
void				init_lexer(t_lex *lex, char *str);
void				push_token(t_lex *lex, enum e_tk tk);
int					find_token_substr(t_lex *lex);
void				next_char_substr(t_lex *lex);
enum e_tk			end_substr(t_lex *lex);
enum e_lex			last_substr(t_lex *lex);
enum e_lex			main_loop_lex(t_lex *lex);

#endif
