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
	TK_WORD,
	TK_OPT,
	TK_AND_IF,		// &&
	TK_OR_IF,		// ||
	TK_DLESS,		// <<
	TK_DGREAT,		// >>
	TK_LESSAND,		// <&
	TK_GREATAND,	// >&
	TK_LESSGREAT,	// <>
	TK_CLOBBER,		// >|
	TK_WSPC,		// ' '
	TK_PIPE,		// |
	TK_SCOL,		// ;
	TK_AND,			// &
	TK_LESS,		// <
	TK_GREAT,		// >
	TK_COUNT,
	TK_BEG,
	TK_END,
};

enum	e_rule
{
	RULE_INSTR,
	RULE_WORD,
	RULE_OPT,
	RULE_GREAT,		// >
	RULE_COUNT,
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

#define RULE_COUNT 1

typedef struct 		s_parse
{
	t_listd_info	*stack;
	t_listd_info	*lst_sub_tree;
	t_tree			*root;
	int				(*rule_func[RULE_COUNT])(t_token *token_node);
}					t_parse;

void				clean_lst_token(t_listd_info *token_lst);

t_listd_info		*lexer(char *str);
void				init_sts(t_status *status);
void				debug_print_status(t_status *status);
void				debug_print_state(unsigned int *state);
void				debug_print_lst_token(void *content);
void				debug_print_token_node(t_tree *node);
void				debug_all_sub_tree(t_listd_info *lst);
void				debug_print_lst_sep(t_list *l);

enum e_sts			tk_generic_1(char c, unsigned int *state, char *str);
enum e_sts			tk_generic_2(char c, unsigned int *state, char *str);

enum e_sts			tk_word(char c, unsigned int *state);
enum e_sts			tk_opt(char c, unsigned int *state);
enum e_sts			tk_wspc(char c, unsigned int *state);
enum e_sts			tk_pipe(char c, unsigned int *state);
enum e_sts			tk_scol(char c, unsigned int *state);
enum e_sts			tk_and(char c, unsigned int *state);
enum e_sts			tk_and_if(char c, unsigned int *state);
enum e_sts			tk_or_if(char c, unsigned int *state);
enum e_sts			tk_dless(char c, unsigned int *state);
enum e_sts			tk_dgreat(char c, unsigned int *state);
enum e_sts			tk_lessand(char c, unsigned int *state);
enum e_sts			tk_greatand(char c, unsigned int *state);
enum e_sts			tk_lessgreat(char c, unsigned int *state);
enum e_sts			tk_clobber(char c, unsigned int *state);
enum e_sts			tk_less(char c, unsigned int *state);
enum e_sts			tk_great(char c, unsigned int *state);

void				init_sts(t_status *status);
void				init_token_func(t_lex *lex);
void				init_lexer(t_lex *lex, char *str);
void				push_token(t_lex *lex, enum e_tk tk);
int					find_token_substr(t_lex *lex);
void				next_char_substr(t_lex *lex);
enum e_tk			end_substr(t_lex *lex);
enum e_lex			last_substr(t_lex *lex);
enum e_lex			main_loop_lex(t_lex *lex);
const char* 		debug_get_token_name(enum e_tk tk);


t_tree				*parser(t_list *lst);

void				init_rule_func(t_parse *parse);
void				init_parser(t_parse *parse);

int 				rule_great(t_token *token_node);

#endif
