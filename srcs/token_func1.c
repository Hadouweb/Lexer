#include "lexer.h"

enum e_sts		tk_name(unsigned int c, unsigned int s)
{
	if (c + s)
		return (STS_ACCEPT);
	return (STS_REJECT);
}

enum e_sts		tk_spc(unsigned int c, unsigned int s)
{
	if (c + s)
		return (STS_ACCEPT);
	return (STS_REJECT);
}