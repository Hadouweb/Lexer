#include "lexer.h"

enum e_sts		tk_generic_1(char c, unsigned int *state, char *str)
{
	if (*state == 0 && c == str[0] && (*state = 1))
		return (STS_ACCEPT);
	*state = 0;
	return (STS_REJECT);
}

enum e_sts		tk_generic_2(char c, unsigned int *state, char *str)
{
	if (*state == 0 && c == str[0] && (*state = 1))
		return (STS_HUNGRY);
	else if (*state == 1 && c == str[1] && (*state = 2))
		return (STS_ACCEPT);
	*state = 0;
	return (STS_REJECT);
}

enum e_sts		tk_str(char c, unsigned int *state)
{
	if (*state)
		;
	if (ft_isprint(c) &&
		c != '&' &&
		c != '|' &&
		c != '<' &&
		c != '>' &&
		c != ' ' &&
		c != ';')
		return (STS_ACCEPT);
	return (STS_REJECT);
}

enum e_sts		tk_opt(char c, unsigned int *state)
{
	if (*state == 0)
	{
		if (c == '-' && (*state = 1))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	else if (*state == 1)
	{
		if (ft_isalnum(c))
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

enum e_sts		tk_pipe(char c, unsigned int *state)
{
	return (tk_generic_1(c, state, "|"));
}

enum e_sts		tk_scol(char c, unsigned int *state)
{
	return (tk_generic_1(c, state, ";"));
}

enum e_sts		tk_and(char c, unsigned int *state)
{
	return (tk_generic_1(c, state, "&"));
}

enum e_sts		tk_less(char c, unsigned int *state)
{
	return (tk_generic_1(c, state, "<"));
}

enum e_sts		tk_great(char c, unsigned int *state)
{
	return (tk_generic_1(c, state, ">"));
}

enum e_sts		tk_and_if(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, "&&"));
}

enum e_sts		tk_or_if(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, "||"));
}

enum e_sts		tk_dless(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, "<<"));
}

enum e_sts		tk_dgreat(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, ">>"));
}

enum e_sts		tk_lessand(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, "<&"));
}

enum e_sts		tk_greatand(char c, unsigned int *state)
{
	if (*state == 0)
	{
		if ((c == '>' || ft_isdigit(c)) && (*state = 1))
			return (STS_HUNGRY);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	else if (*state == 1)
	{
		if (ft_isdigit(c) && (*state = 1))
			return (STS_HUNGRY);
		if (c == '>' && (*state = 2))
			return (STS_HUNGRY);
		if (c == '&' && (*state = 2))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	else if (*state == 2)
	{
		if (c == '&' && (*state = 2))
			return (STS_ACCEPT);
		else if ((*state = 0))
			return (STS_REJECT);
	}
	return (tk_generic_2(c, state, ">&"));
}

enum e_sts		tk_lessgreat(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, "<>"));
}

enum e_sts		tk_clobber(char c, unsigned int *state)
{
	return (tk_generic_2(c, state, ">|"));
}