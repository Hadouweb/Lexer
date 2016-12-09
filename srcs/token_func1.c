#include "lexer.h"

enum e_sts		tk_generic_2(char c, unsigned int *state, char *str)
{
	if (*state == 0 && c == str[0] && (*state = 1))
		return (STS_HUNGRY);
	else if (*state == 0)
		return (STS_REJECT);
	else if (*state == 1 && c == str[1] && (*state = 2))
		return (STS_ACCEPT);
	else if (*state == 1)
		return (STS_REJECT);
	return (STS_REJECT);
}

enum e_sts		tk_and_if(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, "&&"));
}

enum e_sts		tk_word(char c, unsigned int *state)
{
	if (*state == 0)
	{
		if ((ft_isalpha(c) || c == '_') && (*state = 1))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	else if (*state == 1)
	{
		if ((ft_isalnum(c)  || c == '_'))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	return (STS_REJECT);
}

enum e_sts		tk_wspc(char c, unsigned int *state)
{
	if (*state == 0)
	{
		if ((c == ' ' || c == '\t') && (*state = 1))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	else if (*state == 1)
	{
		if ((c == ' ' || c == '\t'))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	return (STS_REJECT);
}

enum e_sts		tk_scol(char c, unsigned int *state)
{
	if (*state == 0)
	{
		if (c == ';' && (*state = 1))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	return (STS_REJECT);
}