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

void	lexer(t_lex *lex, char *str)
{
	init_lexer(lex, str);
	if (main_loop_lex(lex) == LEX_UNKNOWN_TOKEN)
		printf("LEX_UNKNOWN_TOKEN\n");
	//debug_print_status(lex.status);
	//debug_print_state(lex.state);
	//ft_lstprint(lex.lst_token, debug_tree_token);
}
