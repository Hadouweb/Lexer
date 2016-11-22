#include "lexer.h"

void	init_sts(t_status *statuses)
{
	int 	i;

	i = 0;
	while (i < TK_COUNT)
	{
		statuses[i].prev = STS_HUNGRY;
		statuses[i].curr = STS_REJECT;
		i++;
	}
}

void	lex(char *str)
{
	t_status	statuses[TK_COUNT];

	init_sts(statuses);
	printf("%s\n", str);
}