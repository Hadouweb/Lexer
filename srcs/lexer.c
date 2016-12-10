/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:37:20 by nle-bret          #+#    #+#             */
/*   Updated: 2016/11/23 12:37:21 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*lexer(char *str)
{
	t_lex			lex;

	init_lexer(&lex, str);
	//push_token(&lex, TK_BEG);
	if (main_loop_lex(&lex) == LEX_UNKNOWN_TOKEN)
		printf("LEX_UNKNOWN_TOKEN\n");
	//debug_print_status(lex.status);
	//debug_print_state(lex.state);
	ft_lstprint(lex.lst_token, debug_tree_token);
	return (lex.lst_token);
}
