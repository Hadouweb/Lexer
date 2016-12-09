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
	printf("tk:\t[%s]\n", debug_get_token_name(token->tk));
}

/*const char* debug_get_token_name(enum e_tk tk)
{
	switch (tk)
	{
		case TK_WORD: return "TK_WORD";
		case TK_WSPC: return "TK_WSPC";
		case TK_AND_IF: return "TK_AND_IF";
		case TK_OR_IF: return "TK_OR_IF";
		case TK_DLESS: return "TK_DLESS";
		case TK_DGREAT: return "TK_DGREAT";
		case TK_LESSAND: return "TK_LESSAND";
		case TK_GREATAND: return "TK_GREATAND";
		case TK_LESSGREAT: return "TK_LESSGREAT";
		case TK_DLESSDASH: return "TK_DLESSDASH";
		case TK_CLOBBER: return "TK_CLOBBER";
		case TK_PIPE: return "TK_PIPE";
		case TK_SCOL: return "TK_SCOL";
		case TK_AND: return "TK_AND";
		case TK_COUNT: return "TK_COUNT";
		case TK_BEG: return "TK_BEG";
		case TK_END: return "TK_END";
	}
}*/

const char* debug_get_token_name(enum e_tk tk)
{
	switch (tk)
	{
		case TK_WORD: return "TK_WORD";
		case TK_WSPC: return "TK_WSPC";
		case TK_AND_IF: return "TK_AND_IF";
		case TK_COUNT: return "TK_COUNT";
		case TK_BEG: return "TK_BEG";
		case TK_END: return "TK_END";
	}
}