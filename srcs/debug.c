#include "lexer.h"

void	debug_print_status(t_status *status)
{
	int 			i;

	i = 0;
	printf("** debug_print_status **\n");
	while (i < TK_COUNT)
	{
		if (status[i].prev == STS_ACCEPT)
			printf("[%d] prev: [%s]\n", i, "STS_ACCEPT");
		else if (status[i].prev == STS_HUNGRY)
			printf("[%d] prev: [%s]\n", i, "STS_HUNGRY");
		else if (status[i].prev == STS_REJECT)
			printf("[%d] prev: [%s]\n", i, "STS_REJECT");

		if (status[i].curr == STS_ACCEPT)
			printf("[%d] curr: [%s]\n", i, "STS_ACCEPT");
		else if (status[i].curr == STS_HUNGRY)
			printf("[%d] curr: [%s]\n", i, "STS_HUNGRY");
		else if (status[i].curr == STS_REJECT)
			printf("[%d] curr: [%s]\n", i, "STS_REJECT");
		printf("____________________________\n");
		i++;
	}
}

void	debug_print_state(unsigned int *state)
{
	int 			i;

	i = 0;
	printf("** debug_print_state **\n");
	while (i < TK_COUNT)
	{
		printf("[%d] state: [%u]\n", i, state[i]);
		i++;
	}
}

void	debug_print_lst_token(void *content)
{
	t_token		*token;

	token = (t_token*)content;
	printf("\nbeg:\t[%s]\n", token->beg);
	printf("end:\t[%s]\n", token->end);
	printf("tk:\t[%u]\n", token->tk);
}