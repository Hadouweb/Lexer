#include "lexer.h"

int 	rule_great(t_token *token_node)
{
	//printf("rule_great %s [%s] [%s]\n",
	//debug_get_token_name(token_node->tk), token_node->beg, token_node->end);
	if (token_node->tk == TK_GREAT)
		return (1);
	return (0);
}