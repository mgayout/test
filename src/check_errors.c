/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:34:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/04/30 16:17:59 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int	check_lexer(t_lex *lexer)
{
	if (lexer->type == PIPE)
		print_errors(BEGIN_PIPE);
	else if (lexlast(lexer)->type == PIPE)
		print_errors(END_PIPE);
	else if (lexlast(lexer)->type == REDIR)
		print_errors(END_TOKEN);
	else
		return (1);
	return (0);
}

int	check_parser(t_par *parser)
{
	if (parser->data)
		return (1);
	return (0);
}

void	print_errors(t_errors n)
{
	if (n == BEGIN_PIPE)
		printf("bash: syntax error near unexpected token `|'\n");
	else if (n == END_PIPE)
		printf("Ajoutez une fin de cmd.\n");
	else if (n == END_TOKEN)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (n == NO_EOF_Q)
		printf("bash: unexpected EOF while looking for matching `%c'\nbash: syntax error: unexpected end of file\n", '\'');
	else if (n == NO_EOF_DQ)
		printf("bash: unexpected EOF while looking for matching `%c'\nbash: syntax error: unexpected end of file\n", '"');
	
}