#include "lexer.h"

void			init_rule_func(t_parse *parse)
{
	parse->rule_func[0] = rule_great;
	//parse->rule_func[1] = rule_less;
	//parse->rule_func[2] = rule_pipe;
}

void			init_parser(t_parse *parse)
{
	ft_bzero(parse, sizeof(t_parse));
	init_rule_func(parse);
}