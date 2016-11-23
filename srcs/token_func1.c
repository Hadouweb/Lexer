#include "lexer.h"

enum e_sts		tk_name(char c, unsigned int *state)
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

enum e_sts		tk_nmbr(char c, unsigned int *state)
{
	if (c + state)
		return (STS_ACCEPT);
	return (STS_REJECT);
}

enum e_sts		tk_assn(char c, unsigned int *state)
{
	if (c + state)
		return (STS_ACCEPT);
	return (STS_REJECT);
}

enum e_sts		tk_wspc(char c, unsigned int *state)
{
	if (c + state)
		return (STS_ACCEPT);
	return (STS_REJECT);
}

enum e_sts		tk_scol(char c, unsigned int *state)
{
	if (c + state)
		return (STS_ACCEPT);
	return (STS_REJECT);
}