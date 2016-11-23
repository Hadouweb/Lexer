#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft.h"

typedef struct		s_status
{
	unsigned int	prev;
	unsigned int	curr;
}					t_status;

enum {
	TK_BEG,
	TK_COUNT,
};

enum {
	STS_ACCEPT,
	STS_REJECT,
	STS_HUNGRY,
};

void	lex(char *str);
void	init_sts(t_status *statuses);

#endif