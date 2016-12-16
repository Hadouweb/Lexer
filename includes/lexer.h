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
	TK_AND_IF,		// && ok
	TK_OR_IF,		// ||
	TK_DLESS,		// << ok
	TK_DGREAT,		// >> ok
	TK_LESSAND,		// <& ok
	TK_GREATAND,	// >& ok
	TK_LESSGREAT,	// <>
	TK_CLOBBER,		// >|
	TK_WSPC,		// ' ' ok
	TK_PIPE,		// | ok
	TK_SCOL,		// ; ok
	TK_AND,			// & ok
	TK_LESS,		// < ok
	TK_GREAT,		// > ok
	TK_STR,
	TK_COUNT,
	TK_FILE,
	TK_HEREDOC,
	TK_FD,
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

typedef struct 		s_token
{
	t_link			link;
	t_link			l_stack;
	t_tree			tree;
	char 			*str;
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
	t_list			*list_token;
	t_list			*list_token_separate;
	enum e_sts		(*token_func[TK_COUNT])(char, unsigned int*);
}					t_lex;

#define RULE_COUNT 7

typedef struct 		s_parse
{
	t_list			*list_tree;
	t_list			*stack;
	t_tree			*root;
	t_token			*last_process;
	t_tree			*(*rule_func[RULE_COUNT])(struct s_parse *parse,
						t_link **node, t_tree *prev_tree);
}					t_parse;

void				clean_list_token(t_list **list);
void				clean_tree_token(void *node);
void				clean_list_tree(t_list **list);
void				clean_stack(t_list **list);
void				clean_sub_list(t_list **list);

void				lexer(t_lex *lex, char *str);
void				init_sts(t_status *status);
void				debug_print_status(t_status *status);
void				debug_print_state(unsigned int *state);
void				debug_all_sub_tree(t_list *list);
void				debug_print_list_sep(t_list *l);
void				debug_print_token_list(void *content);
void				debug_print_token_tree(void *content);
void				debug_print_list_tree(t_list *l);

enum e_sts			tk_generic_1(char c, unsigned int *state, char *str);
enum e_sts			tk_generic_2(char c, unsigned int *state, char *str);

enum e_sts			tk_str(char c, unsigned int *state);
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

t_tree				*get_right_node(t_tree *root);
void				update_tree(void *node);
void				merge_tree(t_tree *prev_tree, t_tree **cur_tree);

t_token				*make_token(char *str, enum e_tk tk);
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

void				parser(t_parse *parse, t_list *list);

t_list				*get_sub_list(t_link **l);
void				filter_lexer_list(t_list **list, t_list **list_tk_sep);

void				init_rule_func(t_parse *parse);
void				init_parser(t_parse *parse);

t_tree				*rule_great(t_parse *parse, t_link **node, t_tree *prev_tree);
t_tree				*rule_dgreat(t_parse *parse, t_link **node, t_tree *prev_tree);
t_tree				*rule_less(t_parse *parse, t_link **node, t_tree *prev_tree);
t_tree				*rule_pipe(t_parse *parse, t_link **node, t_tree *prev_tree);
t_tree				*rule_dless(t_parse *parse, t_link **node, t_tree *prev_tree);
t_tree				*rule_greatand(t_parse *parse, t_link **node, t_tree *prev_tree);
t_tree				*rule_lessand(t_parse *parse, t_link **node, t_tree *prev_tree);

char 				*get_concat_str_stack(t_parse *parse, t_token **root);
void				add_instr(t_parse *parse, t_token **root);

#endif
