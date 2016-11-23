#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft.h"

enum {
	TK_BEG,
	TK_SPC,
	TK_COUNT,
};

enum {
	STS_ACCEPT,
	STS_REJECT,
	STS_HUNGRY,
};

typedef struct 		s_token
{
	char 			*beg;
	char 			*end;
	unsigned int	tk;
}					t_token;

typedef struct		s_status
{
	unsigned int	prev;
	unsigned int	curr;
}					t_status;

typedef struct 		s_lex
{
	char 			*nbeg;
	char 			*nend;
	int 			accepted_token;
	t_status		status[TK_COUNT];
	unsigned int 	state[TK_COUNT];
	t_token			*token;
	unsigned int	ntoken;
	t_listd			*lst_token;
}					t_lex;

void	lex(char *str);
void	init_sts(t_status *status);
void	debug_print_status(t_status *status);
void	debug_print_state(unsigned int *state);
void	debug_print_lst_token(void *content);

#endif